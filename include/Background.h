#ifndef _BACKGROUND_SPACEGAME_170908_
#define _BACKGROUND_SPACEGAME_170908_

#include <SFML/Graphics.hpp>
#include <sstream>

#include "TextureHolder.h"

//background class is necessary for moving the image of space
const float SPEED_BACKGROUND = 100;//speed of moving


class Background: public sf::Drawable
{
private:
	sf::Sprite backSprite;//two sprites changes each other while moving
    sf::Sprite additionalBackSprite;//when one sprite is below the game screen moves to a place above the upper border
	float startX;//this place should be given by cordinates

private://text for showing points and text below it
    sf::Font fontForText;
    sf::Text textForPrintingPoints;
    sf::Text lineAboveTheNumber;

public:
    Background(TextureHolder &TXT);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void update(sf::Time dt, int DrawablePoints);//update(move) background

};




#endif