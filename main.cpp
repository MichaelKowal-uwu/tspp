#include <iostream>
#include <iomanip>
#include "tsp_solver.h"

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    TSPSolver solver(n);
    solver.readCities();
    std::cout << std::fixed << std::setprecision(10) << solver.solve() << std::endl;
    return 0;
}
