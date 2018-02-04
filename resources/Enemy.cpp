#include "../include/Enemy.h"

Enemy::Enemy(sf::Vector2f vect, std::vector<sf::Vector2f> route) : RouteEntity(vect, route, SPEEDS_ENTITY::ENEMY_SPEED)
{
    mSprite.setTexture(*TextureHolder::TH().getTexture(type));
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    global = vect;
    mSprite.setPosition(global);

    numberOfShots = 0;
    isFire = false;

    numberOfSpawns = -1;//We will set this variable a bit later during creating enemy from spawn

    hitPoints = (int)HITPOINTS_ENTITY::ID::Enemy;
}


bool Enemy::enemyLogic()//changing directions and stopping\shooting 
{
    if (mSprite.getPosition().y < (points[1].y)) {
        velocity = directions[0];
        return true;
    }
    if (numberOfShots < LOGIC_GAME::MAX_SHOOTS){//stop and make 3 shoots
        velocity = sf::Vector2f(0, 0);
        isFire = enemyAttack();
        return true;
    }
    isFire = false;//continue moving
    if (mSprite.getPosition().y < (points[2].y)) {
        velocity = directions[1];
        return true;
    }
    if (mSprite.getPosition().y < (points[3].y)) {
        velocity = directions[2];
        return true;
    }
    if (mSprite.getPosition().y < (points[4].y)) {
        velocity = directions[3];
        return true;
    }
    velocity = directions[4];
    if (mSprite.getPosition().y > LOGIC_GAME::LOWER_Deadline)
    {
        return false;
    }
}

bool Enemy::enemyUpdate(sf::Time dt)
{
    if (!(enemyLogic())) {
        return false;
    }
    mSprite.move(velocity * dt.asSeconds());
    return true;
}

bool Enemy::enemyAttack()
{
    if (timeToFire.getElapsedTime().asSeconds() > TIMING::ENEMY_TIME_BETWEEN_BULLETS)
    {
        numberOfShots++;
        timeToFire.restart();
        return true;//isFire is true, enemy can attack
    }
    return false;//isFire is false, enemy can't attack
}