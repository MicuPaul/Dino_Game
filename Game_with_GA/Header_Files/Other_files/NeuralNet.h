#pragma once
#include "stdafx.h"
#include "Genome.h"
#include "NLayer.h"

class NeuralNet{
private:
    int inputAmount;
    int outputAmount;
    std::vector<float> inputs;
    std::vector<NLayer*> hiddenLayers;
    NLayer* outputLayer;
    std::vector<float> outputs;
public:
    NeuralNet();
    ~NeuralNet();

    void Update();
    void SetInput(std::vector<float> in);
    float GetOutput(unsigned int ID);
    std::vector<float> GetInputs();
    int GetTotalOutputs() const;

    void CreateNet(int numOfHiddenLayers, int numOfInputs, int neuronsPerHidden, int numOfOutputs);
    int GetNumOfHiddenLayers();
    std::vector<NLayer*> GetHiddenLayers();
    NLayer* GetOutputLayer();

    void ReleaseNet();

    void FromGenome(const Genome& genome, int numOfInputs, int neuronsPerHidden, int numOfOutputs, int numOfHiddenLayers);
    Genome* ToGenome();
};
