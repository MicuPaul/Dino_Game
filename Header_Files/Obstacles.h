#pragma once
#include "stdafx.h"
#include "Tile.h"
#include "Dino.h"

enum OBSTACLEID {
    SMALL_CACTUS,
    DOUBLE_SMALL_CACTI,
    TRIPLE_SMALL_CACTI,
    LARGE_CACTUS,
    DOUBLE_LARGE_CACTI,
    QUAD_LARGE_CACTI,
    BIRD
};

class Obstacles{
private:
    std::vector<Tile*> obstacles;
    sf::Texture* spriteSheet;
    sf::Clock animationTimer;
    sf::Sound deathSound;

    short obstacleId;
    unsigned obstacleWidth;
    unsigned maxObstacles;
    float game_speed;
    float updateTimer;
    float obstacleTimer;

public:
    Obstacles();
    Obstacles(sf::Texture* sprite_sheet);
    ~Obstacles();

    void getRandomObstacle();
    void addObstacle(unsigned x);
    void removeObstacle(unsigned x);

    void setGameSpeed(float x);
    void setDeathSound(sf::Sound D);

    void restartObstacles();

    void resetObstacleTimer();
    void resetUpdateTimer();
    void updateAnimations();
    void updateCollision(Dino& dino, bool* gameState);

    void update();
    void render(sf::RenderTarget& target);
};