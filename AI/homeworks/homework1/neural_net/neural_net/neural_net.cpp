//  Ann Tupek
//  CS405
//  neural_net.cpp
//  neural_net
//
//

#include "neural_net.h"
#include <random>
using std::mt19937;
using std::random_device;

//create neuron
Neuron::Neuron(int numInputs): numInputs(numInputs)
{
    random_device rd;
    mt19937 generator(rd());
    std::uniform_real_distribution<> distribution(-1.0,1.0);
    for (auto i=0; i<numInputs; i++)
    {
        weights.push_back(distribution(generator));
    }
}

Neuron::Neuron()
{
    random_device rd;
    mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(-1.0, 1.0);
    weights.push_back(distribution(generator));
}

double Neuron::getValue()
{
    return value;
}

//create layer of neurons
NeuronLayer::NeuronLayer(int numNeurons, int inputsPerNeuron): numNeurons(numNeurons)
{
    for (auto i=0; i<numNeurons; i++)
    {
        neuronVec.push_back(Neuron(inputsPerNeuron));
    }
}

//create neural net
NeuralNet::NeuralNet()
{
    createNet();
}

//create neural net
void NeuralNet::createNet()
{
    layerVec.push_back(NeuronLayer(numNeuronsPerLayer, numInputs));
    for (auto i=0; i<numLayers-1; i++)
    {
        layerVec.push_back(NeuronLayer(numNeuronsPerLayer, numNeuronsPerLayer));
    }
    
    layerVec.push_back(NeuronLayer(numOutputs, numNeuronsPerLayer));
}


vector<double> NeuralNet::getWeights()const
{
    vector<double> weights;
    for (auto i=0; i<numLayers; i++)
    {
        for (auto j=0; j<layerVec[i].numNeurons; j++)
        {
            for (auto k=0; k<layerVec[i].neuronVec[j].numInputs; k++)
            {
                weights.push_back(layerVec[i].neuronVec[j].weights[k]);
            }
        }
    }
    return weights;
}

int NeuralNet::getNumberOfWeights() const
{
    int weights = 0;
    for (auto i=0; i<numLayers; i++)
    {
        for (auto j=0; j< layerVec[i].numNeurons; j++)
        {
            for (auto k=0; k<layerVec[i].neuronVec[j].numInputs; k++)
            {
                weights++;
            }
        }
    }
    return weights;
}

vector<double> NeuralNet::calculateOutput(vector<double> &inputs)
{
    int c=0;
    vector<double> outputs;
    for (auto i=0; i<numLayers; i++)
    {
        inputs = outputs;
        for (auto j=0; j<layerVec[i].numNeurons; j++)
        {
            double sumInput=0;
            int numInputs=layerVec[i].neuronVec[j].numInputs;
            for (auto k=0; k<numInputs; k++)
            {
                sumInput += layerVec[i].neuronVec[j].weights[k] * inputs[c];
            }
            outputs.push_back(sumInput);
        }
    }
    return outputs;
}






























