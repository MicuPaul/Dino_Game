#include "NN_Renderer.h"

void NN_Renderer::initWindow() {
    this->window.create(sf::VideoMode(600, 350), "Best Dino NN", sf::Style::Titlebar);
    this->window.setFramerateLimit(60);
}

NN_Renderer::NN_Renderer() {
    this->initWindow();
    this->NN = nullptr;
    this->neuron_radius = 14.0f;
    this->neuron_spacing = 6.0f;
    this->layer_spacing = 85.0f;
    this->inputs.clear();
    this->layers.clear();
    this->position.x = 0;
    this->position.y = 0;
}

NN_Renderer::NN_Renderer(sf::Vector2f pos){
    this->initWindow();
    this->NN = nullptr;
    this->neuron_radius = 14.0f;
    this->neuron_spacing = 6.0f;
    this->layer_spacing = 85.0f;
    this->inputs.clear();
    this->layers.clear();
    this->position = pos;
}

void NN_Renderer::Render() {
    this->window.clear(sf::Color::Black);

    this->Update();

    const int layers_count = layers.size();
    for(int i = 1; i < layers_count; ++i){
        const GLayer curr_layer = layers[i];
        const GLayer prev_layer = layers[i-1];
        unsigned int neuron_id = 0;
        for (const sf::Vector2f& neuron_pos : curr_layer.neurons_positions) {
            unsigned int weight_id = 0;
            for (const sf::Vector2f& prev_neuron_pos : prev_layer.neurons_positions) {
                const float link_weight = (i == layers_count - 1 ? this->NN->GetOutputLayer() : this->NN->GetHiddenLayers()[i - 1])->GetWeights()[weight_id];
                float link_value = 0.f;
                if(i == 1)
                    link_value = link_weight * inputs[weight_id];
                else link_value = link_weight * this->NN->GetHiddenLayers()[i-2]->GetNeurons()[weight_id].Value;
                const sf::Color link_color = link_value > 0.0f ? sf::Color(0, 128, 0) : sf::Color(128, 0, 0);
                const float link_width = 2.0f * log2(1.0f + std::abs(link_value));
                this->window.draw(getLine(neuron_pos, prev_neuron_pos, link_width, link_color));
                ++weight_id;
            }
            ++neuron_id;
        }

        unsigned int layer_id = 0;
        for (GLayer& layer : layers) {
            neuron_id = 0;
            for (const sf::Vector2f& pos : layer.neurons_positions) {
                const sf::Vector3f base_color(0, 0,0);
                const sf::Vector3f activated_color(0,128,0);

                sf::Color neuron_color;
                float current_neuron_radius = neuron_radius;
                float intensity = 0.0f;

                if (!layer_id) {
                    intensity = std::min(1.0f, 2.0f * std::abs(inputs[neuron_id]));
                }
                else if (layer_id == layers_count - 1) {
                    intensity = this->NN->GetOutput(neuron_id);
                }
                else {
                    intensity = this->NN->GetHiddenLayers()[layer_id - 1]->GetNeurons()[neuron_id].Value;
                    current_neuron_radius = neuron_radius * 0.8f;
                }

                sf::Vector3f color_vec = intensity * activated_color + (1.0f - intensity) * base_color;
                neuron_color = toColor(color_vec);

                sf::CircleShape neuron_shape(current_neuron_radius);
                neuron_shape.setOrigin(current_neuron_radius, current_neuron_radius);
                neuron_shape.setPosition(pos);
                neuron_shape.setFillColor(neuron_color);
                this->window.draw(neuron_shape);
                ++neuron_id;
            }
            ++layer_id;
        }
    }

    this->window.display();

}

float NN_Renderer::getLayerHeight(int neurons_count)
{
    return neurons_count * (2.0f * neuron_radius + neuron_spacing);
}

void NN_Renderer::SetInputs(std::vector<float> input_vector) {
    this->inputs = input_vector;
}

void NN_Renderer::SetNN(NeuralNet *NeuralN) {
    this->NN = NeuralN;
}

void NN_Renderer::Update() {
    this->layers.clear();

    float max_layer_height = getLayerHeight(this->inputs.size());
    for (NLayer* layer : this->NN->GetHiddenLayers()) {
        float layer_height = getLayerHeight(layer->GetNrNeurons());
        if (layer_height > max_layer_height) {
            max_layer_height = layer_height;
        }
    }

    //INPUT LAYER
    float layer_x = this->position.x;
    float layer_height = getLayerHeight(this->inputs.size());
    float neuron_y = position.y + 0.5f * (max_layer_height - layer_height) + neuron_radius;

    layers.emplace_back();
    for (int i = 0; i < inputs.size(); ++i) {
        layers.back().neurons_positions.push_back(sf::Vector2f(layer_x, neuron_y));
        neuron_y += 2.0f * neuron_radius + neuron_spacing;
    }
    layer_x += 2.0f * neuron_radius + layer_spacing;

    //HIDDEN LAYERS
    for (NLayer* layer : this->NN->GetHiddenLayers()) {
        layers.emplace_back();
        layer_height = getLayerHeight(layer->GetNrNeurons());
        neuron_y = position.y + 0.5f * (max_layer_height - layer_height) + neuron_radius;
        for (int i = 0; i < layer->GetNrNeurons(); ++i) {
            layers.back().neurons_positions.push_back(sf::Vector2f(layer_x, neuron_y));
            neuron_y += 2.0f * neuron_radius + neuron_spacing;
        }

        layer_x += 2.0f * neuron_radius + layer_spacing;
    }

    //OUTPUT LAYER

    layer_x += 2.0f * neuron_radius + layer_spacing;
    layers.emplace_back();
    layer_height = getLayerHeight(this->NN->GetOutputLayer()->GetNrNeurons());
    neuron_y = position.y + 0.5f * (max_layer_height - layer_height) + neuron_radius;
    for (int i = 0; i < this->NN->GetOutputLayer()->GetNrNeurons(); ++i) {
        layers.back().neurons_positions.push_back(sf::Vector2f(layer_x, neuron_y));
        neuron_y += 2.0f * neuron_radius + neuron_spacing;
    }

}

