#include "SimpleNeuralNetwork/Settings.h"
#include "SimpleNeuralNetwork/GeneticAlgorithm.h"
#include "Snake/game.h"

#include <fstream>
#include <string>

#include <Windows.h>

void runGame(std::string file) {
    // initialize random seed
    srand (time(NULL));
    Game game = Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
    NeuralNetwork nnet = NeuralNetwork(NUMBER_OF_INPUTS,NUMBER_OF_OUTPUTS,HIDDEN_LAYERS,HIDDEN_LAYER_SIZE);

    // get weights from file, file must be formatted as space separated doubles
    std::vector<double> weights(nnet.GetNumWeights());
    double d;
    std::ifstream fs(file);
    while (fs.is_open()) {
        for (size_t i=0; i<weights.size(); ++i) {
            fs >> d;
            weights[i] = d;
        }
        fs.close();
    }

    nnet.SetWeights(weights);

    int facing = 0;
    int steps = 0;
    do {
        Sleep(50);
        std::cout << game.toString() << "total steps: " << steps++ << " | size: " << game.getSize() << std::endl;
        std::vector<double> outputs = nnet.Calculate(game.getInputVector());
        facing = game.getFacing();
        // 3 outputs
        if (outputs[0] > outputs[1] && outputs[0] > outputs[2]) {
            ++facing; //turn left
        } else if (outputs[2] > outputs[0] && outputs[2] > outputs[1]) {
            --facing; //turn right
        } //else go straight
        facing = (facing % 4 + 4) % 4;
    }
    while (game.move(facing));

    std::cout << game.toString() << "total steps: " << steps++ << " | size: " << game.getSize() << std::endl;
    
    std::cout << "game over." << std::endl;
}

void trainNnet() {
    // initialize random seed
    srand (time(NULL));

    Game game = Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
    GeneticAlgorithm ga = GeneticAlgorithm(POPULATION_SIZE,MUTATION_RATE,CROSSOVER_RATE);
    NeuralNetwork nnet = NeuralNetwork(NUMBER_OF_INPUTS,NUMBER_OF_OUTPUTS,HIDDEN_LAYERS,HIDDEN_LAYER_SIZE);
    
    std::ofstream fs;

    // create initial genomes
    std::vector<Genome> genomes;
    std::vector<double> randWeights = nnet.GetWeights();

    for (int i=0; i<POPULATION_SIZE; ++i) {
        for (size_t j=0; j < randWeights.size(); ++j) {
            randWeights[j] = ((double) std::rand() / (RAND_MAX)) * 2 - 1;
        }
        genomes.emplace_back(randWeights,0);
    }

    // learning cycle
    int i = 0;
    int f = 0;
    while (f < TARGET_FITNESS) {
        std::cout << "#########################################" << std::endl;
        std::cout << "Starting Generation " << i << "." << std::endl;
        std::cout << "#########################################" << std::endl;

        // run each genome through the game to get their fitness scores
        for (int j=0; j<POPULATION_SIZE; ++j) {
            // std::cout << "*****************************************" << std::endl;
            // std::cout << "Training Species " << j << " of Generation " << i << "." << std::endl;
            double fitnessAverage = 0;
            nnet.SetWeights(genomes[j].getWeights());

            // we will run each genome through the game multiple times and take an average fitness
            for (int k=0; k<GAME_REPEATS; ++k) {
                int steps = 0, totalSteps = 0, facing = 0, size = INITIAL_SNAKE_SIZE;
                bool validMove, loop = true;
                std::vector<double> outputs(NUMBER_OF_OUTPUTS);

                game.reset(INITIAL_SNAKE_SIZE);

                while (loop) {
                    outputs = nnet.Calculate(game.getInputVector());
                    facing = game.getFacing();
                    // 3 outputs
                    if (outputs[0] > outputs[1] && outputs[0] > outputs[2]) {
                        ++facing; //turn left
                    } else if (outputs[2] > outputs[0] && outputs[2] > outputs[1]) {
                        --facing; //turn right
                    } //else go straight
                    facing = (facing % 4 + 4) % 4;
                    validMove = game.move(facing);
                    ++steps;

                    if (!validMove) {
                        fitnessAverage += (game.getSize() - INITIAL_SNAKE_SIZE) * (game.getSize() - INITIAL_SNAKE_SIZE) ;
                        loop = false;
                    } else {
                        if (game.getSize() > size) {
                            totalSteps += steps;
                            steps = 0;
                            ++size;
                        }
                        if (steps >= 100) loop = false; //not going anywhere, kill genome
                    }
                }
            }

            genomes[j].setFitness(fitnessAverage/(GAME_REPEATS * 1.0));

            // std::cout << "Fitness Score: " << genomes[j].getFitness() << " | Genome took " << totalSteps + steps << " steps, and grew to a size of " << size << std::endl;
            // std::cout << "*****************************************" << std::endl;
        }

        // now use ga to calculate next generation
        ga.Step(genomes);
        Genome bestGenome = ga.getBestGenomeOfGeneration();

        //save best genome to file
        std::vector<double> bestweights = bestGenome.getWeights();
        fs.open("out.txt", std::ios::app);
        fs << bestGenome.getFitness() << "| ";
        for (size_t j=0; j<bestweights.size(); ++j) {
            fs << bestweights[j] << " ";
        }
        fs << "\n";
        fs.close();

        std::cout << "#########################################" << std::endl;
        std::cout << "Generation " << i << " completed." << std::endl;
        std::cout << "Best fitness: " << bestGenome.getFitness() << std::endl;
        std::cout << "#########################################" << std::endl;

        ++i;
        f = bestGenome.getFitness();
    }

    //save all genomes to file
    fs.open("final_out.txt", std::ios::app);
    for (int i=0; i<POPULATION_SIZE; ++i) {
        std::vector<double> w = genomes[i].getWeights();
        for (size_t j=0; j<w.size(); ++j) {
            fs << w[j] << " ";
        }
        fs << "\n";
    }
    fs.close();
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        runGame(argv[1]);
    } else {
        trainNnet();
    }
}


