#pragma once
#include "stdafx.h"
#include "GameGlobals.h"
#include "Dino.h"
#include "Floor.h"
#include "Clouds.h"
#include "Obstacles.h"
#include "Score.h"
#include "Genetic_Algorithm.h"

class Game{
private:
    sf::RenderWindow window;
    sf::Event ev;
    sf::Texture spriteSheet;

    bool gameState;
    bool initGame;

    Floor* floor;
    Clouds* sky;
    Obstacles* obstacles;
    Score* score;
    Genetic_Algorithm* GA;
    unsigned int gameOverTimer;
    unsigned int scoreTimer;

    void initGA();
    void initWindow();
    void initSpritesheet();
    void initFloor();
    void initSky();
    void initObstacles();
    void initScore();

public:
    Game();
    virtual ~Game();

    //Functions

    void updateGA_Dinos();
    void updateFloor();
    void updateSky();
    void updateObstacles();
    void updateScore();
    void update();
    void renderGA_Dinos_Info();
    void renderFloor();
    void renderSky();
    void renderObstacles();
    void render();
    const sf::RenderWindow& getWindow() const;
};