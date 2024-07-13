#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Atom {
    int id;
    int type;
    double xs, ys, zs;
};

int main() {
    string filename = "type_1_2.lammpstrj";
    ifstream infile(filename);
    string line;

    int total_water_molecules = 0;

    // Read until the end of file
    while (getline(infile, line)) {
        // Check for the start of a frame
        if (line.find("ITEM: TIMESTEP") != string::npos) {
            // Read until the next "ITEM: TIMESTEP" to get to the next frame
            while (getline(infile, line) && line.find("ITEM: TIMESTEP") == string::npos) {
                // Check for the "ATOMS" section
                if (line.find("ITEM: ATOMS") != string::npos) {
                    // Read atoms for the current frame
                    vector<Atom> atoms;
                    while (getline(infile, line) && !line.empty()) {
                        istringstream iss(line);
                        Atom atom;
                        iss >> atom.id >> atom.type >> atom.xs >> atom.ys >> atom.zs;
                        atoms.push_back(atom);
                    }

                    // Count water molecules (pairs of H and O atoms)
                    int hydrogen_count = 0;
                    int oxygen_count = 0;
                    for (size_t i = 0; i < atoms.size(); ++i) {
                        if (atoms[i].type == 1) { // Hydrogen atom
                            hydrogen_count++;
                        } else if (atoms[i].type == 2) { // Oxygen atom
                            oxygen_count++;
                        }

                        // If we have enough atoms to form a water molecule, count it
                        if (hydrogen_count >= 2 && oxygen_count >= 1) {
                            total_water_molecules++;
                            hydrogen_count -= 2;
                            oxygen_count -= 1;
                        }
                    }

                    break; // Move to the next frame
                }
            }
        }
    }

    cout << "Total number of water molecules: " << total_water_molecules << endl;

    infile.close();
    return 0;
}
