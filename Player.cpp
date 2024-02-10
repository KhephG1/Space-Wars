#include "Player.h"

Player::Player() {
	initTextures();
	initSprite();
	movementSpeed = 5.0f;
}
 Player:: ~Player() {

}

void Player::update() {
	//handle shooting cooldown
	if (attack_counter < attackCoolDownMax) {
		attack_counter += 1.0f;
	}
	health_meter.setTexture(current_health);
	health_meter.setScale(0.2, 0.2);
	health_meter.setPosition(sprite.getPosition() + sf::Vector2f{ 0,sprite.getGlobalBounds().height });
}
sf::Sprite Player::getSprite()
{
	return sprite;
}
const sf::Vector2f& Player::getPos() const
{
	return sprite.getPosition();
}
void Player::render(sf::RenderTarget& target) {
	target.draw(sprite);
	target.draw(health_meter);
}
void Player::initSprite() {
	sprite.setTexture(texture);
	sprite.scale(0.05f, 0.05f);
	sprite.setPosition(200, 200);
	health_meter.setPosition(sprite.getPosition() + sf::Vector2f{ 0,sprite.getGlobalBounds().height });
	health_meter.setTexture(current_health);
}

void Player::initTextures() {

	if (!texture.loadFromFile("C:/sprites/spaceship.png")) {
		std::cout << "Error could not load texture";
	}
	if (!current_health.loadFromFile("c:/sprites/health3.png")) {
		std::cout << "error loading player health" << std::endl;
	}
	
}

void Player::move(const float dir_x, const float dir_y) {
	sprite.move(movementSpeed * dir_x, movementSpeed * dir_y);
}

const bool Player::canAttack()
{
	if (attack_counter >= attackCoolDownMax) {
		attack_counter = 0.0f;
		return true;
	}
	return false;
}
