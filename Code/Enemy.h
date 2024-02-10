#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "animation.h"
struct enemy_stats {
	int hp;
	int hp_max;
	int points;
	int damage;
};
class Enemy
{
	sf::Sprite shape;
	sf::Texture* texture;
	sf::Sprite health_meter{};
	sf::Texture* current_health{};
	sf::Vector2f direction{};
	float movementSpeed{};
	enemy_stats stats{};
	void init();
public:
	Enemy();
	Enemy(sf::Texture* tex, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	enemy_stats& getStats();
	virtual ~Enemy();
	sf::Sprite& getShape();
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget& target);
	animation anim;

};

