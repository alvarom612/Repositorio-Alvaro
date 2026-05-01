#include "NQueensSolver.h"
#include "Solution.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace {

void assertAllBoardsAreValid(NQueensSolver& solver,
                             const std::vector<std::vector<std::string>>& solutions) {
    for (const std::vector<std::string>& board : solutions) {
        assert(solver.isValidBoard(board));
    }
}

void testKnownCounts() {
    NQueensSolver solver;

    const std::vector<std::pair<int, int>> cases = {
        {1, 1},
        {2, 0},
        {3, 0},
        {4, 2},
        {5, 10},
        {6, 4},
    };

    for (const auto& testCase : cases) {
        const int n = testCase.first;
        const int expected = testCase.second;

        const std::vector<std::vector<std::string>> solutions = solver.solve(n);
        assert(static_cast<int>(solutions.size()) == expected);
        assertAllBoardsAreValid(solver, solutions);
    }
}

void testLeetCodeCompatibleWrapper() {
    Solution solution;
    const std::vector<std::vector<std::string>> boards = solution.solveNQueens(4);

    assert(boards.size() == 2);
}

void testInvalidOrEmptyInputDoesNotCrash() {
    NQueensSolver solver;

    assert(solver.solve(0).empty());
    assert(solver.solve(-3).empty());
}

void testBoardValidatorRejectsInvalidBoards() {
    NQueensSolver solver;

    const std::vector<std::string> sameColumn = {
        "Q...",
        "Q...",
        "....",
        "...."
    };

    const std::vector<std::string> diagonalConflict = {
        "Q...",
        ".Q..",
        "..Q.",
        "...Q"
    };

    const std::vector<std::string> badCharacter = {
        "Q...",
        ".x..",
        "..Q.",
        "...Q"
    };

    assert(!solver.isValidBoard(sameColumn));
    assert(!solver.isValidBoard(diagonalConflict));
    assert(!solver.isValidBoard(badCharacter));
}

}  // namespace

int main() {
    testKnownCounts();
    testLeetCodeCompatibleWrapper();
    testInvalidOrEmptyInputDoesNotCrash();
    testBoardValidatorRejectsInvalidBoards();

    std::cout << "Todos los tests de N-Queens pasaron.\n";
    return 0;
}
