#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

const double MASS_OXYGEN = 16.000;  // Atomic mass units
const double MASS_HYDROGEN = 1.008; // Atomic mass units

struct Atom {
    int id;
    int type;
    double xs, ys, zs;
};

double calculate_com_z(const std::vector<Atom>& atoms) {
    double total_mass = 0.0;
    double weighted_sum_z = 0.0;

    for (const auto& atom : atoms) {
        if (atom.type == 2) {  // Oxygen
            total_mass += MASS_OXYGEN;
            weighted_sum_z += MASS_OXYGEN * atom.zs;
        } else if (atom.type == 1) {  // Hydrogen
            total_mass += MASS_HYDROGEN;
            weighted_sum_z += MASS_HYDROGEN * atom.zs;
        }
    }

    return weighted_sum_z / total_mass;
}

int main() {
    std::ifstream infile("type_1_2.lammpstrj");
    if (!infile.is_open()) {
        std::cerr << "Error: File not found." << std::endl;
        return 1;
    }

    std::ofstream outfile("z_com11.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to create output file." << std::endl;
        infile.close();
        return 1;
    }

    std::string line;
    std::vector<Atom> current_frame_atoms;
    int frame_count = 0;
    bool reading_atoms = false;

    while (std::getline(infile, line)) {
        if (line.find("ITEM: ATOMS") != std::string::npos) {
            reading_atoms = true;
            if (!current_frame_atoms.empty()) {
                // Calculate the COM for the current frame
                double com_z = calculate_com_z(current_frame_atoms);
                // Save the COM value to the output file
                outfile << com_z << std::endl;
                current_frame_atoms.clear();
            }
            frame_count++;
        } else if (reading_atoms) {
            std::istringstream iss(line);
            Atom atom;
            if (iss >> atom.id >> atom.type >> atom.xs >> atom.ys >> atom.zs) {
                current_frame_atoms.push_back(atom);
            }
        }
    }

    // Process the last frame if any
    if (!current_frame_atoms.empty()) {
        double com_z = calculate_com_z(current_frame_atoms);
        outfile << com_z << std::endl;
    }

    infile.close();
    outfile.close();
    return 0;
}

