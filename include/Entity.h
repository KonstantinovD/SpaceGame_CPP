#ifndef _ENTITY_SPACEGAME_180204_
#define _ENTITY_SPACEGAME_180204_

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class Entity: public sf::Drawable
{
public:
    sf::Sprite mSprite;//sprite to load texture and set on
    int hitPoints;

public:
    Textures::ID type;//type of loading texture

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif