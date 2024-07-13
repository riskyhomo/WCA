#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Function to generate a random floating-point number between min and max
double randomDouble(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

// Check if a point is within the sphere
bool isWithinSphere(double x, double y, double z, double centerX, double centerY, double centerZ, double radius) {
    double dx = x - centerX;
    double dy = y - centerY;
    double dz = z - centerZ;
    double distance = sqrt(dx * dx + dy * dy + dz * dz);
    return (distance <= radius);
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    // Parameters for the sphere
    double centerX = 150.0;
    double centerY = 150.0;
    double centerZ = 150.0;
    double radius = 75.0;
    int numMolecules = 5000;

    // Relative coordinates of the atoms in a water molecule
    double waterO[3] = {0.0, 0.0, 0.0};
    double waterH1[3] = {0.0, 0.757, 0.586};
    double waterH2[3] = {0.0, -0.757, 0.586};

    // Open the output file
    std::ofstream outputFile("water_sphere_5000.xyz");
    outputFile << numMolecules * 3 << std::endl; // Total number of atoms
    outputFile << "5000 water molecules in a sphere" << std::endl;

    for (int i = 0; i < numMolecules; ++i) {
        double x, y, z;
        do {
            x = randomDouble(centerX - radius, centerX + radius);
            y = randomDouble(centerY - radius, centerY + radius);
            z = randomDouble(centerZ - radius, centerZ + radius);
        } while (!isWithinSphere(x, y, z, centerX, centerY, centerZ, radius));

        // Output the coordinates for each atom in the water molecule
        outputFile << "O " << x + waterO[0] << " " << y + waterO[1] << " " << z + waterO[2] << std::endl;
        outputFile << "H " << x + waterH1[0] << " " << y + waterH1[1] << " " << z + waterH1[2] << std::endl;
        outputFile << "H " << x + waterH2[0] << " " << y + waterH2[1] << " " << z + waterH2[2] << std::endl;
    }

    outputFile.close();
    std::cout << "Generated 5000 water molecules in water_sphere_5000.xyz" << std::endl;

    return 0;
}
