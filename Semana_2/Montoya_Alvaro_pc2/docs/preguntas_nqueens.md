# Preguntas específicas - LeetCode 51 N-Queens

## Debe explicar

### Backtracking

El algoritmo coloca una reina por fila. Cada nivel de recursión representa la decisión de una fila. Al terminar una rama, se retira la reina para probar otra columna.

### Conflictos por columnas y diagonales

Una reina en `(row, col)` entra en conflicto si:

- La columna `col` ya está ocupada.
- La diagonal principal `row - col` ya está ocupada.
- La diagonal secundaria `row + col` ya está ocupada.

Como `row - col` puede ser negativo, se transforma a `row - col + n - 1`.

### Poda

Si `canPlace(row, col)` devuelve falso, esa casilla no se explora. Esa rama no puede producir una solución válida porque ya viola una restricción.

## Preguntas obligatorias

### 1. ¿Qué significa una decisión parcial válida?

Significa que ya se colocaron reinas en algunas filas, exactamente una por fila, y ninguna de ellas se ataca entre sí.

### 2. ¿Cómo detectas conflicto?

Con tres arreglos de ocupación:

```cpp
usedColumn_[col]
usedMainDiagonal_[row - col + n_ - 1]
usedAntiDiagonal_[row + col]
```

Si cualquiera está marcado, colocar una reina ahí produce conflicto.

### 3. ¿Qué ramas podas?

Se podan las ramas donde la casilla actual comparte columna o diagonal con una reina ya colocada.

### 4. ¿Qué estructura usas para diagonales?

Uso dos arreglos contiguos `std::vector<char>`:

- `usedMainDiagonal_`, indexado con `row - col + n - 1`.
- `usedAntiDiagonal_`, indexado con `row + col`.

Cada arreglo tiene tamaño `2n - 1`.

## Reto grabado específico

El reto de N-Queens pide mostrar el tablero parcial en cada nivel para `n = 4`.

El repositorio incluye:

```bash
./build/nqueens_demo 4 --trace
```

La traza imprime:

- nivel de recursión,
- tablero parcial,
- colocaciones aceptadas,
- podas,
- retrocesos,
- soluciones encontradas.
