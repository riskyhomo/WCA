#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <limits> 


std::vector<double> parseZcomFile(const std::string &filename) {
    std::vector<double> z_com_values;
    std::ifstream infile(filename);
    std::string line;
    
    if (!infile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return z_com_values;
    }
    
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        double z_com;
        ss >> z_com;
        z_com_values.push_back(z_com);
    }
    
    infile.close();
    return z_com_values;
}

double calculateR0(int N, double po) {
    return std::pow((3.0 * N) / (4.0 * M_PI * po), 1.0 / 3.0);
}

double calculateContactAngle(double z_com, double r0) {
    double rhs = z_com / (std::pow(2.0, -4.0 / 3.0) * r0);
    double closest_theta = 0.0;
    double min_difference = std::numeric_limits<double>::max();

    for (double theta = 0.0000; theta <= 180.0000; theta += 0.0001) {
        double cosTheta = std::cos(theta * M_PI / 180.0);
        double lhs = std::pow((1 - cosTheta) / (2 + cosTheta), 1.0 / 3.0) * ((3 + cosTheta)/ (2+cosTheta));

        double difference = std::fabs(lhs - rhs);
        if (difference < min_difference) {
            min_difference = difference;
            closest_theta = theta;
        }
    }

    return closest_theta;
}

int main() {
    
    double po = 0.033;
    int N = 4424; 
    std::string inputFilename = "distances_m2.txt";
    std::string outputFilename = "wca.txt"; 
    

    std::vector<double> z_com_values = parseZcomFile(inputFilename);
    
    double r0 = calculateR0(N, po);
    

    std::ofstream outfile(outputFilename);
    if (!outfile.is_open()) {
        std::cerr << "Unable to open file for writing: " << outputFilename << std::endl;
        return 1;
    }
    
    for (double z_com : z_com_values) {
        double contact_angle = calculateContactAngle(z_com, r0);
        outfile << contact_angle  << std::endl;
    }
    
    outfile.close();
    return 0;
}
