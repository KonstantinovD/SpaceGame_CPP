#ifndef _BULLET_SPACEGAME_180204_
#define _BULLET_SPACEGAME_180204_


#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "GameConstants.h"

class Bullet : public Entity
{
public:
    Bullet(sf::Vector2f vect, bool isPlayer, int HP);
    bool bulletUpdate(sf::Time dt);//move bullet
    //If return 0, Bullet becomes destroyed
    bool isPlayerBullet;
};

#endif
