#pragma once

#include "Neuron.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

inline double lossFunction(vector<double> prediction, vector<double> real)
{
	double result = 0;
	for (int i = 0; i < real.size(); i++)
		result += pow(prediction[i] - real[i], 2);
	return result * 0.5;
}

class NeuralNetwork
{
public:
	NeuralNetwork() = delete;
	NeuralNetwork(vector<int>& layers);
	NeuralNetwork(const char* path);

	double getResult(vector<double>& input);
	int HebbsMethod(int steps, vector<vector <double> > input, bool contin = false, double learning_rate = 0.05);//возвращает общее кол-во итераций

	void save(const char* path);

private:
	vector< vector<Neuron*> > neurons;
	vector< vector<double> > weight;
	vector< vector<double> > bias;

	vector<double> getVectorOfValues(int lay);
	void randMatrix(vector< vector<double> >& v);
};