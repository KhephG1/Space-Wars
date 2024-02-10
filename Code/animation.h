#pragma once
#include "SFML/Graphics.hpp"
class animation
{
public:
	animation();
	sf::Sprite sprite{};
	sf::Texture anim{};
	void run();
	bool over();
	unsigned int currentFramex{};
	unsigned int currentFramey{};
	unsigned int frameCount{};

};

