#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    const double tan5 = 0.08748866352;  
    ifstream inputFile("task1.txt");   
    ofstream outputFile("with_tan5.txt"); 

    string line;
    vector<double> modifiedValues;

    
    while (getline(inputFile, line)) {
        double value;
        istringstream iss(line);
        if (iss >> value) {
            double modifiedValue = value * tan5;
            modifiedValues.push_back(modifiedValue);
        }
    }
    for (const double &value : modifiedValues) {
        outputFile << value << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
