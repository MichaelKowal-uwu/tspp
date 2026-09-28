#include "tsp_solver.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>

TSPSolver::TSPSolver(int n) : n(n) {
    cities.resize(n);
}

void TSPSolver::readCities() {
    for (int i = 0; i < n; ++i) std::cin >> cities[i].x >> cities[i].y;
}

double TSPSolver::dist(int i, int j) const {
    return std::sqrt(std::pow(cities[i].x - cities[j].x, 2) + std::pow(cities[i].y - cities[j].y, 2));
}

double TSPSolver::calculateTotal() const {
    double total = 0;
    for (int i = 0; i < n; ++i) total += dist(path[i], path[(i + 1) % n]);
    return total;
}

void TSPSolver::greedyInitial() {
    std::vector<bool> visited(n, false);
    path = {0};
    visited[0] = true;
    for (int i = 1; i < n; ++i) {
        int last = path.back(), best = -1;
        double minDist = 1e18;
        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                double d = dist(last, j);
                if (d < minDist) { minDist = d; best = j; }
            }
        }
        path.push_back(best);
        visited[best] = true;
    }
}

void TSPSolver::optimize2Opt() {
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 1; i < n - 1; ++i) {
            for (int k = i + 1; k < n; ++k) {
                double d_old = dist(path[i-1], path[i]) + dist(path[k], path[(k+1)%n]);
                double d_new = dist(path[i-1], path[k]) + dist(path[i], path[(k+1)%n]);
                if (d_new < d_old - 1e-9) {
                    std::reverse(path.begin() + i, path.begin() + k + 1);
                    improved = true;
                }
            }
        }
    }
}

bool TSPSolver::optimize3Opt() {
    bool improved = false;
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                int A = path[i], B = path[i+1];
                int C = path[j], D = path[j+1];
                int E = path[k], F = path[(k+1)%n];

                double d_old = dist(A, B) + dist(C, D) + dist(E, F);
                double d_new = dist(A, D) + dist(E, B) + dist(C, F);

                if (d_new < d_old - 1e-9) {
                    std::vector<int> new_path;
                    for (int x = 0; x <= i; ++x) new_path.push_back(path[x]);
                    for (int x = j + 1; x <= k; ++x) new_path.push_back(path[x]);
                    for (int x = i + 1; x <= j; ++x) new_path.push_back(path[x]);
                    for (int x = k + 1; x < n; ++x) new_path.push_back(path[x]);
                    path = new_path;
                    improved = true;
                }
            }
        }
    }
    return improved;
}

double TSPSolver::solve() {
    if (n < 2) return 0;
    greedyInitial();
    bool improving = true;
    while (improving) {
        optimize2Opt();
        improving = optimize3Opt();
    }
    return calculateTotal();
}
