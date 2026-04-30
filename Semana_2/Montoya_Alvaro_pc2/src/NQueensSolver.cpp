#include "NQueensSolver.h"

#include <ostream>

std::vector<std::vector<std::string>> NQueensSolver::solve(int n) {
    reset(n);
    if (n_ <= 0) {
        return solutions_;
    }

    backtrack(0, false, nullptr);
    return solutions_;
}

std::vector<std::vector<std::string>> NQueensSolver::solveWithTrace(int n, std::ostream& out) {
    reset(n);
    if (n_ <= 0) {
        out << "n invalido o vacio: no hay tablero que explorar\n";
        return solutions_;
    }

    out << "Traza de backtracking para n = " << n_ << "\n";
    backtrack(0, true, &out);
    return solutions_;
}

bool NQueensSolver::isValidBoard(const std::vector<std::string>& board) const {
    const int n = static_cast<int>(board.size());
    if (n == 0) {
        return false;
    }

    std::vector<char> usedColumn(n, 0);
    std::vector<char> usedMainDiagonal(2 * n - 1, 0);
    std::vector<char> usedAntiDiagonal(2 * n - 1, 0);

    int queens = 0;

    for (int row = 0; row < n; ++row) {
        if (static_cast<int>(board[row].size()) != n) {
            return false;
        }

        int queensInRow = 0;

        for (int col = 0; col < n; ++col) {
            const char cell = board[row][col];

            if (cell == '.') {
                continue;
            }

            if (cell != 'Q') {
                return false;
            }

            ++queens;
            ++queensInRow;

            const int mainDiag = row - col + n - 1;
            const int antiDiag = row + col;

            if (usedColumn[col] || usedMainDiagonal[mainDiag] || usedAntiDiagonal[antiDiag]) {
                return false;
            }

            usedColumn[col] = 1;
            usedMainDiagonal[mainDiag] = 1;
            usedAntiDiagonal[antiDiag] = 1;
        }

        if (queensInRow != 1) {
            return false;
        }
    }

    return queens == n;
}

void NQueensSolver::reset(int n) {
    n_ = n;
    board_.clear();
    queenColumnByRow_.clear();
    usedColumn_.clear();
    usedMainDiagonal_.clear();
    usedAntiDiagonal_.clear();
    solutions_.clear();

    if (n_ <= 0) {
        return;
    }

    board_.assign(n_, std::string(n_, '.'));
    queenColumnByRow_.assign(n_, -1);
    usedColumn_.assign(n_, 0);
    usedMainDiagonal_.assign(2 * n_ - 1, 0);
    usedAntiDiagonal_.assign(2 * n_ - 1, 0);
}

void NQueensSolver::backtrack(int row, bool trace, std::ostream* out) {
    if (trace && out != nullptr) {
        *out << "\nNivel " << row << ": filas fijadas = " << row << "\n";
        printPartialBoard(row, *out);
    }

    if (row == n_) {
        saveSolution();

        if (trace && out != nullptr) {
            *out << "Solucion encontrada #" << solutions_.size() << "\n";
        }

        return;
    }

    for (int col = 0; col < n_; ++col) {
        if (!canPlace(row, col)) {
            if (trace && out != nullptr) {
                *out << "Poda: no se coloca en fila " << row
                     << ", columna " << col << "\n";
            }
            continue;
        }

        if (trace && out != nullptr) {
            *out << "Colocar reina en fila " << row
                 << ", columna " << col << "\n";
        }

        placeQueen(row, col);
        backtrack(row + 1, trace, out);
        removeQueen(row, col);

        if (trace && out != nullptr) {
            *out << "Retroceder desde fila " << row
                 << ", columna " << col << "\n";
        }
    }
}

bool NQueensSolver::canPlace(int row, int col) const {
    return !usedColumn_[col]
        && !usedMainDiagonal_[mainDiagonalIndex(row, col)]
        && !usedAntiDiagonal_[antiDiagonalIndex(row, col)];
}

void NQueensSolver::placeQueen(int row, int col) {
    board_[row][col] = 'Q';
    queenColumnByRow_[row] = col;
    usedColumn_[col] = 1;
    usedMainDiagonal_[mainDiagonalIndex(row, col)] = 1;
    usedAntiDiagonal_[antiDiagonalIndex(row, col)] = 1;
}

void NQueensSolver::removeQueen(int row, int col) {
    board_[row][col] = '.';
    queenColumnByRow_[row] = -1;
    usedColumn_[col] = 0;
    usedMainDiagonal_[mainDiagonalIndex(row, col)] = 0;
    usedAntiDiagonal_[antiDiagonalIndex(row, col)] = 0;
}

void NQueensSolver::saveSolution() {
    solutions_.push_back(board_);
}

int NQueensSolver::mainDiagonalIndex(int row, int col) const {
    return row - col + n_ - 1;
}

int NQueensSolver::antiDiagonalIndex(int row, int col) const {
    return row + col;
}

void NQueensSolver::printPartialBoard(int fixedRows, std::ostream& out) const {
    for (int row = 0; row < n_; ++row) {
        out << board_[row];

        if (row < fixedRows) {
            out << "  fija";
        }

        out << "\n";
    }
}
