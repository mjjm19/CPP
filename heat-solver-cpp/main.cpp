#include "heat_solver.h"

int main() {
    int    numPoints = 100;      // 100 points along the rod
    double length    = 1.0;      // 1 meter long rod
    double alpha     = 0.01;     // thermal diffusivity (steel ~approx)
    double dt        = 0.001;    // time step in seconds
    double totalTime = 1.0;      // simulate 1 second

    HeatSolver1D solver(numPoints, length, alpha, dt, totalTime);
    solver.run();
    solver.saveToCSV("results.csv");

    return 0;
}
