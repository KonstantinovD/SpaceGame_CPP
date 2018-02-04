#include "..\include\GameOverText.h"

void showGameOverString(sf::RenderWindow* &window, int gameRezult)
{
    sf::Font temporaryGameOverFont;
    temporaryGameOverFont.loadFromFile("TextSources\\arialbi.ttf");

    sf::Text temporaryFirstGOText, temporarySecondGOText;

    temporaryFirstGOText.setFont(temporaryGameOverFont);
    temporaryFirstGOText.setString("GAME OVER");
    temporaryFirstGOText.setCharacterSize(40);
    temporaryFirstGOText.setOrigin(temporaryFirstGOText.getLocalBounds().width / 2, temporaryFirstGOText.getLocalBounds().height / 2);
    temporaryFirstGOText.setPosition(300, 250);

    std::ostringstream oss;
    oss << gameRezult;
    std::string rezultPointsString = oss.str();

    rezultPointsString = "Your rezult: " + rezultPointsString;

    temporarySecondGOText.setFont(temporaryGameOverFont);
    temporarySecondGOText.setString(rezultPointsString);
    temporarySecondGOText.setCharacterSize(20);
    temporarySecondGOText.setOrigin(temporarySecondGOText.getLocalBounds().width / 2, temporarySecondGOText.getLocalBounds().height / 2);
    temporarySecondGOText.setPosition(300, 300);

    window->draw(temporaryFirstGOText);
    window->draw(temporarySecondGOText);
    window->display();
    //pause before going to the main menu
    sf::Clock pauseClock;
    pauseClock.restart();

    while (pauseClock.getElapsedTime().asSeconds() < 3.0) {}
}