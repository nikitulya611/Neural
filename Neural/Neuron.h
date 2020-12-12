#pragma once

#include <cmath>
#include <vector>

using std::vector;

inline double scalar(vector<double> x, vector<double> w)
{
	double result = 0;
	for (int i = 0; i < x.size(); i++)
		result += x[i] * w[i];
	return result;
}

//������������� ������� ���������
inline double sigma(double x)
{
	return 1.0 / (1 + exp(-x));
}

//����������� ������������� �������
inline double derivativeSigma(double x)
{
	return sigma(x) * (1 - sigma(x));
}

//��������� ������� ���������
inline int threshold(double x)
{
	return x <= 0 ? 0 : 1;
}

//��������������� �������
inline double th(double x)
{
	return tanh(x);
}


class Neuron
{
	friend class NeuralNetwork;
public:
	Neuron(double(*Func) (double) = sigma);

private:
	double (*activation_function) (double x);
	double currValue;
};

