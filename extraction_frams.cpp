/*#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct Atom {
    int id;
    int type;
    double xs, ys, zs;
    double vx, vy, vz;
};

void processFrame(const std::vector<Atom>& atoms, std::ofstream& outFileType12, std::ofstream& outFileType34, int frameCount) {
    outFileType12 << "ITEM: TIMESTEP\n" << frameCount << "\n";
    outFileType34 << "ITEM: TIMESTEP\n" << frameCount << "\n";

    outFileType12 << "ITEM: NUMBER OF ATOMS\n" << atoms.size() << "\n";
    outFileType34 << "ITEM: NUMBER OF ATOMS\n" << atoms.size() << "\n";

        outFileType12 << "ITEM: BOX BOUNDS pp pp ff\n-1.0000000000000000e+02 2.2000000000000000e+02\n-1.0000000000000000e+02 2.2000000000000000e+02\n-2.0000000000000000e+01 2.0000000000000000e+02\n";
    outFileType34 << "ITEM: BOX BOUNDS pp pp ff\n-1.0000000000000000e+02 2.2000000000000000e+02\n-1.0000000000000000e+02 2.2000000000000000e+02\n-2.0000000000000000e+01 2.0000000000000000e+02\n";

    outFileType12 << "ITEM: ATOMS id type xs ys zs vx vy vz\n";
    outFileType34 << "ITEM: ATOMS id type xs ys zs vx vy vz\n";

    std::cout << "Processing frame:" << frameCount <<'/' << '\n'; 
    for (const auto& atom : atoms)
    {
        if (atom.type == 1 || atom.type == 2) {
            outFileType12 << atom.id << " " << atom.type << " " << atom.xs << " " << atom.ys << " " << atom.zs << " " << atom.vx << " " << atom.vy << " " << atom.vz << "\n";
        } else if (atom.type == 3 || atom.type == 4) {
            outFileType34 << atom.id << " " << atom.type << " " << atom.xs << " " << atom.ys << " " << atom.zs << " " << atom.vx << " " << atom.vy << " " << atom.vz << "\n";
        }
    }
}

void processFile(const std::string& inputFile, const std::string& outputFileType12, const std::string& outputFileType34)
    {
    int total_frame;
    std::ifstream inFile(inputFile);
    std::ofstream outFileType12(outputFileType12);
    std::ofstream outFileType34(outputFileType34);

    if (!inFile.is_open()) {
        std::cerr << "Could not open the input file." << std::endl;
        return;
    }

    if (!outFileType12.is_open() || !outFileType34.is_open()) {
        std::cerr << "Could not open one of the output files." << std::endl;
        return;
    }

    std::string line;
    std::vector<Atom> atoms;
    int frameCount = 0;
    int atomsPerFrame = 42472;

    while (std::getline(inFile, line)) {
        if (line.find("ITEM: TIMESTEP") != std::string::npos) {
            // New frame starts
            if (!atoms.empty()) {
                // Process the previous frame
                processFrame(atoms, outFileType12, outFileType34, frameCount);
                atoms.clear();
                frameCount++;
                //total_frame=frameCount;
            }
        } else if (line.find("ITEM: NUMBER OF ATOMS") != std::string::npos) {
            // Do nothing, handled in processFrame
        } else if (line.find("ITEM: BOX BOUNDS") != std::string::npos) {
            // Skip the BOX BOUNDS lines, handled in processFrame
            for (int i = 0; i < 3; ++i) {
                std::getline(inFile, line);
            }
        } else if (line.find("ITEM: ATOMS") != std::string::npos) {
            // Skip this line, handled in processFrame
        } else {
            std::istringstream iss(line);
            Atom atom;
            iss >> atom.id >> atom.type >> atom.xs >> atom.ys >> atom.zs >> atom.vx >> atom.vy >> atom.vz;
            atoms.push_back(atom);
        }
    }

    // Process the last frame
    if (!atoms.empty()) {
        processFrame(atoms, outFileType12, outFileType34, frameCount);
        frameCount++;
    }

    //std::cout << "Processed " << frameCount << " frames." << std::endl;

    inFile.close();
    outFileType12.close();
    outFileType34.close();
}

int main() {
    std::string inputFile = "v_0.005_eps_0.02_all.lammpstrj";
    std::string outputFileType12 = "type_1_2.lammpstrj";
    std::string outputFileType34 = "type_3_4.lammpstrj";

    processFile(inputFile, outputFileType12, outputFileType34);

    //std::cout << "Files created successfully." << std::endl;

    return 0; 
} */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct Atom {
    int id;
    int type;
    double xs, ys, zs;
    double vx, vy, vz;
};

void processFrame(const std::vector<Atom>& atoms, std::ofstream& outFileType12, std::ofstream& outFileType34, int frameCount) {
    outFileType12 << "ITEM: TIMESTEP\n" << frameCount << "\n";
    outFileType34 << "ITEM: TIMESTEP\n" << frameCount << "\n";

    outFileType12 << "ITEM: NUMBER OF ATOMS\n" << atoms.size() << "\n";
    outFileType34 << "ITEM: NUMBER OF ATOMS\n" << atoms.size() << "\n";

    outFileType12 << "ITEM: BOX BOUNDS pp pp ff\n-1.0000000000000000e+02 2.2000000000000000e+02\n-1.0000000000000000e+02 2.2000000000000000e+02\n-2.0000000000000000e+01 2.0000000000000000e+02\n";
    outFileType34 << "ITEM: BOX BOUNDS pp pp ff\n-1.0000000000000000e+02 2.2000000000000000e+02\n-1.0000000000000000e+02 2.2000000000000000e+02\n-2.0000000000000000e+01 2.0000000000000000e+02\n";

    outFileType12 << "ITEM: ATOMS id type xs ys zs vx vy vz\n";
    outFileType34 << "ITEM: ATOMS id type xs ys zs vx vy vz\n";

    std::cout << "Processing frame: " << frameCount << '\n'; 
    for (const auto& atom : atoms)
    {
        if (atom.type == 1 || atom.type == 2) {
            outFileType12 << atom.id << " " << atom.type << " " << atom.xs << " " << atom.ys << " " << atom.zs << " " << atom.vx << " " << atom.vy << " " << atom.vz << "\n";
        } else if (atom.type == 3 || atom.type == 4) {
            outFileType34 << atom.id << " " << atom.type << " " << atom.xs << " " << atom.ys << " " << atom.zs << " " << atom.vx << " " << atom.vy << " " << atom.vz << "\n";
        }
    }
}

void processFile(const std::string& inputFile, const std::string& outputFileType12, const std::string& outputFileType34)
{
    int total_frame;
    std::ifstream inFile(inputFile);
    std::ofstream outFileType12(outputFileType12);
    std::ofstream outFileType34(outputFileType34);

    if (!inFile.is_open()) {
        std::cerr << "Could not open the input file." << std::endl;
        return;
    }

    if (!outFileType12.is_open() || !outFileType34.is_open()) {
        std::cerr << "Could not open one of the output files." << std::endl;
        return;
    }

    std::string line;
    std::vector<Atom> atoms;
    int frameCount = 0;
    int atomsPerFrame = 42472;

    while (std::getline(inFile, line)) {
        if (line.find("ITEM: TIMESTEP") != std::string::npos) {
            // New frame starts
            if (!atoms.empty()) {
                // Process the previous frame
                processFrame(atoms, outFileType12, outFileType34, frameCount);
                atoms.clear();
                frameCount++;
                std::cout << "Processed frame: " << frameCount << '\n';
            }
        } else if (line.find("ITEM: NUMBER OF ATOMS") != std::string::npos) {
            // Do nothing, handled in processFrame
        } else if (line.find("ITEM: BOX BOUNDS") != std::string::npos) {
            // Skip the BOX BOUNDS lines, handled in processFrame
            for (int i = 0; i < 3; ++i) {
                std::getline(inFile, line);
            }
        } else if (line.find("ITEM: ATOMS") != std::string::npos) {
            // Skip this line, handled in processFrame
        } else {
            std::istringstream iss(line);
            Atom atom;
            iss >> atom.id >> atom.type >> atom.xs >> atom.ys >> atom.zs >> atom.vx >> atom.vy >> atom.vz;
            atoms.push_back(atom);
        }
    }

    // Process the last frame
    if (!atoms.empty()) {
        processFrame(atoms, outFileType12, outFileType34, frameCount);
        frameCount++;
        std::cout << "Processed frame: " << frameCount << '\n';
    }

    inFile.close();
    outFileType12.close();
    outFileType34.close();
}

int main() {
    std::string inputFile = "v_0.005_eps_0.02_all.lammpstrj";
    std::string outputFileType12 = "type_1_2.lammpstrj";
    std::string outputFileType34 = "type_3_4.lammpstrj";

    processFile(inputFile, outputFileType12, outputFileType34);

    return 0;
}