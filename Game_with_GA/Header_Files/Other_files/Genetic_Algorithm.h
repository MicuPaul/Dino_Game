#pragma once
#include "stdafx.h"
#include "GameGlobals.h"
#include "Genome.h"
#include "Dino.h"
#include "NN_Renderer.h"



class Genetic_Algorithm{
private:
    unsigned int totalPopulation;
    int generation;
    int NR_HIDDEN_LAYERS;
    int NR_NEURONS_PER_LAYER;
    int totalGenomeWeights;
    std::vector<Dino*> dinos;
    std::vector<Genome*> population;
    NN_Renderer* NN_Visualizer;
    unsigned int SelectBestTimer;
    unsigned int SelectedBestIndex;
    bool Selected_Best;

    void initNNRenderer();
    void GetBestCases(std::vector<Genome *> &out);
    void CrossBreed(Genome* g1, Genome* g2, Genome* &baby1, Genome* &baby2);
    void Mutate(Genome* genome);
    Genome* CreateNewGenome(unsigned int totalWeights);
public:

    Genetic_Algorithm();
    ~Genetic_Algorithm();

    unsigned int GetBestIndex();
    Genome* GetWorstGenome();
    Genome* GetGenome(int index);
    Dino* GetDino(int index);

    int GetTotalPopulation() const;
    int GetDinosAlive() const;

    void setDinosScore(unsigned int score);
    void setDinosInputs(std::vector<float>);
    void attachNNtoDinos();
    bool checkIfDinosFailed();
    unsigned int calculateScoresum();
    void GenerateNewPopulation();
    void BreedPopulation();
    void ClearPopulation();

    void SetGenomeFitness(float fitness, int index);
    void updateDinos(Tile* closest_obstacle);
    void renderInfo(sf::RenderTarget& target, unsigned int score);
    void render(sf::RenderTarget& target,  unsigned int score, bool gamestate);
};
