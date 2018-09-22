//GeneticAlgorithms.h
#ifndef _GENALGOH
#define _GENALGOH

#include "NeuralNetwork.h"
#include "Genome.h"
#include "Settings.h"

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

	Genome bestGenome;
	
	void crossover(Genome& g1, Genome& g2);

	void mutate(Genome& g);

	int rouletteWheelSelect(const std::vector<Genome>& pop, int popsize, double totalFitness);
public:
	GeneticAlgorithm(int psize, double mrate, double crate) :
		popSize(psize), mutationRate(mrate), crossoverRate(crate) {};

	void Step(std::vector<Genome>& pop);

	// call after running Step()
	const Genome& getBestGenomeOfGeneration() {
		return bestGenome;
	}
};

#endif
