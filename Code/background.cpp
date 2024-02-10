#include "background.h"

background::~background()
{
}
background::background(sf::Texture* tex, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed) : texture{ tex }
{
	sprite.setTexture(*texture);
	sprite.setScale(0.08f, 0.08f);
	sprite.setPosition(pos_x, pos_y);
	direction.x = dir_x;
	direction.y = dir_y;
	movementSpeed = movement_speed;
}
void background::update()
{
	sprite.move(movementSpeed * direction);
}

void background::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
sf::Sprite background::getSprite()
{
	return sprite;
}

background::background()
{
	*texture = sf::Texture{};
}
