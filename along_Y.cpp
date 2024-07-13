#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;
double calculateDistance(double x0, double y0, double z0) {
    double A = 0.0, B = 1.0, C = 0.0, D = -0.49;
    double numerator = fabs(A * x0 + B * y0 + C * z0 + D);
    double denominator = sqrt(A * A + B * B + C * C);
    return numerator / denominator;
}

int main() {
    string inputFilePath = "coms_vmd_final.txt";
    string outputFilePath = "along_Y.txt"; 

    ifstream inputFile(inputFilePath);
    if (!inputFile) {
        cerr << "Error opening input file: " << inputFilePath << endl;
        return 1;
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile) {
        cerr << "Error opening output file: " << outputFilePath << endl;
        return 1;
    }

    string line;
    vector<double> distances;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        double x, y, z;
    
        if (!(iss >> x >> y >> z)) {
            cerr << "Error parsing line: " << line << endl;
            continue; 
        }
        double distance = calculateDistance(x, y, z);
        distances.push_back(distance);
    }
    for (const auto& distance : distances) {
        outputFile << distance << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Completed! ;Saved to: " << outputFilePath << endl;
    return 0;
}
