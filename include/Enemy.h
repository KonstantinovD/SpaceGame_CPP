#ifndef _ENEMY_SPACEGAME_180204_
#define _ENEMY_SPACEGAME_180204_


#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "RouteEntity.h"
#include "GameConstants.h"


class Enemy : public Entity, public RouteEntity
{
public:
    Enemy(sf::Vector2f GlobalCord, std::vector<sf::Vector2f> Route);//Main construstor
    bool enemyUpdate(sf::Time dt);//Updating, if return false, we delete Enemy
    bool isFire;//Enemy create a bullet
    int numberOfSpawns;//Which spawn is a owner of this enemy

private:
    sf::Vector2f velocity;//direction
    sf::Vector2f global;//start position, it names global, because all movings
    //(using RouteEntity) are calculated relatively to global position
private:
    Textures::ID type = Textures::ID::Enemy;//IS IT NECESSARY??????

private:
    bool enemyLogic();//Set velocities depending of the reaching one or anotner crucial point

    sf::Clock timeToFire;
    int numberOfShots;//how many shots have already made
    bool enemyAttack();//if return true, we create the bullet
};

#endif