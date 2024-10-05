#ifndef DINO_GAME_NLAYER_H
#define DINO_GAME_NLAYER_H

#include "stdafx.h"
#include "GameGlobals.h"
#include <vector>

class Neuron{
public:
    int numInputs;
    float Value;
    std::vector<float> weights;

    void Populate(int numOfInputs){
        this->numInputs = numOfInputs;

        for (unsigned int i = 0; i < numOfInputs; i++)
        {
            weights.push_back(RandomClamped());
        }

        weights.push_back(RandomClamped());
    }

    void Initilise(std::vector<float> weightsIn, int numOfInputs)
    {
        this->numInputs = numOfInputs;
        weights = weightsIn;
    }

    Neuron(){}
    ~Neuron(){}
};

const float BIAS = -1.0f;

class NLayer{
private:
    int totalNeurons;
    int totalInputs;
    std::vector<Neuron> neurons;
public:
    NLayer();
    ~NLayer();

    void Evaluate(std::vector<float> input, std::vector<float> &output, bool LayerType);

    void LoadLayer(std::vector<Neuron> in);

    // Creates the layer with 'n' neurons, intilise with random weights.
    void PopulateLayer(int numOfNeurons, int numOfInputs);

    void SetWeights(std::vector<float> weights, int numOfNeurons, int numOfInputs);
    std::vector<float> GetWeights();
    int GetNrNeurons();
    std::vector<Neuron> GetNeurons();

    void SetNeurons(std::vector<Neuron> neurons, int numOfNeurons, int numOfInputs);
};



#endif // #ifndef DINO_GAME_NLAYER_H