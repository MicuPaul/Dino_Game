#pragma once
#include "stdafx.h"

class Tile{
private:
    sf::Sprite sprite;
    sf::Texture textureSheet;
public:
    Tile();
    Tile(sf::Texture* texture_sheet, sf::IntRect texture_rect);

    sf::FloatRect getGlobalBounds();
    sf::Sprite getSprite();

    void moveTile(float offsetX, float offsetY);
    void setTilepos(float x, float y);
    void setTextureRect(sf::IntRect current_frame);
    sf::IntRect getCurrentFrame();
    void setScale(float x, float y);
    void update();
    void render(sf::RenderTarget& target);
};