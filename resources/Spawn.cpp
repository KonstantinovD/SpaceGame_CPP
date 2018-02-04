#include "../include/Spawn.h"

Spawn::Spawn(){}

void Spawn::setNewSpawn(sf::Vector2f* takeRegion, int size)
{
    while (evil.size()>0){//clear current spawn and delete all created enemies
        evil.pop_back();
    }
    while (isAlive.size()>0){
        isAlive.pop_back();
    }
    while (spawnList.size() > 0){
        spawnList.pop_back();
    }

    sf::Clock clock;//just clock to add it to our struct
    ElemenemySpawnPoint object;//struct to add it to std::vector spawnList
    object.spawnTime = clock;//iinitialize clock in our struct

    for (int i = 0; i < size; i++)//Initialize all our objects
    {
        object.spawnRegion = takeRegion[i];//Set coordinates to spawnpoint of our struct
        spawnList.push_back(std::move(object));//add struct to std::vector spawnList

        isAlive.push_back(false);
    }
    for (int i = 0; i < size; i++)
    {
        spawnList[i].spawnTime.restart();
    }

}

void Spawn::updateSpawn()//in case enemy of current spawn was killed, spawn creates a new one after some period of time
{
    for (int i = 0; i < isAlive.size(); i++)
    {
        if (false == isAlive[i])
        {
            float deltaTime = spawnList[i].spawnTime.getElapsedTime().asSeconds();
            if (deltaTime > TIMING::timeBetweenSpawning)//if time is more than it is necessary
            {
                spawnList[i].spawnTime.restart();

                std::vector<sf::Vector2f> arr(0);
                LOGIC_GAME::randomPositionArray(LOGIC_GAME::LG().positionArray, LOGIC_GAME::positionArraySize, arr);

                evil.push_back(std::unique_ptr<Enemy>(new Enemy(spawnList[i].spawnRegion, arr)));
                evil[evil.size() - 1]->numberOfSpawns = i;
                isAlive[i] = true;
                LOGIC_GAME::spawnedEnemies++;
            }
        }

    }

}