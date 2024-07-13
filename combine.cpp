#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Function to read XYZ coordinates from a file
std::vector<std::string> readXYZ(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream infile(filename);
    std::string line;
    // Skip the first two lines (header)
    std::getline(infile, line); // Number of atoms
    std::getline(infile, line); // Comment line
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    return lines;
}

// Function to write combined XYZ coordinates to a file
void writeCombinedXYZ(const std::string& filename, const std::vector<std::string>& roughSurface, const std::vector<std::string>& waterMolecules) {
    std::ofstream outfile(filename);
    // Total number of atoms
    outfile << roughSurface.size() + waterMolecules.size() << std::endl;
    outfile << "Combined rough surface and water molecules" << std::endl;
    // Write rough surface coordinates
    for (const auto& line : roughSurface) {
        outfile << line << std::endl;
    }
    // Write water molecules coordinates with adjusted z position
    for (auto line : waterMolecules) {
        double x, y, z;
        char element[2];
        sscanf(line.c_str(), "%s %lf %lf %lf", element, &x, &y, &z);
        z += 7.0; // Adjust z position to place water molecules above the rough surface
        outfile << element << " " << " 0 " << " "<< x << " " << y << " " << z << std::endl;
    }
    outfile.close();
}

int main() {
    // Read the rough surface coordinates
    std::vector<std::string> roughSurface = readXYZ("surface.xyz");

    // Read the water molecule coordinates
    std::vector<std::string> waterMolecules = readXYZ("water.xyz");

    // Write the combined coordinates to a new XYZ file
    writeCombinedXYZ("combined_surface_water_4.xyz", roughSurface, waterMolecules);

    std::cout << "Combined XYZ file created as combined_surface_water.xyz" << std::endl;

    return 0;
}
