#include "Genetic_Algorithm.h"

void Genetic_Algorithm::initNNRenderer() {
    sf::Vector2f pos;
    pos.x = 20;
    pos.y = 10;
    this->NN_Visualizer = new NN_Renderer(pos);
}

Genetic_Algorithm::Genetic_Algorithm(){
    this->initNNRenderer();
    this->SelectBestTimer = 0;
    this->SelectedBestIndex = -1;
    this->Selected_Best = false;
    this->totalPopulation = MAX_POPULATION;
    this->NR_HIDDEN_LAYERS = 3;
    this->NR_NEURONS_PER_LAYER = 10;
    this->totalGenomeWeights = NR_OF_INPUTS*NR_NEURONS_PER_LAYER + (NR_HIDDEN_LAYERS - 1)*NR_NEURONS_PER_LAYER*NR_NEURONS_PER_LAYER + NR_OF_OUTPUTS*NR_NEURONS_PER_LAYER + NR_HIDDEN_LAYERS*NR_NEURONS_PER_LAYER + NR_OF_OUTPUTS;
    generation = 1;
}

Genetic_Algorithm::~Genetic_Algorithm() {
    this->ClearPopulation();
    for (unsigned int i = 0; i < population.size(); i++){
        if (dinos[i] != nullptr){
            delete dinos[i];
            dinos[i] = nullptr;
        }
    }
    dinos.clear();
}

void Genetic_Algorithm::ClearPopulation()
{
    for (unsigned int i = 0; i < population.size(); i++){
        if (population[i] != nullptr){
            delete population[i];
            population[i] = nullptr;
        }

    }

    population.clear();
}

unsigned int Genetic_Algorithm::GetBestIndex() {
    int bestIndex = 0;
    float fitness = 0;


    for (unsigned int i = 0; i < population.size(); i++)
    {
        if (population[i]->fitness > fitness && !this->dinos[i]->HasFailed())
        {
            fitness = population[i]->fitness;
            bestIndex = i;
        }
    }


    return bestIndex;
}

Genome *Genetic_Algorithm::GetWorstGenome() {
    int worstGenome = -1;
    float fitness = 1000000;
    for (unsigned int i = 0; i < population.size(); i++)
    {
        if (population[i]->fitness < fitness)
        {
            fitness = population[i]->fitness;
            worstGenome = i;
        }
    }

    return population[worstGenome];
}

Genome *Genetic_Algorithm::GetGenome(int index) {
    if (index >= totalPopulation)
        return NULL;

    return population[index];
}

Dino *Genetic_Algorithm::GetDino(int index) {
    if (index >= totalPopulation)
        return NULL;

    return dinos[index];
}

int Genetic_Algorithm::GetTotalPopulation() const {
    return this->totalPopulation;
}

int Genetic_Algorithm::GetDinosAlive() const {
    int dinos_alive = 0;
    for(unsigned int i = 0; i < this->totalPopulation; i++){
        if(!this->dinos[i]->HasFailed()){
            dinos_alive++;
        }
    }
    return dinos_alive;
}


void Genetic_Algorithm::GetBestCases(std::vector<Genome *> &out) {
    int genomeCount = 0;
    int runCount = 0;

    while (genomeCount < MAX_POPULATION)
    {
        if (runCount > 30)
            return;

        runCount++;

        float bestFitness = 0;
        int bestIndex = -1;
        for (unsigned int i = 0; i < this->totalPopulation; i++)
        {
            if (population[i]->fitness > bestFitness)
            {
                bool isUsed = false;

                for (unsigned int j = 0; j < out.size(); j++)
                {
                    if (out[j]->ID == population[i]->ID) {
                        isUsed = true;
                    }
                }

                if (!isUsed)
                {
                    bestIndex = i;
                    bestFitness = population[bestIndex]->fitness;
                }
            }
        }

        if (bestIndex != -1)
        {
            genomeCount++;
            out.push_back(population[bestIndex]);
        }

    }
}

Genome* Genetic_Algorithm::CreateNewGenome(unsigned int totalWeights) {
    Genome* genome = new Genome();
    genome->fitness = 0.0f;
    genome->weights.resize(totalWeights);
    for (unsigned int j = 0; j < totalWeights; j++)
    {
        genome->weights[j] = RandomClamped();
    }

    return genome;
}

void Genetic_Algorithm::setDinosScore(unsigned int score) {
    for(unsigned int i = 0; i < this->totalPopulation; i++){
        if(!this->dinos[i]->HasFailed()){
            this->dinos[i]->setScore(score);
        }
    }
}

void Genetic_Algorithm::setDinosInputs(std::vector<float> inputs) {
    for(unsigned int i = 0; i < this->totalPopulation; i++){
        if(!this->dinos[i]->HasFailed()){
            inputs[9] = (162.4f - this->dinos[i]->getGlobalBounds().top) / 162.4f;
            this->dinos[i]->setInputs(inputs);
        }
    }
}

void Genetic_Algorithm::attachNNtoDinos() {
    for (unsigned int i = 0; i < population.size(); i++){
        NeuralNet* NN = new NeuralNet();
        this->population[i]->ID = i;
        NN->FromGenome(*this->population[i], NR_OF_INPUTS, this->NR_NEURONS_PER_LAYER, NR_OF_OUTPUTS, this->NR_HIDDEN_LAYERS);
        this->dinos[i]->Attach(NN);
    }
}

bool Genetic_Algorithm::checkIfDinosFailed() {
    for (unsigned int i = 0; i < population.size(); i++) {
        if(!this->dinos[i]->HasFailed())
            return false;
    }
    return true;
}

unsigned int Genetic_Algorithm::calculateScoresum() {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < population.size(); i++) {
        sum += this->dinos[i]->getScore();
    }
    return sum;
}

void Genetic_Algorithm::GenerateNewPopulation() {
    std::vector<float> weights;
    bool can_read = true;
    this->ClearPopulation();

    std::ifstream rf("/home/alexpail/Documents/Dino_Game/Game_with_GA/Saved_Generation.dat", std::ios::out | std::ios::binary);
    if (!rf) {
        std::cout << "Cannot open NN binary file!" << std::endl;
        can_read = false;
    }
    else{
        rf.read((char *)&this->generation, sizeof(int));
        rf.read((char *)&this->NR_HIDDEN_LAYERS, sizeof(int));
        rf.read((char *)&this->NR_NEURONS_PER_LAYER, sizeof(int));
        rf.read((char *)&this->totalGenomeWeights, sizeof(int));
    }

    population.resize(this->totalPopulation);
    for (unsigned int i = 0; i < population.size(); i++)
    {
        Genome* genome = new Genome();
        Dino* dino = new Dino();
        genome->ID = i;
        genome->fitness = 0.0f;
        genome->weights.resize(this->totalGenomeWeights);
        weights.clear();
        for (unsigned int j = 0; j < this->totalGenomeWeights; j++)
        {
            if(!can_read){
                genome->weights[j] = RandomClamped();
            }
            else{
                rf.read((char * ) &genome->weights[j], sizeof(float));
            }
        }
        population[i] = genome;
        this->dinos.push_back(dino);
    }

    this->attachNNtoDinos();
}

void Genetic_Algorithm::CrossBreed(Genome* g1, Genome* g2, Genome* &baby1, Genome* &baby2)
{
    // Select a random crossover point
    unsigned int totalWeights = g1->weights.size();
    unsigned int crossover = rand() % totalWeights;

    baby1 = new Genome();
    baby1->weights.resize(totalWeights);

    baby2 = new Genome();
    baby2->weights.resize(totalWeights);

    // Go from start to crossover point, copying the weights from g1.
    for (unsigned int i = 0; i < crossover; i++)
    {
        baby1->weights[i] = g1->weights[i];
        baby2->weights[i] = g2->weights[i];
    }
    // Go from start to crossover point, copying the weights from g2 to child.
    for (unsigned int i = crossover; i < totalWeights; i++)
    {
        baby1->weights[i] = g2->weights[i];
        baby2->weights[i] = g1->weights[i];
    }
}


void Genetic_Algorithm::BreedPopulation()
{
    std::vector<Genome*> bestGenomes;

    this->GetBestCases(bestGenomes);

    std::vector<Genome*> children;

    for(int i = 0; i < bestGenomes.size(); i++){
        Genome* bestDude = new Genome();
        bestDude->fitness = 0.0f;
        bestDude->weights = bestGenomes[i]->weights;
        Mutate(bestDude);
        children.push_back(bestDude);
    }

    Genome* baby1 = nullptr;
    Genome* baby2 = nullptr;


    for(int i = 0; i <= 15; i++){
        for(int j = i + 1; j <= 15; j++){
            this->CrossBreed(bestGenomes[i], bestGenomes[j], baby1, baby2);
            this->Mutate(baby1);
            this->Mutate(baby2);
            children.push_back(baby1);
            children.push_back(baby2);
        }
    }

    unsigned int remainingChildren = (totalPopulation - children.size());
    for (unsigned int i = 0; i < remainingChildren; i++){
        Genome* genome = CreateNewGenome(this->totalGenomeWeights);
        children.push_back(genome);
    }


    this->ClearPopulation();

    population = children;


    for (unsigned int i = 0; i < this->totalPopulation; i++)
    {
        this->dinos[i]->resetDino();
    }
    this->attachNNtoDinos();

    this->generation++;
    this->SelectedBestIndex = 0;
    this->Selected_Best = false;
    this->SelectBestTimer = 0;

    std::ofstream wf("/home/alexpail/Documents/Dino_Game/Game_with_GA/Saved_Generation.dat", std::ios::out | std::ios::binary);

    if (!wf) {
        std::cout << "Cannot open NN binary file!" << std::endl;
    }

    wf.write((char *)&this->generation, sizeof(int));
    wf.write((char *)&this->NR_HIDDEN_LAYERS, sizeof(int));
    wf.write((char *)&this->NR_NEURONS_PER_LAYER, sizeof(int));
    wf.write((char *)&this->totalGenomeWeights, sizeof(int));
    for(int j = 0; j < this->totalPopulation; j++)
        for(int k = 0; k < this->totalGenomeWeights; k++)
            wf.write((char * ) & this->population[j]->weights[k], sizeof(float));

    wf.close();
}

void Genetic_Algorithm::Mutate(Genome* genome)
{
    for (unsigned int i = 0; i < genome->weights.size(); ++i)
    {
        // Generate a random chance of mutating the weight in the genome.
        if (RandomFloat() < MUTATION_RATE)
        {
            genome->weights[i] += (RandomClamped() * MAX_PERBETUATION);
        }
    }
}

void Genetic_Algorithm::SetGenomeFitness(float fitness, int index)
{
    if (index >= population.size())
        return;

    population[index]->fitness = fitness;
}

void Genetic_Algorithm::updateDinos(Tile* closest_obstacle) {
    for(int i = 0; i < this->totalPopulation; i++){
        if(!this->dinos[i]->HasFailed())
            this->dinos[i]->update(closest_obstacle);
    }

    this->SelectBestTimer += 1;

    if(SelectBestTimer == 240) { // 4 seconds
        this->SelectBestTimer = 0;
        this->SelectedBestIndex = this->GetBestIndex();
        this->Selected_Best = true;
    }

    if(this->Selected_Best){
        this->NN_Visualizer->SetInputs(this->dinos[this->SelectedBestIndex]->GetNeuralNet()->GetInputs());
        this->NN_Visualizer->SetNN(this->dinos[this->SelectedBestIndex]->GetNeuralNet());
        this->NN_Visualizer->Update();
    }


}

void Genetic_Algorithm::renderInfo(sf::RenderTarget &target, unsigned int score) {

    sf::Text GA_Info;
    std::ostringstream ss; //string buffer to convert numbers to string
    ss << "Generation: " << this->generation << "\nAlive: " << this->GetDinosAlive() << "\nScore: " << score;
    sf::Font font;
    if (!font.loadFromFile("/home/alexpail/Documents/Dino_Game/Game_with_GA/Spritesheet/Arial.ttf"))
    {
        std::cout << "ERROR: Could not load Font!";
    }
    GA_Info.setCharacterSize(14);
    GA_Info.setFont(font);
    GA_Info.setStyle(sf::Text::Bold);
    GA_Info.setFillColor(sf::Color::Black);
    GA_Info.setPosition(425,0);
    GA_Info.setString(ss.str());

    target.draw(GA_Info);
}

void Genetic_Algorithm::render(sf::RenderTarget &target,  unsigned int score, bool gamestate) {

    this->renderInfo(target, score);
    for(int i = 0; i < this->totalPopulation; i++){
        if(!this->dinos[i]->HasFailed())
            this->dinos[i]->render(target);
    }
    if(this->Selected_Best && gamestate)
        this->NN_Visualizer->Render();

}