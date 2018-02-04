#include "../include/Player.h"

Player::Player(sf::Vector2f vect)
{
    mSprite.setTexture(*TextureHolder::TH().getTexture(type));
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    mSprite.setPosition(vect);

    isMovingRight = false;
    isMovingLeft = false;

    isAttack = false;
    isFire = false;

    hitPoints = (int)HITPOINTS_ENTITY::ID::Player;
}

void Player::playerLogic()
{
    if (mSprite.getPosition().x < LOGIC_GAME::LEFT_Deadline) {
        float coordinateY = mSprite.getPosition().y;
        mSprite.setPosition(LOGIC_GAME::LEFT_Deadline, coordinateY);
    }
    if (mSprite.getPosition().x > LOGIC_GAME::RIGHT_Deadline) {
        float coordinateY = mSprite.getPosition().y;
        mSprite.setPosition(LOGIC_GAME::RIGHT_Deadline, coordinateY);
    }
}

void Player::playerUpdate(sf::Time dt)
{
    if (isMovingRight)
    {
        mSprite.move(SPEEDS_ENTITY::PLAYER_SPEED*dt.asSeconds(), 0);
    }
    if (isMovingLeft)
    {
        mSprite.move(-(SPEEDS_ENTITY::PLAYER_SPEED*dt.asSeconds()), 0);
    }
    playerLogic();
    if (isAttack){
        playerAttack();
    }
}

void Player::playerAttack()
{
    if (timeToFire.getElapsedTime().asSeconds() > TIMING::PLAYER_TIME_BETWEEN_BULLETS)
    {
        timeToFire.restart();
        isFire = true;
        return;//isFire is true, Player can attack
    }
    isFire = false;
    return;//isFire is false, Player can't attack
}