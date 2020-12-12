#include <iostream>
#include <vector>
#include "NeuralNetwork.h"

using namespace std;

int main()
{
    vector <int> layers = { 4, 3, 1 };
    vector <vector<double> > input = { {1, 2, 3, 5}, {1, 5, 1, 5}, {1, 6, 7, 1} };
    
    NeuralNetwork n(layers);
    
    cout << n.HebbsMethod(400, input);

    n.save("WB.txt");

    return 0;
}
