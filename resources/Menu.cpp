#include "..\include\Menu.h"
#include <iostream>


Menu::Menu(TextureHolder &TXT) : menuInterface("TextSources\\ApplianceMenu.txt", 0, TXT)
{
	iterator = 0;

	std::ifstream FINP;
	FINP.open("TextSources\\ButtonMenu.txt");
    //content of .txt is:
    /*
    - StartCondition
    - Number of buttons
    ...
    EACH BUTTON: 
    - position X/Y
    - necessaryPoints
    - changingPoints
    - type
    ...
    */

	FINP >> condition;
	int FileStrSize;//input number of buttons
	FINP >> FileStrSize;

	for (int i = 0; i < FileStrSize; i++)//creating new buttons
	{
		std::unique_ptr<Button> TemporaryObj(new Button);
        //inputting button position
		FINP>>TemporaryObj->buttonRectangle.left;
		FINP>>TemporaryObj->buttonRectangle.top;
        //height\width are equal to zero, because the size of button is depends on its texture
        TemporaryObj->buttonRectangle.width=0;
        TemporaryObj->buttonRectangle.height=0;

		FINP >> TemporaryObj->necessaryPoints;
		FINP >> TemporaryObj->changingPoints;
		FINP >> TemporaryObj->type;
		
		buttonArray.push_back(std::move(TemporaryObj));
		buttonArray[buttonArray.size() - 1]->buttonSprite.setTexture(*TXT.getTexture((Textures::ID)buttonArray[buttonArray.size() - 1]->type));
        
        buttonArray[buttonArray.size() - 1]->buttonRectangle.width = buttonArray[buttonArray.size() - 1]->buttonSprite.getLocalBounds().width;
        buttonArray[buttonArray.size() - 1]->buttonRectangle.height = buttonArray[buttonArray.size() - 1]->buttonSprite.getLocalBounds().height;

        buttonArray[buttonArray.size() - 1]->buttonSprite.setOrigin(buttonArray[buttonArray.size() - 1]->buttonRectangle.width / 2, buttonArray[buttonArray.size() - 1]->buttonRectangle.height / 2);
        buttonArray[buttonArray.size() - 1]->buttonSprite.setPosition(buttonArray[buttonArray.size() - 1]->buttonRectangle.left, buttonArray[buttonArray.size() - 1]->buttonRectangle.top);

        buttonArray[buttonArray.size() - 1]->buttonRectangle.left -= buttonArray[buttonArray.size() - 1]->buttonRectangle.width / 2;
        buttonArray[buttonArray.size() - 1]->buttonRectangle.top -= buttonArray[buttonArray.size() - 1]->buttonRectangle.height / 2;

    }
	FINP.close();
	startCondition = condition;
}


int Menu::update(sf::RenderWindow& mWindow, TextureHolder &TXT)
{
	for (int i = 0; i < buttonArray.size(); i++)
	{
		if (condition == buttonArray[i]->necessaryPoints)
		{
			buttonArray[i]->buttonSprite.setColor(sf::Color::White);
			if (buttonArray[i]->buttonRectangle.contains(sf::Mouse::getPosition(mWindow)))
			{
				buttonArray[i]->buttonSprite.setColor(sf::Color::Green);
				iterator = i;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    condition = buttonArray[iterator]->changingPoints;
                }
			}

		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		mWindow.close();
	}


	menuInterface.update(condition);
	return condition;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(menuInterface);

	for (int i = 0; i < buttonArray.size(); i++)
	{
		if (condition == buttonArray[i]->necessaryPoints)
		{
			target.draw(buttonArray[i]->buttonSprite);
		}
	}
}

void Menu::reset()
{
	condition = startCondition;
}