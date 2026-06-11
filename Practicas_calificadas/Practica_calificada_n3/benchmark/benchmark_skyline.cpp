#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "../include/skyline.hpp"

using namespace std;
using namespace std::chrono;

/*
 * Genera edificios aleatorios para pruebas de rendimiento
 */
vector<Skyline::Building> generateBuildings(int n, int maxCoord = 100000, int maxHeight = 1000) {
    vector<Skyline::Building> b;
    b.reserve(n);

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distX(0, maxCoord);
    uniform_int_distribution<int> distH(1, maxHeight);

    for (int i = 0; i < n; i++) {
        int l = distX(gen);
        int r = l + (distX(gen) % 100 + 1);
        int h = distH(gen);

        b.push_back({l, r, h});
    }

    return b;
}

/*
 * Ejecuta una medición de rendimiento para un tamaño dado
 */
void runBenchmark(int n) {
    Skyline solver;
    auto buildings = generateBuildings(n);

    auto start = high_resolution_clock::now();
    auto result = solver.getSkyline(buildings);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "n=" << n
         << " | skyline_points=" << result.size()
         << " | time_ms=" << duration.count()
         << endl;
}

/*
 * Benchmark principal
 */
int main() {

    vector<int> tests = {
        100,
        500,
        1000,
        2000,
        5000,
        10000
    };

    for (int n : tests) {
        runBenchmark(n);
    }

    return 0;
}