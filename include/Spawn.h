#ifndef _SPAWN_SPACEGAME_180204_
#define _SPAWN_SPACEGAME_180204_


#include <SFML/Graphics.hpp>
#include "GameConstants.h"
#include "Enemy.h"

class Spawn
{
private:
    struct ElemenemySpawnPoint//Struct for our points of spawn
    {
        sf::Vector2f spawnRegion; //Coordinates of current spawn
        sf::Clock spawnTime;//if enemy was killed immediately after the appearance, spawn couldn't create the next enemy at the moment
    };//or we can have a an endless stream of enemies

    std::vector<ElemenemySpawnPoint> spawnList; //Every spawn point

public:
    Spawn();

    void setNewSpawn(sf::Vector2f* takeRegion, int size);//create new level - create new spawn 

    void updateSpawn(); //Updating our spawn points

    std::vector<std::unique_ptr<Enemy>> evil; //Spawn is a owner of its spawned enemies
    std::vector<bool> isAlive;//if enemy of spawn point exist
};

#endif