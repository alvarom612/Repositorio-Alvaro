#include "NQueensSolver.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

namespace {

void printSolution(const std::vector<std::string>& board, int index) {
    std::cout << "Solucion " << index << ":\n";
    for (const std::string& row : board) {
        std::cout << row << "\n";
    }
}

bool allBoardsAreValid(NQueensSolver& solver,
                        const std::vector<std::vector<std::string>>& solution) {
    for (const std::vector<std::string>& board : solution) {
        if (!solver.isValidBoard(board)) {
            return false;
        }
    }

    return true;

}

bool readArguments(int argc, char* argv[], int& n, bool& trace) {
    n = 4;
    trace = false;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (arg == "--trace") {
            trace = true;
            continue;
        }

        try {
            n = std::stoi(arg);
        } catch (const std::exception&) {
            std::cerr << "Uso: " << argv[0] << " [n] [--trace]\n";
            return false;
        }
    }

    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    int n = 4;
    bool trace = false;

    if (!readArguments(argc, argv, n, trace)) {
        return 1;
    }

    NQueensSolver solver;
    std::vector<std::vector<std::string>> solutions;

    if (trace) {
        solutions = solver.solveWithTrace(n, std::cout);
    } else {
        solutions = solver.solve(n);
    }

    std::cout << "\nn = " << n << "\n";
    std::cout << "cantidad de soluciones = " << solutions.size() << "\n";

    std::cout << "validacion observable = "
              << (allBoardsAreValid(solver, solutions) ? "OK" : "FALLO") << "\n";


    if (n <= 6) {
        for (int i = 0; i < static_cast<int>(solutions.size()); ++i) {
            printSolution(solutions[i], i + 1);
        }
    } else {
        std::cout << "Para n > 6 solo se imprime la cantidad.\n";
    }

    return 0;
}