#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <vector>

struct City {
    double x, y;
};

class TSPSolver {
public:
    TSPSolver(int n);
    void readCities();
    double solve();

private:
    int n;
    std::vector<City> cities;
    std::vector<int> path;

    double dist(int i, int j) const;
    double calculateTotal() const;
    void greedyInitial();
    void optimize2Opt();
    bool optimize3Opt();
};

#endif
