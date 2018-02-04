#pragma once

#ifndef _TEXTUREHOLDER_SPACEGAME_170824_
#define _TEXTUREHOLDER_SPACEGAME_170824_

#include <SFML/Graphics.hpp>
#include <memory>
#include <sstream>

//////////////////////// NAMESPACE TEXTURES ////////////////////////////////////////////////////////////////////////////////////////////////
namespace Textures
{
	enum ID //types of objects, we need one texture for every type
	{
		Bullet,
		Player,
		Enemy,
		Nothing,
		LifeHearth,
		ArmorShield,
		Appliance1,
		BackGround,
        Button1,
        Button2,
        Button3,
        Button4,
        MenuBack1,
        MenuBack2,

		TheLast,
		NumberOfObjects = TheLast - Nothing + Enemy + 1//counter of number of textures
	};
}

class TextureHolder
{
private:
	std::vector<std::shared_ptr<sf::Texture>> holder; //Holder for pointers to textures

public:
	TextureHolder();
	std::shared_ptr<sf::Texture> getTexture(Textures::ID type); //Get texture using ID of it

    static TextureHolder& TH();

};



#endif