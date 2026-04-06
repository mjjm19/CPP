#include "heat_solver.h"
#include <iostream>
#include <fstream>
#include <cmath>

HeatSolver1D::HeatSolver1D(int n, double L, double a, double dt, double totalTime)
    : numPoints(n), length(L), alpha(a), dt(dt), totalTime(totalTime) {
    u.resize(n, 0.0);
}

void HeatSolver1D::setInitialCondition() {
    double dx = length / (numPoints - 1);
    for (int i = 0; i < numPoints; i++) {
        double x = i * dx;
        // Initial temperature: a sine wave (common test case)
        u[i] = sin(M_PI * x / length) * 100.0;
    }
    // Boundary conditions: both ends fixed at 0 degrees
    u[0] = 0.0;
    u[numPoints - 1] = 0.0;
}

void HeatSolver1D::step() {
    double dx = length / (numPoints - 1);
    double r = alpha * dt / (dx * dx);  // stability number (must be <= 0.5)

    if (r > 0.5) {
        std::cout << "WARNING: r = " << r << " > 0.5, simulation may be unstable!\n";
    }

    std::vector<double> u_new = u;

    // Finite difference update for interior points
    for (int i = 1; i < numPoints - 1; i++) {
        u_new[i] = u[i] + r * (u[i+1] - 2*u[i] + u[i-1]);
    }

    // Boundary conditions stay fixed at 0
    u_new[0] = 0.0;
    u_new[numPoints - 1] = 0.0;

    u = u_new;
}

void HeatSolver1D::run() {
    setInitialCondition();
    int numSteps = static_cast<int>(totalTime / dt);

    std::cout << "Starting simulation...\n";
    std::cout << "Steps: " << numSteps << "\n";

    for (int step = 0; step < numSteps; step++) {
        this->step();
        if (step % 100 == 0) {
            std::cout << "Step " << step << " / " << numSteps << "\n";
        }
    }
    std::cout << "Simulation complete.\n";
}

void HeatSolver1D::saveToCSV(const std::string& filename) {
    double dx = length / (numPoints - 1);
    std::ofstream file(filename);
    file << "x,temperature\n";
    for (int i = 0; i < numPoints; i++) {
        file << i * dx << "," << u[i] << "\n";
    }
    file.close();
    std::cout << "Results saved to " << filename << "\n";
}