#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Function to generate a random floating-point number between min and max
double randomDouble(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

// Function to generate a noise-based height for the surface
double noiseHeight(double x, double y, double scale, double amplitude) {
    return amplitude * sin(scale * x) * cos(scale * y) + randomDouble(-1, 1) * amplitude * 0.1;
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    // Dimensions of the surface
    int xSize = 300;
    int ySize = 300;
    double zMax = 5.0;
    double scale = 0.1;    // Controls the frequency of the roughness
    double amplitude = 1.0; // Controls the amplitude of the roughness

    // Open the output file
    std::ofstream outputFile("rough_surface_2.xyz");
    outputFile << xSize * ySize << std::endl; // Total number of points
    outputFile << "Rough surface coordinates" << std::endl;

    // Generate the rough surface
    for (int x = 0; x < xSize; ++x) {
        for (int y = 0; y < ySize; ++y) {
            double z = noiseHeight(x, y, scale, amplitude);
            // Ensure z is within the specified range (0 to zMax)
            z = std::max(0.0, std::min(z, zMax));
            outputFile << "0 " << x << " " << y << " " << z << std::endl;
        }
    }

    outputFile.close();
    std::cout << "Generated rough surface coordinates in rough_surface.xyz" << std::endl;

    return 0;
}
