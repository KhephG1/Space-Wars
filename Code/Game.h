#pragma once
#include "player.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <map>
#include "Bullet.h"
#include "Enemy.h"
#include "star.h"
#include "Menu.h"
#include <fstream>
#include <vector>
class Game
{
private:
	unsigned int enemy_spawn{720};
	unsigned int enemy_counter{720};
	unsigned int spawn_acceleration{ 1 };
	unsigned int star_spawn{ 60 };
	unsigned int star_counter{ 60 };
	bool is_high{ false };
	int end_score{};
	sf::Text score{};
	sf::RenderWindow* window{};
	Player* player{};
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::SoundBuffer*> sounds;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	std::vector<background*> backgrounds;
	std::vector<animation> animations;
	std::map<int,std::string> high_scores{};
	sf::Texture explosion{};
	sf::Text dialogue{};
	sf::Font font{};
	sf::Sound shoot{};
	sf::Sound explode{};
	Menu menu{};
	void init();
	void initPlayer();
	void initTextures();
	void initDialogue();
	//initialize the window
public:
	Game();
	virtual ~Game();
	void updatePollEvents();
	void updateInput();
	void playSound(std::string name);
	void updateBullets();
	void spawnEnemies();
	void updateanimations();
	void initSounds();
	void run();
	void update();
	void generateBackground();
	void updateBackground();
	void updateEnemies();
	void checkCollisions();
	void render();

};

