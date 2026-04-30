#ifndef SOLUTION_H
#define SOLUTION_H

#include "NQueensSolver.h"

#include <string>
#include <vector>

class Solution {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        return solver_.solve(n);
    }

private:
    NQueensSolver solver_;
};

#endif