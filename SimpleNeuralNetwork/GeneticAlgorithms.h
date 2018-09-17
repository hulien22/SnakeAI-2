//GeneticAlgorithms.h
#ifndef _GENALGOH
#define _GENALGOH

#include "NeuralNetwork.h"

class GeneticAlgorithms {
	NeuralNetwork nnet;
	

public:
	GeneticAlgorithms(int double cr, double mr,  );	

	NeuralNetwork crossover(const NeuralNetwork& nnet1, const NeuralNetwork& nnet2, double probability);

	NeuralNetwork mutate(const NeuralNetwork& nnet);


}

#endif
