//  Ann Tupek
//  CS405
//  neural_net.h
//  neural_net
//
//

#ifndef neural_net_neural_net_h
#define neural_net_neural_net_h

#include <vector>
#include <random>
#include <chrono>
#include <cmath>

using std::vector;

class Neuron
{
public:
    int numInputs;
    vector<double> weights;
    int value;
    //ctor
    Neuron(int numInputs);
    Neuron();
    double getValue();
};

class NeuronLayer
{
public:
    int numNeurons;
    vector<Neuron> neuronVec;
    NeuronLayer(int numNeurons, int inputsPerNeuron);
};

class NeuralNet
{
public:
    int numInputs;
    int numOutputs;
    int numLayers;
    int numNeuronsPerLayer;
    vector<NeuronLayer> layerVec;
    NeuralNet();
    void createNet();
    vector<double> getWeights() const;
    int getNumberOfWeights() const;
    vector<double> calculateOutput(vector<double> & inputs);
};

#endif
