#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include <map>
#include <iostream>
#include <fstream>
class Menu
{
public:
	
	bool play{false};
	bool scores{false};
	bool over{false};
	sf::Font font{};
	sf::Texture background{};
	sf::Sprite back{};
	std::map<std::string, sf::Text> Menu_map{};
	std::map<int,sf::Text> highScores{};
	std::string score_path{ "C:\Lectures\space_invaders\space_invaders\hishScores.txt" };
	void updateInput();
	void init();

};

