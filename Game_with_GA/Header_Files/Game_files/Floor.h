#pragma once
#include "stdafx.h"
#include "GameGlobals.h"
#include "Tile.h"
#include "Dino.h"

enum FLOOR_ID  {ID_1 = 5, ID_2 = 1405, ID_3 = 2045};

class Floor{
private:
    std::vector<Tile*> floor;
    sf::Texture* spriteSheet;
    float floorY_pos;
    int floorTileSize;
    unsigned nr_tiles;
    float game_speed;
    short floor_id;
    float updateTimer;

public:

    Floor();
    Floor(sf::Texture* sprite_sheet);
    ~Floor();

    void addFloorTile(unsigned x);
    void removeFloorTile(unsigned x);

    void setGameSpeed(float x);

    void restartFloor();

    void resetUpdateTimer();
    void updateCollision(Dino& dino) const;

    void update();
    void render(sf::RenderTarget& target);
};