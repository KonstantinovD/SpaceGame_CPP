#ifndef _PLAYER_SPACEGAME_180204_
#define _PLAYER_SPACEGAME_180204_

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "GameConstants.h"

class Player : public Entity
{
public:
    Player(sf::Vector2f vect);
    bool isMovingRight;
    bool isMovingLeft;

public:
    bool isAttack;
    bool isFire;//Player create a bullet
    void playerAttack();

public:
    void playerUpdate(sf::Time dt);

private:
    void playerLogic();

private:
    sf::Clock timeToFire;

private:
    Textures::ID type = Textures::ID::Player;
};


#endif