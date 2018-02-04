#include <SFML/Graphics.hpp>
#include "..\include\Game.h"

int main()
{
    sf::RenderWindow mWindow(sf::VideoMode(600, 480), "SPACEGAME");

    gameLoop(mWindow);

    return 0;
}


