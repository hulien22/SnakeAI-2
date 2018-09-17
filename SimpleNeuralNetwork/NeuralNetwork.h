//NeuralNetwork.h
#ifndef _NNETH
#define _NNETH

#include "NeuralLayer.h"
#include <vector>
#include <algorithm>

class NeuralNetwork {
	int inputs;
	int outputs;
	int hiddenLayers;
	int neuronsPerHidLayer;

	std::vector<NeuralLayer> vecLayers;
public:
	NeuralNetwork();

	NeuralNetwork(int i, int o, int h, int nph);

	// void CreateNetwork();

	std::vector<double> GetWeights() const;

	int GetNumWeights() const;

	void SetWeights(const std::vector<std::vector<std::vector<double>>> &weights);

	std::vector<double> Calculate(const std::vector<double> &inputs);

	inline double Sigmoid(double activation, double response)
	{
		return (1 / (1 + exp(-activation / response)));
	}
	inline double ReLU(double activation, double response)
	{
		return std::max(activation / response, 0.0);
	}


};



#endif
