#pragma once
#include "stdafx.h"
#include "Dino.h"
#include "Floor.h"
#include "Clouds.h"
#include "Obstacles.h"
#include "Score.h"

class Game{
private:
    sf::RenderWindow window;
    sf::Event ev;
    sf::Texture spriteSheet;
    std::vector<sf::SoundBuffer> buff;
    sf::Sound jumpSound;
    sf::Sound deathSound;
    sf::Sound pointSound;
    std::vector<sf::Sprite> gameOverSprites;

    unsigned gameOverTimer;  //Waits for 50 frames after game over
    bool gameState;
    bool initGame;

    Dino* dino;
    Floor* floor;
    Clouds* sky;
    Obstacles* obstacles;
    Score* score;

    void initWindow();
    void initSpritesheet();
    void initDino();
    void initFloor();
    void initSky();
    void initObstacles();
    void initScore();
    void initSounds();

public:
    Game();
    virtual ~Game();

    //Functions
    void updateDino();
    void updateFloor();
    void updateSky();
    void updateObstacles();
    void updateScore();
    void update();
    void renderDino();
    void renderFloor();
    void renderSky();
    void renderObstacles();
    void renderGameOver();
    void renderScore();
    void render();
    const sf::RenderWindow& getWindow() const;
};