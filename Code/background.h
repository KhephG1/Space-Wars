#pragma once
#include "SFML/Graphics.hpp"
class background
{
protected:
	sf::Sprite sprite{};
	sf::Texture* texture{};
	sf::Vector2f direction{};
	float movementSpeed{};
public:
	virtual ~background();
	sf::Sprite getSprite();
	background();
	background(sf::Texture* tex, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	void update();
	void render(sf::RenderTarget& target);
};

