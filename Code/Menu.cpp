#include "Menu.h"

void Menu::updateInput()
{
	sf::Mouse mouse{};
	sf::Event e{};
	if (mouse.isButtonPressed(mouse.Left)) {
		if (mouse.getPosition().x > Menu_map["play"].getGlobalBounds().getPosition().x && mouse.getPosition().x < Menu_map["play"].getGlobalBounds().getPosition().x + Menu_map["play"].getGlobalBounds().getSize().x) {
			if (mouse.getPosition().y > Menu_map["play"].getGlobalBounds().getPosition().y && mouse.getPosition().y < Menu_map["play"].getGlobalBounds().getPosition().y + Menu_map["play"].getGlobalBounds().getSize().y) {
				play = true;
			}
		}
		if (mouse.getPosition().x > Menu_map["highScores"].getGlobalBounds().getPosition().x && mouse.getPosition().x < Menu_map["highScores"].getGlobalBounds().getPosition().x + Menu_map["highScores"].getGlobalBounds().getSize().x) {
			if (mouse.getPosition().y > Menu_map["highScores"].getGlobalBounds().getPosition().y && mouse.getPosition().y < Menu_map["highScores"].getGlobalBounds().getPosition().y + Menu_map["highScores"].getGlobalBounds().getSize().y) {
				scores = true;
			}
		}
	}
	else if (mouse.isButtonPressed(mouse.Right)) {
		play = false;
		scores = false;
	}
	else {
		if (mouse.getPosition().x > Menu_map["play"].getGlobalBounds().getPosition().x && mouse.getPosition().x < Menu_map["play"].getGlobalBounds().getPosition().x + Menu_map["play"].getGlobalBounds().getSize().x) {
			if (mouse.getPosition().y > Menu_map["play"].getGlobalBounds().getPosition().y && mouse.getPosition().y < Menu_map["play"].getGlobalBounds().getPosition().y + Menu_map["play"].getGlobalBounds().getSize().y) {
				Menu_map["play"].setFillColor(sf::Color{ 0, 255, 0 });
			}
			else {
				Menu_map["play"].setFillColor(sf::Color{ 255,0,0 });
			}
		}
		else {
			Menu_map["play"].setFillColor(sf::Color{ 255,0,0 });
		}
		if (mouse.getPosition().x > Menu_map["highScores"].getGlobalBounds().getPosition().x && mouse.getPosition().x < Menu_map["highScores"].getGlobalBounds().getPosition().x + Menu_map["highScores"].getGlobalBounds().getSize().x) {
			if (mouse.getPosition().y > Menu_map["highScores"].getGlobalBounds().getPosition().y && mouse.getPosition().y < Menu_map["highScores"].getGlobalBounds().getPosition().y + Menu_map["highScores"].getGlobalBounds().getSize().y) {
				Menu_map["highScores"].setFillColor(sf::Color{ 0, 255, 0 });
			}
			else {
				Menu_map["highScores"].setFillColor(sf::Color{ 255,0,0 });
			}
		}
		else {
			Menu_map["highScores"].setFillColor(sf::Color{ 255,0,0 });
		}

	}


}



void Menu::init()
{
	font.loadFromFile("c:/fonts/NotoSans-Regular.ttf");
	Menu_map["play"] = sf::Text{};
	Menu_map["play"].setFont(font);
	Menu_map["play"].setString("BLAST OFF");
	Menu_map["play"].setCharacterSize(48);
	Menu_map["play"].setPosition(0, 300);
	
	Menu_map["highScores"] = sf::Text{};
	Menu_map["highScores"].setFont(font);
	Menu_map["highScores"].setString("HIGHSCORES");
	Menu_map["highScores"].setCharacterSize(48);
	Menu_map["highScores"].setPosition(0, 400);

	Menu_map["title"] = sf::Text{};
	Menu_map["title"].setFont(font);
	Menu_map["title"].setString("||SPACE WARS||");
	Menu_map["title"].setCharacterSize(76);
	Menu_map["title"].setFillColor(sf::Color::Magenta);
	if (!background.loadFromFile("c:/sprites/background.png")) {
		std::cout << "error loading background" << std::endl;
	}
	std::ifstream in{"c:/highscores.txt"};
	if (!in) {
		std::cout << "failed" << std::endl;
	}
	int temp{};
	std::string name{};
	while (in >> name >> temp) {
		std::string str = std::to_string(temp);
		sf::Text txt{};
		txt.setFont(font);
		txt.setCharacterSize(48);
		txt.setFillColor(sf::Color::Green);
		txt.setString(name + ": " + str);
		highScores[temp] = txt;
	}
	back.setTexture(background);
}
