#ifndef _GAMECONST_SPACEGAME_171126_
#define _GAMECONST_SPACEGAME_171126_

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <fstream>



const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);//FPS


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// A LOT OF CLASSES //////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////// HITPOINTS_ENTITY ////////////////////////////////////////////////////////////////////////////////////////////////

class HITPOINTS_ENTITY
{
public:
    static enum ID
    {
        Bullet = 10,
        Player = 30,
        Enemy = 10,
        NumberOfObjects //counter of number of hitpoints
    };
};

//////////////////////// SPEEDS_ENTITY ////////////////////////////////////////////////////////////////////////////////////////////////
class SPEEDS_ENTITY
{
public:
    static const float ENEMY_SPEED;
    static const float PLAYER_SPEED;
    static const float BULLET_SPEED;
};



//////////////////////// TIMING ////////////////////////////////////////////////////////////////////////////////////////////////
class TIMING
{
public:
    static const float ENEMY_TIME_BETWEEN_BULLETS;
    static const float PLAYER_TIME_BETWEEN_BULLETS;

    static float timeBetweenSpawning; 
};



//////////////////////// LOGIC_GAME ////////////////////////////////////////////////////////////////////////////////////////////////
class LOGIC_GAME
{
public:
    static int killedEnemys;
    static int escapedEnemys;//If enemy escapes, player loses one of its armor
    //Both killed enemies and enemies which escaped are summands of variable which is compared with NecessaryPointsToChangeLevel[i],  

    static int spawnedEnemies;
    static int necessaryPointsToChangeLevel[10];//How many enemies should be killed or escape so we move to another level
    static int iterator;//Iterator to current NecessaryPoints...
    static int numberOfLevels;


    static bool spawnWork;//When we move from one level to another, we need delay, and spawn doesn't work this time
    float delay;//Delay betwing changing one level to another
    sf::Clock clockForDelay;


    sf::Vector2f coordinatesOfSpawn[10];//We take coordinates from file(Finp) to get it to Game::SPW (spawn)
    int numberOfSpawns;//Number of arrays (spawn, its coordinates)

    std::ifstream finp;//Reading data from file

    static int armorLeft;

    static const int UPPER_Deadline = -50;//Upper line to delete entities
    static const int LOWER_Deadline = 530;//Lower line to delete entities

    /*Border lines for the player, the second line has the same X coordinate as the width of game window*/
    static const int LEFT_Deadline = 0;
    static const int RIGHT_Deadline = 600;

    //How many times enemy will shoot
    static const int MAX_SHOOTS = 3;


    static const int positionArraySize = 6;
    sf::Vector2f positionArray[positionArraySize];

    static void randomPositionArray(sf::Vector2f* positionArray, int positionArraySize, std::vector<sf::Vector2f>& arr)
    {
        for (int i = 0; i < positionArraySize; i++)
        {
            arr.push_back(positionArray[i]);
        }
        for (int i = 2; i < (arr.size() - 1); i++)
        {
            arr[i].y = arr[i].y - 50 + rand() % 101;
        }
    }

    static LOGIC_GAME& LG(){
        static LOGIC_GAME lg;
        return lg;
    }
};

#endif