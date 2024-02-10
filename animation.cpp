#include "animation.h"
#include <iostream>
animation::animation()
{

    anim.loadFromFile("c:/sprites/explosion.png");
    sprite.setTexture(anim);
    sprite.setTextureRect(sf::IntRect{0,0, 100, 96 });
    sprite.setPosition(300, 300);
    currentFramex = 1;
    currentFramey = 1;
    frameCount = 36;
}

void animation::run()
{
    sprite.setTextureRect(sf::Rect<int>{(int)(100 *currentFramex),(int)(96*currentFramey),100,96});
    currentFramex++;
    if (currentFramex >= 6) {
        currentFramey++;
        currentFramex = 0;
    }
  
}

bool animation::over()
{
    if (currentFramex >= 6 && currentFramey >= 6) {
        return true;
    }
    return false;
}
