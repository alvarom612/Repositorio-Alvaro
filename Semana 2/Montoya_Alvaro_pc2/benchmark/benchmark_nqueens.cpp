#include "NQueensSolver.h"

#include <chrono>
#include <iostream>
#include <vector>

int main() {
    NQueensSolver solver;

    std::cout << "n,soluciones,tiempo_ms\n";

    for (int n = 1; n <= 10; ++n) {
        const auto start = std::chrono::steady_clock::now();
        const std::vector<std::vector<std::string>> solutions = solver.solve(n);
        const auto end = std::chrono::steady_clock::now();

        const auto elapsedMs =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << n << ","
                  << solutions.size() << ","
                  << elapsedMs << "\n";
    }

    return 0;
}