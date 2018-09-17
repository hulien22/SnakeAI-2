#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork() {
    
}

NeuralNetwork::NeuralNetwork(int i, int o, int h, int nph) : inputs(i), outputs(o), hiddenLayers(h), neuronsPerHidLayer(nph) {
    
}

std::vector<double> NeuralNetwork::GetWeights() const {

}

int NeuralNetwork::GetNumWeights() const {
    
}

void NeuralNetwork::SetWeights(const std::vector<std::vector<std::vector<double>>> &weights) {
    
}

std::vector<double> Step(const std::vector<double> &inputs) {

}



