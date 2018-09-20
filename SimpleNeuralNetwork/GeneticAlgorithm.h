//GeneticAlgorithms.h
#ifndef _GENALGOH
#define _GENALGOH

// define macros
#define MUTATION_RATE 0.2
#define CROSSOVER_RATE 0.7
#define ELITISM_RATE 0.5

#include "NeuralNetwork.h"
#include "Genome.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

class GeneticAlgorithm {
	int generation;

	int popSize;
	int chromosomeLength;
	double mutationRate;
	double crossoverRate;

	double bestFitness;
	
	void crossover(Genome& g1, Genome& g2);

	void mutate(Genome& g);

	int rouletteWheelSelect(const std::vector<Genome>& pop, int popsize, double totalFitness);
public:
	GeneticAlgorithm(int psize, double mrate, double crate) :
		popSize(psize), mutationRate(mrate), crossoverRate(crate) {};

	void Step(std::vector<Genome>& pop);

};

#endif
