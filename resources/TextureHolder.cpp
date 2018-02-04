#include "..\include\TextureHolder.h"

//TextureHolder _TEXTR;//The object of TextureHolder, one for the whole app

TextureHolder::TextureHolder()
{
	for (int i = 0; i < Textures::ID::NumberOfObjects; i++)
	{
		std::ostringstream oss;               //working with streams
		oss << i;                             //loading number to the stream
		std::string numberOfFile = oss.str(); //loading number from stream to the string

		std::shared_ptr<sf::Texture> ptr(new sf::Texture);//Create new pointer to texture
		holder.push_back(std::move(ptr));

		//Using Image to avoid some background colors(white by default)
		sf::Image img;
		img.loadFromFile("Sprites\\SpaceGame\\" + numberOfFile + ".png");
		img.createMaskFromColor(sf::Color(255, 255, 255));

		holder[i]->loadFromImage(img);//Load current texture from image
	}
}

std::shared_ptr<sf::Texture> TextureHolder::getTexture(Textures::ID type)
{
	if (type < Textures::ID::NumberOfObjects)
	{
		return holder[type];
	}
}

TextureHolder& TextureHolder::TH(){
    static TextureHolder obj;
    return obj;
}