#include "Neuron.h"

Neuron::Neuron(double(*Func)(double))
{
    activation_function = Func;
    currValue = 0;
}

