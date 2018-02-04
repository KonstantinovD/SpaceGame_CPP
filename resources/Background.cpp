#include "..\include\Background.h"

Background::Background(TextureHolder &TXT)
{
	backSprite.setTexture(*TXT.getTexture((Textures::ID)7));
	startX = -backSprite.getLocalBounds().height + 480;//calculate start position
	backSprite.setPosition(0, startX);

    additionalBackSprite.setTexture(*TXT.getTexture((Textures::ID)7));
    additionalBackSprite.setPosition(0, (startX - backSprite.getLocalBounds().height));

    fontForText.loadFromFile("TextSources\\arialbi.ttf");
    textForPrintingPoints.setFont(fontForText);
    textForPrintingPoints.setColor(sf::Color::White);
    textForPrintingPoints.setCharacterSize(20); // pixels, no points!
    textForPrintingPoints.setPosition(10, 25);
 
    lineAboveTheNumber.setFont(fontForText);
    lineAboveTheNumber.setColor(sf::Color::White);
    lineAboveTheNumber.setCharacterSize(15);
    lineAboveTheNumber.setPosition(5, 5);
    lineAboveTheNumber.setString("Enemies killed:");
}

void Background::update(sf::Time dt, int DrawablePoints)//Move background; if we scroll it to the end, set start position
{
    std::ostringstream oss;               //working with streams
    oss << DrawablePoints;                             //loading number to the stream
    std::string pointsToDraw = oss.str(); //loading number from stream to the string
    textForPrintingPoints.setString(pointsToDraw);

    //if any sprite is below the game screen
	if (backSprite.getPosition().y >= 480)
	{
        backSprite.setPosition(0, startX - backSprite.getLocalBounds().height);
	}
    if (additionalBackSprite.getPosition().y >= 480)
    {
        additionalBackSprite.setPosition(0, startX - additionalBackSprite.getLocalBounds().height);
    }
	backSprite.move(0, (1)*SPEED_BACKGROUND*dt.asSeconds());
    additionalBackSprite.move(0, (1)*SPEED_BACKGROUND*dt.asSeconds());
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backSprite, states);
    target.draw(additionalBackSprite, states);
    target.draw(textForPrintingPoints, states);
    target.draw(lineAboveTheNumber, states);
}