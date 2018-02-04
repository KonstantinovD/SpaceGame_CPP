#include "..\include\Interface.h"


Appliance::Appliance(const std::string& fileName, int points, TextureHolder& TXT)
{
	std::ifstream fin;
	fin.open(fileName);

    //content of .txt is:
    /*
    - GlobalPosition of panel X/Y
    - Texture of main panel
    - Number of element
    ...
    EACH ELEMENT:
    - LOCAL position X/Y(relative to the main panel)
    - Texture
    - changingPoints
    ...
    */

	fin >> globalPos.x >> globalPos.y;
	int typeOfTexture;
	fin >> typeOfTexture;
	type = (Textures::ID)typeOfTexture;
	if (type < Textures::ID::Bullet||type > Textures::ID::NumberOfObjects){
		type = Textures::ID::Player;
	}
	applianceSprite.setTexture(*TXT.getTexture(type));
	applianceSprite.setPosition(globalPos);

	int numberOfElements;
	fin >> numberOfElements;
	int mapIterator = 0;
	for (int i = 0; i < numberOfElements; i++)
	{
		Element temporaryElem;//New element to add it to StatesOfAppliance vector
		
		//And initializing it
		fin >> temporaryElem.localPos.x >> temporaryElem.localPos.y;

		fin >> typeOfTexture;
		temporaryElem.type = (Textures::ID)typeOfTexture;
		if (type < (Textures::ID)201 || type>Textures::ID::NumberOfObjects){
			type = Textures::ID::Player;
		}

		fin >> temporaryElem.reachedPoints;

		if (mapIterator < temporaryElem.reachedPoints)
		{
			if (0 == i)//For the first iteration we shouldn't compare MapIterator and points to key, we just need to initialize the first
			{
				mapIterator = temporaryElem.reachedPoints;
			}
			else//We had reached new Point, so, we add to the map the number of the element before current
			{//new group of element with same Reached Points appears, so, create the level of points for previous group
				VectorKey temporaryKey;
				temporaryKey.points = statesOfAppliance[i - 1].reachedPoints;
				temporaryKey.numberArrayElement = i - 1;
				map.push_back(std::move(temporaryKey));
				mapIterator = temporaryElem.reachedPoints;
			}
		}

		statesOfAppliance.push_back(std::move(temporaryElem));
		statesOfAppliance[statesOfAppliance.size() - 1].sprite.setTexture(*TXT.getTexture(statesOfAppliance[statesOfAppliance.size() - 1].type));
		statesOfAppliance[statesOfAppliance.size() - 1].sprite.setPosition(sf::Vector2f(globalPos + statesOfAppliance[statesOfAppliance.size() - 1].localPos));
	}
	if (numberOfElements > 0)//the last group of elements with same Reached Points should be added in map too
	{
		VectorKey temporaryKey;
		temporaryKey.points = statesOfAppliance[statesOfAppliance.size() - 1].reachedPoints;
		temporaryKey.numberArrayElement = statesOfAppliance.size() - 1;
		//We need to add the last element of StatesOfAppliance.ReachedPoints
		map.push_back(std::move(temporaryKey));
		
		currentIterator = 0;
		map[currentIterator].numberArrayElement;
	}

	fin.close();
	update(points);
}

void Appliance::update(int points)
{
	if (map.size() < 1) return;

	int i = map.size()-1;
	while (i > 0)
	{
		if (points < map[i].points)
		{
			i--;
		}
		else break;
	}

	currentIterator = i;
	map[currentIterator].numberArrayElement;
}


void Appliance::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(applianceSprite, states);
	if (map.size() < 1) return;
	if (currentIterator < 0) return;
	for (int i = 0; i <= map[currentIterator].numberArrayElement; i++)
	{
		target.draw(statesOfAppliance[i].sprite, states);
	}
}


