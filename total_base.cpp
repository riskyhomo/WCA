#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    const double addValue = 10.5031424;  
    ifstream inputFile("with_tan5.txt");    
    ofstream outputFile("total_base_len.txt");  

    string line;
    vector<double> modifiedNumbers;
    while (getline(inputFile, line)) {
        double number;
        istringstream iss(line);
        if (iss >> number) {
            double modifiedNumber = number + addValue;
            modifiedNumbers.push_back(modifiedNumber);
        }
    }

    for (const double &number : modifiedNumbers) {
        outputFile << number << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
