#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void create_water_pdb(const char* filename, double box_x, double box_y, double box_z, double spacing_x, double spacing_y, double spacing_z) {
    double OH_distance = 0.96;  // in angstrong
    double HOH_angle = 104.5;   // degrees
    double H1_x, H1_y, H1_z, H2_x, H2_y, H2_z;

    // Convert angle to radians
    double HOH_angle_rad = HOH_angle * M_PI / 180.0;

    H1_x = OH_distance * sin(HOH_angle_rad / 2);
    H1_y = OH_distance * cos(HOH_angle_rad / 2);
    H1_z = 0;

    H2_x = -H1_x;
    H2_y = H1_y;
    H2_z = 0;

    ofstream pdb_file(filename);

    if (!pdb_file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    int atom_count = 1;

    for (double x = 0; x < box_x; x += spacing_x) {
        for (double y = 0; y < box_y; y += spacing_y) {
            for (double z = 0; z < box_z; z += spacing_z) {
                // Oxygen atom
                pdb_file << "ATOM  " << atom_count++ << "  O   HOH A" << atom_count << "    "
                         << x << "  " << y << "  " << z << "  1.00  0.00           O\n";

                // Hydrogen atoms
                pdb_file << "ATOM  " << atom_count++ << "  H1  HOH A" << atom_count - 1 << "    "
                         << x + H1_x << "  " << y + H1_y << "  " << z + H1_z << "  1.00  0.00           H\n";

                pdb_file << "ATOM  " << atom_count++ << "  H2  HOH A" << atom_count - 2 << "    "
                         << x + H2_x << "  " << y + H2_y << "  " << z + H2_z << "  1.00  0.00           H\n";
            }
        }
    }

    pdb_file << "TER\nEND\n";

    // Close the file
    pdb_file.close();

    cout << "Successfully created " << filename << " with water molecules." << endl;
}

int main() {
    // Define box dimensions (in Å)
    double box_x = 300.0, box_y = 300.0, box_z = 15.0;

    // Define spacing between water molecules (in Å)
    double spacing_x = 3.0, spacing_y = 3.0, spacing_z = 3.0;

    // Output file name
    const char* output_filename = "water.pdb";

    // Generate the PDB file
    create_water_pdb(output_filename, box_x, box_y, box_z, spacing_x, spacing_y, spacing_z);

    return 0;
}
