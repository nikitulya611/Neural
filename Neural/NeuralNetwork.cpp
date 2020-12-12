#include "NeuralNetwork.h"

vector<double> split(std::string s)
{
	vector<double> result;
	if (s.empty())
		return result;

	int begin = 0, end = 0;
	while (begin < s.size())
	{
		auto it = std::find(s.begin() + begin, s.end(), ' ');
		end = std::distance(s.begin(), it);
		result.push_back(stod(s.substr(begin, end - begin)));
		begin = end + 1;
	}
	return result;
}

NeuralNetwork::NeuralNetwork(vector<int>& layers)
{
	neurons = vector< vector<Neuron*> >(layers.size());
	weight = vector< vector<double> >(layers.size());
	bias = vector < vector < double > >(layers.size());
	for (int i = 0; i < layers.size(); i++)
	{
		neurons[i].resize(layers[i]);
		weight[i].resize(layers[i]);
		bias[i].resize(layers[i]);
	}

	for (int i = 0; i < neurons.size(); i++)
		for (int j = 0; j < neurons[i].size(); j++)
			neurons[i][j] = new Neuron();

	srand(time(NULL));
	randMatrix(weight);
	randMatrix(bias);
}

NeuralNetwork::NeuralNetwork(const char* path)
{
	ifstream in(path);
	if (!in.is_open())
		throw "Bad path";

	std::string temp;
	getline(in, temp);
	vector<double> size = split(temp);


	neurons = vector< vector<Neuron*> >(size.size());
	weight = vector< vector<double> >(size.size());
	bias = vector < vector < double > >(size.size());
	for (int i = 0; i < size.size(); i++)
	{
		neurons[i].resize(size[i]);
		weight[i].resize(size[i]);
		bias[i].resize(size[i]);
	}

	for (int i = 0; i < neurons.size(); i++)
	{
		getline(in, temp);
		vector<double> WB = split(temp);
		for (int j = 0; j < neurons[i].size(); j++)
		{
			neurons[i][j] = new Neuron();
			weight[i][j] = WB[j * 2];
			bias[i][j] = WB[j * 2 + 1];
		}
	}

	in.close();
}

double NeuralNetwork::getResult(vector<double>& input)
{
	if (input.size() != neurons[0].size())
		throw "Bad input";

	for (int i = 0; i < neurons[0].size(); i++)
		neurons[0][i]->currValue = input[i];

	for (int i = 1; i < neurons.size(); i++)
	{
		vector<double> values = getVectorOfValues(i - 1);
		for (int j = 0; j < neurons[i].size(); j++)
			neurons[i][j]->currValue = neurons[i][j]->activation_function(scalar(weight[i - 1], values) + bias[i][j]);
	}

	return neurons[neurons.size() - 1][0]->currValue;
}

int NeuralNetwork::HebbsMethod(int steps, vector<vector <double> > input, bool contin, double learning_rate)
{
	int iter = 0;
	for (int currentStep = 0; currentStep < steps; currentStep++)
	{
		vector< vector<double> > previous(weight);

		for (int currentInput = 0; currentInput < input.size(); currentInput++)
		{
			double result = getResult(input[currentInput]);
			for(int i = 1; i < neurons.size(); i++)
				for (int j = 0; j < neurons[i].size(); j++)
				{
					weight[i][j] = previous[i][j] + learning_rate * neurons[i-1][j]->currValue * neurons[i][j]->currValue;
					iter++;
				}
		}
	}

	return iter;
}

void NeuralNetwork::save(const char* path)
{
	ofstream out(path);
	for (int i = 0; i < weight.size(); i++)
		out << weight[i].size() << ' ';
	out << '\n';

	for (int i = 0; i < weight.size(); i++)
	{
		for (int j = 0; j < weight[i].size(); j++)
			out << weight[i][j] << ' ' << bias[i][j] << ' ';
		out << '\n';
	}
	out.close();
}

vector<double> NeuralNetwork::getVectorOfValues(int lay)
{
	vector<double> result(neurons[lay].size());
	for (int i = 0; i < result.size(); i++)
		result[i] = neurons[lay][i]->currValue;
	return result;
}

void NeuralNetwork::randMatrix(vector<vector<double>>& v)
{
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v[i].size(); j++)
			v[i][j] = (rand() % 7 - 3) / 10.0;
}
