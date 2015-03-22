//  Ann Tupek
//  CS405
//  main.cpp
//  neural_net
//
//

#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <cmath>
#include <ctime>
#include "neural_net.h"
using std::vector;
using std::mt19937;
using std::cout;
using std::endl;
using std::mt19937;
using std::random_device;

double sigmoid(double x);
void mutate(vector <double> weights);

const int SIZE_OF_LAYER1 = 32;
const int SIZE_OF_LAYER2 = 40;
const int SIZE_OF_LAYER3 = 10;
const int SIZE_OF_LAYER4 = 1;

int main()
{

    //Construct Neural Net
    //Yes, I know I should do this in my Neural Net class,
    //but I'm on a time crunch since I've decided rid the world of my middle class...
    vector<Neuron> layer1;
    vector<Neuron> layer2;
    vector<Neuron> layer3;
    vector<Neuron> layer4;
    //for first layer of 32
    for (auto i=0; i<SIZE_OF_LAYER1; i++)
    {
        layer1.push_back(Neuron());
    }
    //for second layer of 40
    for (auto i=0; i<SIZE_OF_LAYER2; i++)
    {
        layer2.push_back(Neuron());
    }
    //for third layer of 10
    for (auto i=0; i<SIZE_OF_LAYER3; i++)
    {
        layer3.push_back(Neuron());
    }
    //for last layer of one
    for (auto i=0; i<SIZE_OF_LAYER4; i++)
    {
        layer4.push_back(Neuron());
    }
    //timing...
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for (auto i=0; i<1000; i++)
    {
    //sum up values of each neuron in layer1
    vector<double> output1;
    for (auto i=0; i<SIZE_OF_LAYER1; i++)
    {
        double sumInput=0;
            {
                sumInput += layer1[i].weights[i] * layer1[i].getValue();
                sumInput = sigmoid(sumInput);
            }
            output1.push_back(sumInput);

    }
        //sum up values of each neuron in layer2
        vector<double> output2;
        for (auto i=0; i<SIZE_OF_LAYER2; i++)
        {
            double sumInput=0;
            {
                sumInput += layer2[i].weights[i] * layer2[i].getValue();
                sumInput = sigmoid(sumInput);
            }
            output2.push_back(sumInput);
            
        }
        //sum up values of each neuron in layer3
        vector<double> output3;
        for (auto i=0; i<SIZE_OF_LAYER3; i++)
        {
            double sumInput=0;
            {
                sumInput += layer3[i].weights[i] * layer3[i].getValue();
                sumInput = sigmoid(sumInput);
            }
            output3.push_back(sumInput);
            
        }
        //sum up values of each neuron in layer4
        vector<double> output4;
        for (auto i=0; i<SIZE_OF_LAYER4; i++)
        {
            double sumInput=0;
            {
                sumInput += layer4[i].weights[i] * layer4[i].getValue();
                sumInput = sigmoid(sumInput);
            }
            output4.push_back(sumInput);
            
        }
    }
    //end timing stuff
    //more timing...
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout<< endl << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    return 0;
}

//sigmoid function
double sigmoid (double x)
{
    double output = 0;
    output = 1/(1+exp(x));
    return output;
}

//mutator function
void mutate (vector<double> weights)
{
    random_device rd;
    mt19937 generator(rd());
    std::uniform_real_distribution<> distribution(-.1,.1);
    for (auto i=0; i<weights.size(); i++)
    {
        weights[i]+=(distribution(generator));
    }
}
