#include "stdafx.h"
#include "Dino.h"

void Dino::initVariables() {
    this->animState = IDLE;
    this->gameState = false;
    this->spacePressTimer = 0;
}

void Dino::initTexture(){
    if(!this->textureSheet.loadFromFile("/home/alexpail/Documents/Dino_Game/Spirtesheet/sprite.png")){
        std::cout << "ERROR::DINO::Could not load player sheet" << "\n";
    }
}

void Dino::initSprite(){
    this->sprite.setTexture(this->textureSheet);
    this->currentFrame = sf::IntRect(1342, 6 ,80, 86);
    this->sprite.setTextureRect(this->currentFrame);
    this->sprite.setScale(0.6, 0.6);
    this->sprite.setPosition(50, 142);
}

void Dino::initAnimations(){
    this->animationTimer.restart();
    this->animationSwitch = true;
}

void Dino::initPhysics(){
    this->velocityMin_Y = 0.1f;
    this->gravity = 0.33f;
    this->jumping = false;
    this->falling = false;
}

Dino::Dino(){
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->initAnimations();
    this->initPhysics();
}


Dino::~Dino(){

}

bool Dino::getAnimSwitch(){
    bool anim_switch = this->animationSwitch;

    if(this->animationSwitch)
        this->animationSwitch = false;

    return anim_switch;
}

void Dino::resetAnimationTimer(){
    this->animationTimer.restart();
    this->animationSwitch = true;
}

sf::FloatRect Dino::getGlobalBounds() const{
    return this->sprite.getGlobalBounds();
}

sf::Sprite Dino::getSprite() const {
    return this->sprite;
}

short Dino::getAnimState() const {
    return this->animState;
}

void Dino::setJumpSound(sf::Sound J) {
    this->jumpSound = J;
}

void Dino::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Dino::setTextureRect(sf::IntRect current_frame) {
    this->sprite.setTextureRect(current_frame);
}

void Dino::setTexture(sf::Texture* texture) {
    this->sprite.setTexture(*texture);
}

void Dino::setGameState(bool state) {
    this->gameState = state;
}

void Dino::setJumpingFalse() {
    this->jumping = false;
    this->falling = false;
    this->spacePressTimer = 0;
}

void Dino::resetVelocityY(){
    this->velocity_Y = 0.f;
}

void Dino::restartDino() {
    this->currentFrame = sf::IntRect(1342, 6 ,80, 86);
    this->sprite.setTextureRect(this->currentFrame);
    this->animState = RUNNING;
    this->sprite.setPosition(50, 142);
    this->gameState = true;
}

void Dino::jump(bool type){
    if(!type){ //short jump
        if(this->getGlobalBounds().top != 67)
            this->velocity_Y = - std::sqrt(2 * this->gravity * (this->getGlobalBounds().top - 67));  //jump from 142 to 67 (jumping 75)
        else {
            this->falling = true;
            this->jumping = false;
        }
    }
    else{     //long jump
        if(this->getGlobalBounds().top != 32)
            this->velocity_Y = - std::sqrt(2 * this->gravity * (this->getGlobalBounds().top - 32));  //jump from 142 to 32 (jumping 110)
        else {
            this->falling = true;
            this->jumping = false;
        }
    }
}

void Dino::updatePhysics(){
    this->velocity_Y += 1.f * this->gravity;

    if(std::abs(this->velocity_Y) < this->velocityMin_Y) {
        this->velocity_Y = 0.f;
        this->falling = true;
    }

    this->sprite.move(0, this->velocity_Y);
}

void Dino::updateMovement(){
    if(this->gameState && !this->jumping)
        this->animState = RUNNING;
    else if(this->jumping)
        this->animState = JUMPING;
    else
        this->animState = IDLE;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !this->jumping) {
        this->animState = DUCKING;
    }
    else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) or
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)))
    {
        if(!this->jumping && !this->falling){
            this->jumpSound.play();
        }
        this->animState = JUMPING;
        this->gameState = true;
        this->jumping = true;
        this->spacePressTimer += 1;
    }

    if(this->spacePressTimer > 0 && this->spacePressTimer < 5 && !this->falling){
        this->jump(false); //short jump if space is pressed for only 4 frames
    }
    else if(this->spacePressTimer >= 5 && !this->falling){
        this->jump(true);
    }


}

void Dino::updateAnimations(){
    if(this->animState == RUNNING) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {

            if(this->currentFrame.width != 80) {
                this->currentFrame = sf::IntRect(1342, 6, 80, 86);
            }

            if (this->currentFrame.left != 1606)
                this->currentFrame.left = 1606;
            else
                this->currentFrame.left = 1518;

            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    }else if(this->animState == JUMPING){
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {

            if(this->currentFrame.width != 80) {
                this->currentFrame = sf::IntRect(1342, 6, 80, 86);
            }

            this->currentFrame.left = 1342;

            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    }else if(this->animState == DUCKING){
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {

            if(this->currentFrame.left != 1870)
                this->currentFrame = sf::IntRect(1870, 40 ,110, 52);
            else
                this->currentFrame = sf::IntRect(1988, 40 ,110, 52);

            this->setPosition(this->getGlobalBounds().left, this->getGlobalBounds().top + 86 * 0.6 - 52 * 0.6);

            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    }
}

void Dino::update(){
    this->updateMovement();
    this->updateAnimations();
    this->updatePhysics();
}

void Dino::render(sf::RenderTarget &target){
    target.draw(this->sprite);
}