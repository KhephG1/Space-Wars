#include "Game.h"
#include <iostream>
#include <random>
//Game constructor initializes all components
Game::Game() {
	init();
	initSounds();
	initTextures();
	initPlayer();
	score = sf::Text{ "Score: " + std::to_string(player->score),font };
}
//dame destrcutor frees all dynamically allocated memory
Game::~Game() {
	delete window;
	delete player;
	for (auto& i : textures) {
		delete i.second;
	}

	for (auto* i : bullets) {
		delete i;
	}
}

void Game::updateanimations() {
	unsigned int counter{};
	for (auto anim : animations) {
		if (anim.over()) {
			animations.erase(animations.begin() + counter);
		}
		counter++;
	}

}
void Game::initSounds()
{
	sounds["shoot"] = new sf::SoundBuffer{};
	if (!sounds["shoot"]->loadFromFile("c:/sprites/shoot.wav")) {
		std::cout << "error loading bullet sprite" << std::endl;
	}
	sounds["explosion"] = new sf::SoundBuffer{};
	if (!sounds["explosion"]->loadFromFile("c:/sprites/explosion.wav")) {
		std::cout << "error loading explosion sound" << std::endl;
	}
}
void Game::run() {
	while (window->isOpen()){
		update();
		render();
	}

}

void Game::init() {
	window = new sf::RenderWindow(sf::VideoMode(1800, 1000), "Space Invaders", sf::Style::Default);
	window->setFramerateLimit(200);
	window->setVerticalSyncEnabled(false);
	score.setCharacterSize(46);
	score.setFillColor(sf::Color::Red);
	menu.init();
	std::ifstream in{"c:/highscores.txt"};
	std::string name{};
	int score{};
	while (in >> name >> score) {
		high_scores[score] = name;
	}
}
//Handles closing the game
void Game::updatePollEvents() {
	sf::Event e;
	while (window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed) {
			window->close();
		}
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
			window->close();
		}
	}
}
//Hanldes user input from mouse and keyboard
void Game::updateInput() {
	//Move player
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if(!player->getSprite().getPosition().x<=0)
			player->move(-1.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if(!(player->getSprite().getPosition().x + player->getSprite().getGlobalBounds().width >= window->getSize().x))
			player->move(1.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if(!player->getSprite().getPosition().y <= 0)
			player->move(0.0f, -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if(!(player->getSprite().getPosition().y + player->getSprite().getGlobalBounds().height >= window->getSize().y))
			player->move(0.0f, 1.0f);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->canAttack()) {
		bullets.push_back(new Bullet(textures["bullet"], player->getPos().x + 23.0f, player->getPos().y, 0.0f, -1.0f, 5.0f));
		playSound("shoot");
	}
	menu.updateInput();

}

void Game::playSound(std::string name)
{

	if (name == "shoot") {
		shoot.setBuffer(*sounds[name]);
		shoot.play();
	}
	if (name == "explosion") {
		explode.setBuffer(*sounds[name]);
		explode.play();
	}

}

void Game::spawnEnemies() {
	if (enemy_counter >= enemy_spawn) {
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, window->getSize().x - 100); // define the range

		std::random_device rand;
		std::mt19937 generate(rand()); 
		std::uniform_int_distribution<> dist(0,2); 
		int chooser{ dist(generate) };
		if (chooser == 0) {
			Enemy* ent{ new Enemy(textures["enemy"], distr(gen), 50.0f, 0, 1.0f, 1.7f) };
			ent->getShape().setScale(0.4, -0.4);
			ent->getStats().hp = ent->getStats().hp_max = 5;
			ent->getStats().damage = 1;
			ent->getStats().points = 50;
			enemies.push_back(ent);
		}
		else if (chooser == 1) {
			Enemy* ent{ new Enemy(textures["enemy2"], distr(gen), 50.0f, 0, 1.0f, 1.2f) };
			ent->getShape().setScale(0.15, -0.15);
			ent->getStats().hp = ent->getStats().hp_max = 8;
			ent->getStats().damage = 2;
			ent->getStats().points = 200;
			enemies.push_back(ent);
		}
		else{
			Enemy* ent{ new Enemy(textures["enemy3"], distr(gen), 50.0f, 0, 1.0f, 2.7f) };
			ent->getShape().setScale(0.6, -0.6);
			ent->getStats().hp = ent->getStats().hp_max = 2;
			ent->getStats().damage = 1;
			ent->getStats().points = 100;
			enemies.push_back(ent);
		}
		enemy_counter = 0;
		enemy_spawn -= spawn_acceleration;
	}
	enemy_counter++;
}
void Game::update() {
	updateInput();
	updatePollEvents();
	if (menu.play) {
		updateBullets();
		spawnEnemies();
		updateEnemies();
		generateBackground();
		updateBackground();
		player->update();
		updateanimations(); // need to fix crashing
		checkCollisions();
		if (player->hp <= 0) {
			end_score = player->score;
			int min{1000000};
			std::string min_name{};
			for (auto& score : high_scores) {
				if (score.first < min) {
					min = score.first;
					min_name = score.first;
				}
			}
			if (end_score > min) {
				high_scores.erase(min);
				is_high = true;
			}
			menu.play = false;
			window->clear();
			menu.over = true;
		}
	}
}

void Game::generateBackground()
{
	if (star_counter >= star_spawn) {
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, window->getSize().x - 100); // define the range
		star* str{ new star{textures["star"], (float)distr(gen),0,0.0f,1.0f,0.7} };
		str->getSprite().setScale(str->scale, str->scale);
		backgrounds.push_back(str);
		star_counter = 0;
	}
	++star_counter;
}

void Game::updateBackground()
{
	unsigned int counter{};
	for (auto* back : backgrounds) {
		back->update();
		if (back->getSprite().getGlobalBounds().top - back->getSprite().getGlobalBounds().height >= window->getSize().y) {
			delete backgrounds.at(counter);
			backgrounds.erase(backgrounds.begin() + counter);
			--counter;
		}
		counter++;
	}

}
void Game::updateEnemies()
{
	unsigned int counter{};
	for (auto* enemy : enemies) {
		enemy->update();
		if (enemy->getBounds().top - enemy->getBounds().height >= window->getSize().y) {
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
			--counter;
		}else if (enemy->getStats().hp <= 0) {
			player->score += enemy->getStats().points;
			enemy->anim.sprite.setPosition(enemy->getShape().getPosition().x , enemy->getShape().getPosition().y - (enemy->getBounds().getSize().y));
			animations.push_back(enemy->anim);
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
			playSound("explosion");
			--counter;
		}
		counter++;
	}
}
void Game::checkCollisions()
{
	unsigned int enemy_ctr{};
	for (auto* enemy : enemies) {
		if (enemy->getShape().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
			player->hp -= enemy->getStats().damage;
			enemy->getStats().hp = 0;
			if (player->hp == 2) {
				player->current_health = *textures["health2"];
				player->health_meter.setScale(0.2, 0.2);
			}
			else {
				player->current_health = *textures["health"];
				player->health_meter.setScale(0.2, 0.2);
			}
		
		}
		++enemy_ctr;
	}
	for (auto* enemy : enemies) {
		unsigned int bullet_ctr{};
		for (auto* bullet : bullets) {
			if(enemy->getShape().getGlobalBounds().intersects(bullet->getBounds())){
				enemy->getStats().hp--;
				delete bullet;
				bullets.erase(bullets.cbegin() + bullet_ctr);
				bullet_ctr--;
			}
			++bullet_ctr;	
		}
		
	}
}
void Game::render() {
	window->clear();
	if (menu.play) {
		//draw all the stuffs
		for (auto* back : backgrounds) {
			back->render(*window);
		}
		player->render(*window);
		for (auto* bullet : bullets) {
			bullet->render(*window);
		}
		for (auto* enemy : enemies) {
			enemy->render(*window);
		}
		for (auto& anim : animations) {
			anim.sprite.setTexture(explosion);
			window->draw(anim.sprite);
			anim.run();
		}
		score.setString("Score: " + std::to_string(player->score));
		window->draw(score);
	
	}
	else if (menu.scores) {
		int count{ 10 };
		sf::Text header{};
		header.setFont(font);
		header.setCharacterSize(72);
		header.setString("||HIGHSCORES||");
		header.setFillColor(sf::Color::Magenta);
		window->draw(menu.back);
		window->draw(header);
		for (auto& x : menu.highScores) {
			x.second.setPosition(700, 100 + 75 * count);
			window->draw(x.second);
			count--;
		}


	}
	else if (menu.over) {
		std::string name{};
		std::ofstream out{ "c:/highscores.txt" };
		initDialogue();
		window->draw(menu.back);
		window->draw(dialogue);
		window->display();
		sf::Clock clk{};
		sf::Time t{};
		t = clk.getElapsedTime();
		while (t < sf::seconds(5.0f)) {
			t = clk.getElapsedTime();
		}
		window->close();
		if (is_high) {
			std::cout << "HIGH SCORE ! :) " << std::endl;
			std::cout << "please enter your name and press enter" << std::endl;
			std::cin >> name;
			high_scores[end_score] = name;	
		}
		for (auto& pair : high_scores) {
			out << pair.second << " " << pair.first << std::endl;
		}
		
	}else {
		window->draw(menu.back);
		for (auto pair : menu.Menu_map) {
			window->draw(pair.second);
		}
	}
	
	window->display();

}

void Game::initPlayer() {
	player = new Player();
}

void Game::initTextures() {
	textures["bullet"] = new sf::Texture{};
	if (!textures["bullet"]->loadFromFile("c:/sprites/bullet.png")) {
		std::cout << "error loading bullet sprite" << std::endl;
	}
	textures["enemy"] = new sf::Texture{};
	if (!textures["enemy"]->loadFromFile("c:/sprites/enemy.png")) {
		std::cout << "Error loading enemy sprite" << std::endl;
	}
	textures["enemy2"] = new sf::Texture{};
	if (!textures["enemy2"]->loadFromFile("c:/sprites/enemy2.png")) {
		std::cout << "Error loading enemy sprite" << std::endl;
	}
	textures["enemy3"] = new sf::Texture{};
	if (!textures["enemy3"]->loadFromFile("c:/sprites/enemy3.png")) {
		std::cout << "error loading enemy sprite" << std::endl;
	}
	textures["health"] = new sf::Texture{};
	if (!textures["health"]->loadFromFile("c:/sprites/health.png")) {
		std::cout << "error loading health sprite" << std::endl;
	}

	textures["health2"] = new sf::Texture{};
	if (!textures["health2"]->loadFromFile("c:/sprites/health2.png")) {
		std::cout << "error loading health sprite" << std::endl;
	}

	textures["health3"] = new sf::Texture{};
	if (!textures["health3"]->loadFromFile("c:/sprites/health3.png")) {
		std::cout << "error loading health sprite" << std::endl;
	}
	textures["star"] = new sf::Texture{};
	if (!textures["star"]->loadFromFile("c:/sprites/star.png")) {
		std::cout << "error loading stars" << std::endl;
	}
	if (!explosion.loadFromFile("c:/sprites/explosion.png")) {
		std::cout << "error loading explosion" << std::endl;
	}
	if (!font.loadFromFile("c:/fonts/NotoSans-Regular.ttf")) {
		std::cout << "error loading font" << std::endl;
	}
}

void Game::initDialogue()
{
	dialogue.setString("Game Over :(");
	dialogue.setFont(font);
	dialogue.setPosition(600, 400);
	dialogue.setCharacterSize(84);
	dialogue.setFillColor(sf::Color::Red);
}

void Game::updateBullets() {
	unsigned int counter{};
	for (auto* bullet : bullets) {
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.0f) {
			delete bullets.at(counter);
			bullets.erase(bullets.begin() + counter);
			--counter;
		}
		counter++;
	}
}

