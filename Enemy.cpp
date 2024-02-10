#include "Enemy.h"


void Enemy::init()
{
	
	
}
Enemy::Enemy()
{
	init();
}

Enemy::Enemy(sf::Texture* tex, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed) : texture{ tex }
{
	init();
	shape.setTexture(*texture);
	shape.setScale(0.2f, 0.2f);
	shape.setPosition(pos_x, pos_y);
	anim = animation{};
	direction.x = dir_x;
	direction.y = dir_y;
	movementSpeed = movement_speed;
}

enemy_stats& Enemy::getStats()
{
	return stats;
}

Enemy::~Enemy()
{
}

sf::Sprite& Enemy::getShape() 
{
	return shape;
}

const sf::FloatRect Enemy::getBounds() const
{
	return shape.getGlobalBounds();
}

void Enemy::update()
{
	shape.move(movementSpeed * direction);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
