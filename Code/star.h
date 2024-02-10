#pragma once
#include "background.h"
class star: public background
{
public:
	
	star(sf::Texture* tex, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	float scale{0.01};
	~star();
};

