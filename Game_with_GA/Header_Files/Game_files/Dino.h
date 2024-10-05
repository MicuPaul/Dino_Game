#pragma once
#include "stdafx.h"
#include "NeuralNet.h"
#include "Tile.h"
#include "Score.h"

enum DINO_ANIMATION_STATES {IDLE = 0, RUNNING, JUMPING, DUCKING};

class Dino{
private:
    sf::Sprite sprite;
    sf::Texture textureSheet;
    //Animation

    short animState;
    sf::Clock animationTimer;
    sf::IntRect currentFrame;
    bool animationSwitch;

    //Physics
    float velocity_Y;
    float velocityMin_Y;
    float gravity;
    bool jumping;
    bool falling;

    //Movement

    void initVariables();
    void initTexture();
    void initSprite();
    void initAnimations();
    void initPhysics();

    //Agent
    unsigned int score;
    unsigned int penalty;
    unsigned int reward;
    bool hasFailed;
    NeuralNet* NN;

public:
    Dino();
    virtual ~Dino();

    //Accessors
    bool getAnimSwitch();
    sf::FloatRect getGlobalBounds() const;
    sf::Sprite getSprite() const;
    short getAnimState() const;
    unsigned int getScore() const;
    bool HasFailed() const;
    bool Jump_or_Duck_availability() const;

    //Modifiers
    void setPosition(float x, float y);
    void setTextureRect(sf::IntRect current_frame);
    void setTexture(sf::Texture* texture);
    void setFailure();
    void setScore(unsigned int scor);
    void setJumpingFalse();
    void resetVelocityY();
    void resetAnimationTimer();
    void resetDino();

    //Functions
    void Attach(NeuralNet* net);
    void setInputs(std::vector<float> inputs);
    NeuralNet* GetNeuralNet();

    void jump(bool type = false);
    void updatePhysics();
    void updateMovement(Tile* closest_obstacle);
    void updateAnimations();
    void update(Tile* closest_obstacle);
    void render(sf::RenderTarget& target);
};

