#include "NLayer.h"

NLayer::NLayer() {

}

NLayer::~NLayer() {

}

void SoftMax(std::vector<float> &output)
{
    float sum = 0.f;
    for(int i = 0; i < output.size(); i++) {
        sum  += float(exp(output[i]));
    }
    for(int i = 0; i < output.size(); i++){
        output[i] = float(exp(output[i])/sum);
    }
}


void NLayer::Evaluate(std::vector<float> input, std::vector<float> &output, bool LayerType) {
    int inputIndex = 0;
    for(unsigned int i = 0; i < this->totalNeurons; i++){

        float activation = 0.0f;

        for (unsigned int j = 0; j < neurons[i].numInputs; j++)
        {
            activation += input[inputIndex] * neurons[i].weights[j];
            inputIndex++;
        }

        // Add the bias.
        // The bias will act as a threshold value to
        activation += neurons[i].weights[neurons[i].numInputs] * BIAS;


        if(LayerType) { //Hidden Layer = true
            output.push_back(RelU(activation));
            neurons[i].Value = RelU(activation);
        }
        else
            output.push_back(activation);
        inputIndex = 0;
    }
    if(!LayerType){//If it's the output Layer
        SoftMax(output);
    }
}

void NLayer::LoadLayer(std::vector<Neuron> in) {
    totalNeurons = in.size();
    totalInputs = in[0].numInputs;
    neurons = in;
}

void NLayer::PopulateLayer(int numOfNeurons, int numOfInputs) {
    totalInputs = numOfInputs;
    totalNeurons = numOfNeurons;
    this->neurons.resize(numOfNeurons);
    for (unsigned int i = 0; i < neurons.size(); i++)
    {
        neurons[i].Populate(numOfInputs);
    }
}

void NLayer::SetWeights(std::vector<float> weights, int numOfNeurons, int numOfInputs) {
    int index = 0;
    totalInputs = numOfInputs;
    totalNeurons = numOfNeurons;
    this->neurons.resize(numOfNeurons);

    for (unsigned int i = 0; i < numOfNeurons; i++)
    {
        neurons[i].weights.resize(numOfInputs);
        for (unsigned int j = 0; j < numOfInputs; j++)
        {
            neurons[i].weights[j] = weights[index];
            index++;
        }
    }
}

std::vector<float> NLayer::GetWeights()
{
    std::vector<float> out;
    size_t size = 0;
    for (unsigned int i = 0; i < this->totalNeurons; i++)
    {
        size += neurons[i].weights.size();
    }
    out.resize(size);


    for (unsigned int i = 0; i < this->totalNeurons; i++)
    {
        for (unsigned int j = 0; j < neurons[i].weights.size(); j++)
        {
            out[totalInputs * i + j] = neurons[i].weights[j];
        }
    }
    return out;
}

int NLayer::GetNrNeurons() {
    return this->totalNeurons;
}

std::vector<Neuron> NLayer::GetNeurons() {
    return neurons;
}

void NLayer::SetNeurons(std::vector<Neuron> n, int numOfNeurons, int numOfInputs)
{
    totalInputs = numOfInputs;
    totalNeurons = numOfNeurons;
    this->neurons = n;
}