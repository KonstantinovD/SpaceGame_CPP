#ifndef _ROUTEENTITY_SPACEGAME_170824_
#define _ROUTEENTITY_SPACEGAME_170824_

#include <SFML/Graphics.hpp>

class RouteEntity
{
public:
	RouteEntity(sf::Vector2f globalCord, std::vector<sf::Vector2f> route, float entitySpeed);
	void setNewRoute(sf::Vector2f globalCord, std::vector<sf::Vector2f> route, float entitySpeed);

public:
	std::vector<sf::Vector2f> points;//coordinates of points to change direction of moving
	std::vector<sf::Vector2f> directions;


private:
	sf::Vector2f calculateVelocity(int x1, int y1, int x2, int y2, float entitySpeed);//Calculate the velocity through the similarity of the triangles of coordinates

};


#endif