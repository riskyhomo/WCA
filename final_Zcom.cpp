#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream inputFile("coms_vmd_final.txt");    
    ofstream outputFile("final_Zcom.txt");  
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        double x, y, z;
        
        if (iss >> x >> y >> z) {
            outputFile << z << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
