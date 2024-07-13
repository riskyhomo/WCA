#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Function to generate a periodic height based on the x and y coordinates
double periodicHeight(double x, double y, double interval, double amplitude) {
    double height = amplitude * (sin((M_PI / interval) * x) + cos((M_PI / interval) * y));
    return height;
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    // Dimensions and parameters of the surface
    int xSize = 300;
    int ySize = 300;
    double interval = 10.0; // Interval for periodic roughness
    double amplitude = 3.0; // Height of the hills for the rough surface
    int numBaseLayers = 2;  // Number of base layers
    int numRoughLayers = 5; // Number of rough layers
    double baseHeightIncrement = 1.0; // Height increment between base layers
    double startRoughLayerHeight = numBaseLayers * baseHeightIncrement; // Starting height for rough layers

    // Open the output file
    std::ofstream outputFile("rough_surface_layers.xyz");
    outputFile << xSize * ySize * (numBaseLayers + numRoughLayers) << std::endl; // Total number of points
    outputFile << "2 base layers and 5 rough surface layers" << std::endl;

    // Generate the base layers
    for (int layer = 0; layer < numBaseLayers; ++layer) {
        for (int x = 0; x < xSize; ++x) {
            for (int y = 0; y < ySize; ++y) {
                double z = layer * baseHeightIncrement;
                outputFile << "P " << x << " " << y << " " << z << std::endl;
            }
        }
    }

    // Generate the rough surface layers
    for (int layer = 0; layer < numRoughLayers; ++layer) {
        for (int x = 0; x < xSize; ++x) {
            for (int y = 0; y < ySize; ++y) {
                double z = startRoughLayerHeight + layer + periodicHeight(x, y, interval, amplitude);
                // Ensure z does not go below the start height for rough layers
                z = std::max(z, startRoughLayerHeight + layer);
                outputFile << "P " << x << " " << y << " " << z << std::endl;
            }
        }
    }

    outputFile.close();
    std::cout << "Generated rough surface coordinates in rough_surface_layers.xyz" << std::endl;

    return 0;
}
