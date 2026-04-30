#ifndef NQUEENS_SOLVER_H
#define NQUEENS_SOLVER_H

#include <iosfwd>
#include <string>
#include <vector>

class NQueensSolver {
public:
    std::vector<std::vector<std::string>> solve(int n);

    std::vector<std::vector<std::string>> solveWithTrace(int n, std::ostream& out);

    bool isValidBoard(const std::vector<std::string>& board) const;

private:
    int n_ = 0;
    std::vector<std::string> board_;
    std::vector<int> queenColumnByRow_;
    std::vector<char> usedColumn_;
    std::vector<char> usedMainDiagonal_;
    std::vector<char> usedAntiDiagonal_;
    std::vector<std::vector<std::string>> solutions_;

    void reset(int n);
    void backtrack(int row, bool trace, std::ostream* out);

    bool canPlace(int row, int col) const;
    void placeQueen(int row, int col);
    void removeQueen(int row, int col);
    void saveSolution();

    int mainDiagonalIndex(int row, int col) const;
    int antiDiagonalIndex(int row, int col) const;
    void printPartialBoard(int fixedRows, std::ostream& out) const;
};

#endif