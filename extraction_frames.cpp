#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Atom {
    int id;
    int type;
    double xs, ys, zs;
    double vx, vy, vz;
};

void extractAtoms(const std::string& inputFilename, const std::string& outputType12, const std::string& outputType34) {
    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open input file: " << inputFilename << std::endl;
        return;
    }

    std::string line;
    std::ofstream outType12(outputType12);
    std::ofstream outType34(outputType34);

    while (std::getline(inputFile, line)) {
        if (line.find("ITEM: ATOMS") != std::string::npos) {
            break;
        }
    }

    while (std::getline(inputFile, line)) {
        std::istringstream atomStream(line);
        Atom atom;
        atomStream >> atom.id >> atom.type >> atom.xs >> atom.ys >> atom.zs >> atom.vx >> atom.vy >> atom.vz;

    
        if (atom.type == 1 || atom.type == 2) {
            outType12 << atom.id << " " << atom.type << " " << atom.xs << " " << atom.ys << " " << atom.zs << " " << atom.vx << " " << atom.vy << " " << atom.vz << "\n";
        }
        
        else if (atom.type == 3 || atom.type == 4) {
            outType34 << atom.id << " " << atom.type << " " << atom.xs << " " << atom.ys << " " << atom.zs << " " << atom.vx << " " << atom.vy << " " << atom.vz << "\n";
        }
    }

    inputFile.close();
    outType12.close();
    outType34.close();

    std::cout << "Processing completed." << std::endl;
}

int main() {
    std::string inputFilename = "v_0.005_eps_0.02_all.lammpstrj";
    std::string outputType12 = "type12.txt";
    std::string outputType34 = "type34.txt";

    extractAtoms(inputFilename, outputType12, outputType34);

    return 0;
}
