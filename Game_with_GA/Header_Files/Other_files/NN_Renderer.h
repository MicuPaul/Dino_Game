#pragma once
#include "stdafx.h"
#include "NeuralNet.h"

struct GLayer
{
    std::vector<sf::Vector2f> neurons_positions;
};

class NN_Renderer{
private:
    sf::RenderWindow window;
    NeuralNet* NN;
    std::vector<float> inputs;
    float neuron_radius;
    float neuron_spacing;
    float layer_spacing;
    sf::Vector2f position;
    std::vector<GLayer> layers;
    void initWindow();

public:
    NN_Renderer();
    NN_Renderer(sf::Vector2f pos);

    float getLayerHeight(int neurons_count);
    void SetInputs(std::vector<float> input_vector);
    void SetNN(NeuralNet* NeuralN);

    void Render();
    void Update();
};
