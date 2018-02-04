#include "../include/Bullet.h"

Bullet::Bullet(sf::Vector2f vect, bool isPlayer, int hp)
{
    isPlayerBullet = isPlayer;

    type = Textures::ID::Bullet;

    mSprite.setTexture(*TextureHolder::TH().getTexture(type));
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    mSprite.setPosition(vect);

    hitPoints = hp;
}

bool Bullet::bulletUpdate(sf::Time dt)
{
    if (true == isPlayerBullet){
        mSprite.move(0, (-1)*(SPEEDS_ENTITY::BULLET_SPEED * dt.asSeconds()));//Move up(negative number of speed)
        if (mSprite.getPosition().y < LOGIC_GAME::UPPER_Deadline) return 1;
    }
    else{
        mSprite.move(0, SPEEDS_ENTITY::BULLET_SPEED * dt.asSeconds());//Move down(positive number of speed)
        if (mSprite.getPosition().y > LOGIC_GAME::LOWER_Deadline) return 1;
    }
    return 0;//if return 1, Bullet becomes destroyed
}
