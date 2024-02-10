#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <iostream>
class Player
{
private:
	sf::Sprite sprite{};
	sf::Texture texture{};
	float movementSpeed{};
	float attack_counter{40.0f};
	float attackCoolDownMax{40.0f};
public:
	sf::Sprite health_meter{};
	sf::Texture current_health{};
	int hp{3};
	int hp_max{ 3 };
	unsigned int score{};
	Player();
	virtual ~Player();
	void initSprite();
	void initTextures();
	void update();
	sf::Sprite getSprite();
	const sf::Vector2f& getPos() const;
	void render(sf::RenderTarget& target);
	void move(const float x, const float y);
	const bool canAttack();
};

