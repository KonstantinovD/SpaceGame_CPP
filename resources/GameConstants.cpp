#include "../include/GameConstants.h"

//LOGIC_GAME _LOGIC_GAME;

const float SPEEDS_ENTITY::ENEMY_SPEED = 170;
const float SPEEDS_ENTITY::PLAYER_SPEED = 190;
const float SPEEDS_ENTITY::BULLET_SPEED = 270;

const float TIMING::ENEMY_TIME_BETWEEN_BULLETS = 2.0;//Elapsed time between single shots
const float TIMING::PLAYER_TIME_BETWEEN_BULLETS = 0.67;
float TIMING::timeBetweenSpawning = 8.0;//Time between spawning

int LOGIC_GAME::killedEnemys = 0;
int LOGIC_GAME::escapedEnemys = 0;//If enemy escapes, player loses one of its armor
//Both killed enemies and enemies which escaped are summands of variable which is compared with NecessaryPointsToChangeLevel[i],  

int LOGIC_GAME::spawnedEnemies = 0;
int LOGIC_GAME::necessaryPointsToChangeLevel[10];//How many enemies should be killed or escape so we move to another level
int LOGIC_GAME::iterator = -1;//Iterator to current NecessaryPoints...
int LOGIC_GAME::numberOfLevels = 0;

bool LOGIC_GAME::spawnWork = true;//When we move from one level to another, we need delay, and spawn doesn't work this time

int LOGIC_GAME::armorLeft = 3;