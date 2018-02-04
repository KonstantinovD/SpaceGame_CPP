#include "..\include\RouteEntity.h"

RouteEntity::RouteEntity(sf::Vector2f globalCord, std::vector<sf::Vector2f> route, float entitySpeed)
{
	sf::Vector2f temporarySummand = (sf::Vector2f(0, 0));
	if (route.size()>0) temporarySummand = globalCord - route[0];
	for (int i = 0; i < route.size(); i++)
	{
		points.push_back(route[i] + temporarySummand);
	}

	for (int i = 0; i < (route.size() - 1); i++)
	{
		sf::Vector2f newSpeed = calculateVelocity(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, entitySpeed);
		directions.push_back(std::move(newSpeed));
	}
}

void RouteEntity::setNewRoute(sf::Vector2f globalCord, std::vector<sf::Vector2f> route, float entitySpeed)
{
	int sizeForErase = directions.size();
	for (int i = 0; i < sizeForErase; i++){
		directions.pop_back();
	}
	sizeForErase = points.size();
	for (int i = 0; i < sizeForErase; i++){
		points.pop_back();
	}

	sf::Vector2f temporarySummand = (sf::Vector2f(0, 0));
	if (route.size()>0) temporarySummand = globalCord - route[0];
	for (int i = 0; i < route.size(); i++)
	{
		points.push_back(route[i]);
	}

	for (int i = 0; i < (route.size() - 1); i++)
	{
		sf::Vector2f newSpeed = calculateVelocity(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, entitySpeed);
		directions.push_back(std::move(newSpeed));
	}
}

sf::Vector2f RouteEntity::calculateVelocity(int x1, int y1, int x2, int y2, float entitySpeed)
{
	float x = x2 - x1;
	float y = y2 - y1;
	float z = y*y + x*x;
	z = sqrt(z);
    float vx = (entitySpeed*x) / z,
        vy = (entitySpeed*y) / z;

	sf::Vector2f rez(vx, vy);
	return rez;
}