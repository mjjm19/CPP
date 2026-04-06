#pragma once
#include <vector>
#include <string>

class HeatSolver1D {
public:
    // Setup
    int    numPoints;     // number of spatial points
    double length;        // rod length (meters)
    double alpha;         // thermal diffusivity
    double dt;            // time step
    double totalTime;     // how long to simulate

    std::vector<double> u;  // temperature at each point

    // Constructor
    HeatSolver1D(int n, double L, double alpha, double dt, double totalTime);

    // Set initial temperature distribution
    void setInitialCondition();

    // Run one time step (explicit method)
    void step();

    // Run full simulation
    void run();

    // Save results to CSV
    void saveToCSV(const std::string& filename);
};
