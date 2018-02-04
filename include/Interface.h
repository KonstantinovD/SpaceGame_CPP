#ifndef _INTERFACE_SPACEGAME_170824_
#define _INTERFACE_SPACEGAME_170824_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "TextureHolder.h"

//element of panel (panel, HP in shape of hearts)
struct Element
{
	sf::Vector2f localPos;
	sf::Sprite sprite;
	int reachedPoints;//how many points needs for current element being showed
	Textures::ID type;//texture of element
};

struct VectorKey
{
	int points;//reachedPoints of group of element
	int numberArrayElement;//the last element in group of element with same ReachedPoints
};

//"appliance" class - for game panels, for instance
class Appliance: public sf::Drawable
{
public://for main panel
	sf::Vector2f globalPos;
	sf::Sprite applianceSprite;
	Textures::ID type;

public:
	std::vector<Element> statesOfAppliance;
	std::vector<VectorKey> map;//elements are drawed from the first to the current. And the current last element to draw is determined by the points of state

public:
	int currentIterator;//"map" iterator points to the current state
    //actually, no variable with points exist, but map contains intermediate points
public:
	Appliance(const std::string& fileName, int points, TextureHolder& TXT);
	void update(int points);//update appliance by "setting points" (actually, currentIterator may change its position)

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};



#endif