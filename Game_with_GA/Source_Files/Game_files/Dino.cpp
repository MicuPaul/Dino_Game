#include "Dino.h"


void Dino::initVariables() {
    this->animState = IDLE;
    this->hasFailed = false;
    this->score = 0;
    this->penalty = 0;
    this->reward = 0;
    this->NN = nullptr;
}

void Dino::initTexture(){
    if(!this->textureSheet.loadFromFile("/home/alexpail/Documents/Dino_Game/Finished_Game_for_single_player/Spirtesheet/sprite.png")){
        std::cout << "ERROR::DINO::Could not load sprite sheet" << "\n";
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
    this->velocity_Y = 0.f;
    this->gravity = 0.8f;
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
    delete this->NN;
}

bool Dino::getAnimSwitch(){
    bool anim_switch = this->animationSwitch;

    if(this->animationSwitch)
        this->animationSwitch = false;

    return anim_switch;
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

unsigned int Dino::getScore() const {
    return this->score;
}


bool Dino::HasFailed() const {
    return hasFailed;
}

bool Dino::Jump_or_Duck_availability() const {
    if(!this->jumping && !this->falling)
        return true;
    else
        return false;
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

void Dino::setFailure() {
    this->hasFailed = true;
}

void Dino::setScore(unsigned int scor) {
    if(!this->HasFailed()){
        this->score = scor;
    }
}

void Dino::setJumpingFalse() {
    this->jumping = false;
    this->falling = false;
}

void Dino::resetVelocityY(){
    this->velocity_Y = 0.f;
}

void Dino::resetAnimationTimer(){
    this->animationTimer.restart();
    this->animationSwitch = true;
}

void Dino::resetDino() {
    this->animState = IDLE;
    this->resetAnimationTimer();
    this->currentFrame = sf::IntRect(1342, 6 ,80, 86);
    this->sprite.setTextureRect(this->currentFrame);
    this->hasFailed = false;
    this->score = 0;
    this->penalty = 0;
    this->reward = 0;
    this->velocity_Y = 0.f;
    this->jumping = false;
    this->falling = false;
    if(this->NN != nullptr){
        delete this->NN;
        this->NN = nullptr;
    }
}

void Dino::Attach(NeuralNet* net)
{
    if(this->NN != nullptr)
        delete this->NN;
    this->NN = net;
}

void Dino::setInputs(std::vector<float> inputs) {
    this->NN->SetInput(inputs);
}

NeuralNet* Dino::GetNeuralNet()
{
    return this->NN;
}

void Dino::jump(bool type){
    if(!type){ //short jump
        if(this->getGlobalBounds().top > 67) {
            this->velocity_Y = -std::sqrt(2 * this->gravity * (this->getGlobalBounds().top - 67));  //jump from 142 to 67 (jumping 75)
            this->jumping = true;
        }
        else {
            this->falling = true;
            this->jumping = false;
        }
    }
    else {     //long jump
        if (floor(this->getGlobalBounds().top) > 32){
            this->velocity_Y = -std::sqrt(2 * this->gravity * (this->getGlobalBounds().top - 32));//jump from 142 to 32 (jumping 110)
            this->jumping = true;
        }
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

void Dino::updateMovement(Tile* closest_obstacle) {

    if(this->jumping || this->falling){
        this->animState = JUMPING;
    }
    else
        this->animState = RUNNING;

    float max = 0;
    unsigned int action = NOTHING;
    for(unsigned int i = 0; i < NR_OF_OUTPUTS; i++){
        if(this->NN->GetOutput(i) > max){
            max = this->NN->GetOutput(i);
            action = i;
        }
    }

    switch (action) {
        case BIG_JUMP:
            if(this->Jump_or_Duck_availability()) {
                this->resetAnimationTimer();
                this->animState = JUMPING;
                this->jump(true);
                this->penalty += 3;
            }
            break;
        case DUCK:
            if(this->Jump_or_Duck_availability()) {
                this->animState = DUCKING;
                if(closest_obstacle != nullptr)
                    if(closest_obstacle->getGlobalBounds().left < 98.f && (fabs(closest_obstacle->getGlobalBounds().height - 78*0.6)) < 0.001 ) //check if it's a bird above the dino
                        this->reward += 75;
                    else
                        this->penalty += 2;
            }
            break;
        case NOTHING:
            this->animState = RUNNING;
            break;

    }


}


void Dino::updateAnimations(){
    if(this->animState == RUNNING) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch()) {

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
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch()) {

            if(this->currentFrame.width != 80) {
                this->currentFrame = sf::IntRect(1342, 6, 80, 86);
            }

            this->currentFrame.left = 1342;

            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    }else if(this->animState == DUCKING){
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch()) {

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

void Dino::update(Tile* closest_obstacle) {
    this->NN->Update();
    this->updateMovement(closest_obstacle);
    this->score += this->reward;
    if (this->score <= this->penalty)
        this->score = 0;
    else
        this->score -= this->penalty;
    this->updateAnimations();
    this->updatePhysics();
}

void Dino::render(sf::RenderTarget &target){
    target.draw(this->sprite);
}
