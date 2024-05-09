#pragma once

enum DINO_ANIMATION_STATES {IDLE = 0, RUNNING, JUMPING, DUCKING};

class Dino{
private:
    sf::Sprite sprite;
    sf::Texture textureSheet;
    sf::Sound jumpSound;
    bool gameState;
    unsigned spacePressTimer;
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

public:
    Dino();
    virtual ~Dino();

    //Accessors
    bool getAnimSwitch();
    sf::FloatRect getGlobalBounds() const;
    sf::Sprite getSprite() const;
    short getAnimState() const;

    //Modifiers
    void setJumpSound(sf::Sound J);
    void setPosition(float x, float y);
    void setTextureRect(sf::IntRect current_frame);
    void setTexture(sf::Texture* texture);
    void setGameState(bool state);
    void setJumpingFalse();
    void resetVelocityY();
    void resetAnimationTimer();

    //Functions
    void restartDino();
    void jump(bool type = false);
    void updatePhysics();
    void updateMovement();
    void updateAnimations();
    void update();
    void render(sf::RenderTarget& target);
};

