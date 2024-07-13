#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

double computeDistance(double x) {
    return abs(x - 120.0);
}

int main() {
    ifstream inputFile("coms_vmd_final.txt");
    ofstream outputFile("task1.txt");

    string line;
    vector<double> distances;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        double x, y, z;
        if (iss >> x >> y >> z) {
            distances.push_back(computeDistance(x));
        }
    }

    for (size_t i = 0; i < distances.size(); ++i) {
        outputFile << distances[i] << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
