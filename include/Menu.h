#ifndef _MENU_SPACEGAME_170908_
#define _MENU_SPACEGAME_170908_

#include <fstream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Interface.h"


class Menu: public sf::Drawable
{
private:

	struct Button
	{
		sf::IntRect buttonRectangle;
		sf::Sprite buttonSprite;
		int necessaryPoints;//how many points needs for current button being showed
		int changingPoints;//when current button is pressed the condition becomes equal to this
		int type;
	};

private:
	std::vector<std::unique_ptr<Button>> buttonArray;

	int condition;//condition is a number of points; whew some number of points is reached, menu changes its condition

	int startCondition; //If we start menu, we need to know the first condition


public:
	Appliance menuInterface;

public:
	Menu(TextureHolder &TXT);

	int update(sf::RenderWindow& mWindow, TextureHolder &TXT);//updating menu and buttons

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void reset();//set start menu condition
private:
	int iterator;//number of button mouse cursor is situated on

};

#endif