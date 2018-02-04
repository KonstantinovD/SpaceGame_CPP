#ifndef _GAME_SPACEGAME_180204_
#define _GAME_SPACEGAME_180204_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <ctime>
#include <fstream>

#include "../include/Interface.h"
#include "../include/TextureHolder.h"
#include "../include/RouteEntity.h"
#include "../include/Background.h"
#include "../include/Menu.h"

#include "../include/GameOverText.h"
#include "../include/GameConstants.h"

#include "../include/Entity.h"
#include "../include/Bullet.h"
#include "../include/Enemy.h"
#include "../include/Spawn.h"
#include "../include/Player.h"

class Game
{
public:
    Game(sf::RenderWindow &userWindow); //�����������
    void run(); //������� ������� ����, ������� ����

private:
    sf::RenderWindow* mWindow;

private:
    void processEvents(); //��������� ������� ������������
    void update(sf::Time deltaTime); //���������� ������� ������
    void render(); //������ ���� � ���������� �� ������
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); //������� �������� ������� �������

    Spawn enemySpawn;
    Player mPlayer;
    Background spaceLandscape;

    bool currentGameContinies;//Is our game still continue

private:
    //sf::RenderWindow mWindow;  //���� ����

    std::vector<std::unique_ptr<Bullet>> enemyBullets;
    std::vector<std::unique_ptr<Bullet>> playerBullets;

private:
    void checkCollusions();
    void gameOver();
    void decreaseHP(int &firstEntity, int &secondEntity);//We change hp of object. We subtract firstEntity HP from the secondEntity HP, then we do the same, but we change Minuend and Subtrahend
    void gameLogic();

private:
    std::vector<std::unique_ptr<Appliance>> panelsArray;
};

void gameLoop(sf::RenderWindow& mWindow);

#endif