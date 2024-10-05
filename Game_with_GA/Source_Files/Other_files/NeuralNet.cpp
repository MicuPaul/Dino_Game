#include "NeuralNet.h"

NeuralNet::NeuralNet()
        :outputLayer(NULL)
{
}

NeuralNet::~NeuralNet(){
    this->ReleaseNet();
}

void NeuralNet::ReleaseNet()
{

    if (outputLayer != NULL)
    {
        delete outputLayer;
        outputLayer = NULL;
    }
    for (unsigned int i = 0; i < hiddenLayers.size(); i++)
    {
        if (hiddenLayers[i] != NULL)
        {
            delete hiddenLayers[i];
            hiddenLayers[i] = NULL;
        }
    }
    hiddenLayers.clear();
}

void NeuralNet::Update()
{
    outputs.clear();
    std::vector<float> copyInputs;
    copyInputs = this->inputs;
    for (unsigned int i = 0; i < hiddenLayers.size(); i++)
    {

        if (i > 0)
        {
            copyInputs = outputs;
            outputs.clear();
        }

        hiddenLayers[i]->Evaluate(copyInputs, outputs, true);
    }

    copyInputs = outputs;
    outputs.clear();
    outputLayer->Evaluate(copyInputs, outputs, false);
    for(int i = 0; i < outputs.size(); ++i){
        this->outputLayer->GetNeurons()[i].Value = outputs[i];
    }

}

void NeuralNet::SetInput(std::vector<float> in)
{
    inputs = in;
}

float NeuralNet::GetOutput(unsigned int ID)
{
    if (ID >= outputAmount)
        return 0.0f;
    return outputs[ID];
}

std::vector<float> NeuralNet::GetInputs() {
    return this->inputs;
}

int NeuralNet::GetTotalOutputs() const
{
    return outputAmount;
}

void NeuralNet::CreateNet(int numOfHiddenLayers, int numOfInputs, int neuronsPerHidden, int numOfOutputs)
{
    inputAmount = numOfInputs;
    outputAmount = numOfOutputs;

    for (unsigned int i = 0; i < numOfHiddenLayers; i++)
    {
        NLayer* layer = new NLayer();
        if(i == 0)
            layer->PopulateLayer(neuronsPerHidden, this->inputAmount);
        else
            layer->PopulateLayer(neuronsPerHidden, neuronsPerHidden);
        hiddenLayers.push_back(layer);
    }

    outputLayer = new NLayer();
    outputLayer->PopulateLayer(this->outputAmount, neuronsPerHidden);
}

int NeuralNet::GetNumOfHiddenLayers()
{
    return hiddenLayers.size();
}

std::vector<NLayer *> NeuralNet::GetHiddenLayers() {
    return this->hiddenLayers;
}

NLayer* NeuralNet::GetOutputLayer(){
    return this->outputLayer;
}

Genome* NeuralNet::ToGenome()
{
    Genome* genome = new Genome();
    for (unsigned int i = 0; i < this->hiddenLayers.size(); i++)
    {
        std::vector<float> weights;
        weights = hiddenLayers[i]->GetWeights();
        for (unsigned int j = 0; j < weights.size(); j++)
        {
            genome->weights.push_back(weights[j]);
        }
    }

    std::vector<float> weights;
    weights = outputLayer->GetWeights();
    for (unsigned int i = 0; i < weights.size(); i++)
    {
        genome->weights.push_back(weights[i]);
    }

    return genome;
}

void NeuralNet::FromGenome(const Genome& genome, int numOfInputs, int neuronsPerHidden, int numOfOutputs, int numOfHiddenLayers)
{
    this->ReleaseNet();

    this->outputAmount = numOfOutputs;
    this->inputAmount = numOfInputs;
    unsigned int genomeIndex = 0;
    int hiddenLayerinputs = numOfInputs;
    for(unsigned int k = 0; k < numOfHiddenLayers; k++) {
        if(k != 0){
            hiddenLayerinputs = neuronsPerHidden;
        }
        NLayer *hidden = new NLayer();
        std::vector<Neuron> neurons;
        neurons.resize(neuronsPerHidden);
        for (unsigned int i = 0; i < neuronsPerHidden; i++) {
            std::vector<float> weights;
            weights.resize(hiddenLayerinputs + 1);
            for (unsigned int j = 0; j < hiddenLayerinputs + 1; j++) {
                weights[j] = genome.weights[genomeIndex];
                genomeIndex++;
            }
            neurons[i].Initilise(weights, hiddenLayerinputs);
        }
        hidden->LoadLayer(neurons);
        this->hiddenLayers.push_back(hidden);
    }


    std::vector<Neuron> neurons;
    neurons.resize(numOfOutputs);
    for (unsigned int i = 0; i < numOfOutputs; i++)
    {
        std::vector<float> weights;
        weights.resize(neuronsPerHidden + 1);
        for (unsigned int j = 0; j < neuronsPerHidden + 1; j++)
        {
            weights[j] = genome.weights[genomeIndex];
            genomeIndex++;
        }
        neurons[i].Initilise(weights, neuronsPerHidden);
    }
    outputLayer = new NLayer();
    this->outputLayer->LoadLayer(neurons);
}

