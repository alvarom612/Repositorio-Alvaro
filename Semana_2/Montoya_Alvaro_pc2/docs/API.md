# API pública y representación interna

## API pública

`NQueensSolver` expone tres operaciones:

```cpp
std::vector<std::vector<std::string>> solve(int n);
std::vector<std::vector<std::string>> solveWithTrace(int n, std::ostream& out);
bool isValidBoard(const std::vector<std::string>& board) const;
```

`Solution` expone el método compatible con LeetCode:

```cpp
std::vector<std::vector<std::string>> solveNQueens(int n);
```

## Representación interna

La representación interna está oculta en la sección privada de `NQueensSolver`:

```cpp
int n_;
std::vector<std::string> board_;
std::vector<int> queenColumnByRow_;
std::vector<char> usedColumn_;
std::vector<char> usedMainDiagonal_;
std::vector<char> usedAntiDiagonal_;
std::vector<std::vector<std::string>> solutions_;
```

## Motivo de encapsulación

El usuario del solucionador no necesita saber cómo se indexan las diagonales ni cómo se deshacen las decisiones. Solo necesita llamar a `solve(n)` y recibir los tableros válidos.