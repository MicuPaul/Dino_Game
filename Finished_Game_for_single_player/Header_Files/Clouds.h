#pragma once
#include "stdafx.h"
#include "Tile.h"

class Clouds{
private:
    std::vector<Tile*> sky;
    sf::Texture* spriteSheet;
    unsigned cloudWidth;
    unsigned maxClouds;
    unsigned cloudsInSky;
    float cloudsSpeed;
    float updateTimer;

    void initClouds();

public:
    Clouds();
    Clouds(sf::Texture* sprite_sheet);
    ~Clouds();

    void addCloud(unsigned x);
    void removeCloud(unsigned x);

    void resetUpdateTimer();
    void update();
    void render(sf::RenderTarget& target);
};