#include "GeneticAlgorithm.h"


// TODO: may want to try a different crossover algorithm??
void GeneticAlgorithm::crossover(Genome& g1, Genome& g2) {
    double r = ((double) rand() / RAND_MAX);
    if (r > crossoverRate) return;

    std::vector<double> weights1 = g1.getWeights();
    std::vector<double> weights2 = g2.getWeights();


    int cut = rand()%chromosomeLength;
    for (size_t i=cut; i<weights1.size(); ++i) {
        std::swap(weights1[i],weights2[i]);
    }
}

void GeneticAlgorithm::mutate(Genome& g) {
    std::vector<double> weights = g.getWeights();
    for (size_t i=0; i<weights.size(); ++i) {
        double r = ((double) rand() / RAND_MAX);
        if (r < mutationRate)
            weights[i] += ((double) rand() / RAND_MAX) * 2 - 1; // -1 to 1
    }
}

int GeneticAlgorithm::rouletteWheelSelect(const std::vector<Genome>& pop, int popsize, double totalFitness) {
    double targetFitness = (double) (((double) rand() / RAND_MAX) * popsize);

    for (int i=0; i<popsize; ++i) {
        targetFitness -= pop[i].getFitness();
        if(targetFitness < 0) return i;
    }

    return popsize - 1;
}

void GeneticAlgorithm::Step(std::vector<Genome>& pop) {
    std::sort(pop.begin(), pop.end());
    size_t popsize = pop.size();

    //TODO: calculate stats here from previous generation
    bestGenome = pop.back();

    // kill off percentage of population
    pop.erase(pop.begin(), pop.begin() + floor(popsize * ELITISM_RATE));

    // repopulate
    // going to do roulette wheel selection method
    // first find total fitness
    double totalFitness = 0;
    int reducedPopSize = pop.size();
    for (int i=0; i<reducedPopSize; ++i) {
        totalFitness += pop[i].getFitness();
    }

    while (pop.size() < popsize) {
        int g1 = rouletteWheelSelect(pop, reducedPopSize, totalFitness);
        int g2 = rouletteWheelSelect(pop, reducedPopSize, totalFitness);
        
        pop.push_back(Genome(pop[g1]));
        pop.push_back(Genome(pop[g2]));
        
        crossover(pop[pop.size()-2], pop[pop.size()-1]);
        mutate(pop[pop.size()-2]);
        mutate(pop[pop.size()-1]);
    }
    while (pop.size() > popsize) pop.pop_back();
}

