#ifndef DINO_GAME_GENOME_H
#define DINO_GAME_GENOME_H
#include <vector>
class Genome{
public:
    float fitness;
    int ID;
    std::vector<float> weights;
};

#endif //DINO_GAME_GENOME_H
