## PC2 - CC232

### Estudiante

- Nombre: **Alvaro Raul Montoya Dulanto**
- Código: **20244154A**
- Problema asignado: **LeetCode 51 - N-Queens**
- Enlace: <https://leetcode.com/problems/n-queens/>

### Referencia oficial

- Archivo de asignación:
  <https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv>

### Tema principal

- Semana: **Semana 4**
- Estructura o técnica principal: **Backtracking con poda usando arreglos auxiliares para columnas y diagonales**

### Resumen de la solución

El problema pide colocar `n` reinas en un tablero `n x n` de manera que ninguna ataque a otra. Una reina ataca por fila, columna y diagonales.

La solución construye el tablero fila por fila. En cada nivel de recursión se intenta colocar una reina en la fila actual. Para saber si una casilla es válida no se recorre todo el tablero: se consultan tres arreglos auxiliares:

- `usedColumn_[col]`: indica si una columna ya tiene reina.
- `usedMainDiagonal_[row - col + n - 1]`: indica si una diagonal principal ya está ocupada.
- `usedAntiDiagonal_[row + col]`: indica si una diagonal secundaria ya está ocupada.

Cuando una posición genera conflicto, la rama se poda. Cuando se llega a `row == n`, el tablero actual es una solución completa y se guarda.

### Complejidad

Sea `S` la cantidad de soluciones producidas.

- Tiempo: `O(n * n! + S * n^2)`.
  - `O(n * n!)` es una cota para la exploración con poda por columnas y diagonales.
  - `O(S * n^2)` corresponde a copiar los tableros solución.
- Espacio auxiliar sin contar la salida: `O(n^2)`.
  - El tablero ocupa `O(n^2)`.
  - Los arreglos de columnas y diagonales ocupan `O(n)`.
  - La profundidad de recursión es `O(n)`.
- Espacio de salida: `O(S * n^2)`.

### Invariante o idea clave

Antes de entrar a `backtrack(row)`, las filas `0..row-1` tienen exactamente una reina cada una, no existe conflicto entre ellas y los arreglos auxiliares describen exactamente esas reinas. Las filas `row..n-1` todavía no están fijadas.

`placeQueen` extiende el invariante para una fila más. `removeQueen` revierte el cambio para probar otra columna sin contaminar otras ramas.

### Archivos relevantes

- `include/NQueensSolver.h`: API pública del solucionador.
- `include/Solution.h`: envoltorio compatible con el estilo de LeetCode.
- `src/NQueensSolver.cpp`: implementación concreta.
- `demos/main.cpp`: programa de demostración.
- `tests/test_nqueens.cpp`: pruebas con `assert`.
- `benchmark/benchmark_nqueens.cpp`: medición simple por tamaño de `n`.
- `docs/`: respuestas, conceptos, casos de prueba y guía de video.
- `actividades/`: actividades 1, 2 y 3 exigidas por el enunciado.

### Compilación

```bash
cmake -S . -B build
cmake --build build
```

### Ejecución

Ejecutar el demo principal con `n = 4`:

```bash
./build/nqueens_demo 4
```

Ejecutar el demo con traza para el reto específico de N-Queens:

```bash
./build/nqueens_demo 4 --trace
```

Ejecutar pruebas:

```bash
./build/nqueens_tests
ctest --test-dir build --output-on-failure
```

Ejecutar benchmark:

```bash
./build/nqueens_benchmark
```

### Casos de prueba

1. `n = 1`: debe producir una solución: `["Q"]`.
2. `n = 2`: no existe solución.
3. `n = 3`: no existe solución.
4. `n = 4`: debe producir exactamente dos soluciones.
5. `n = 5`: debe producir diez soluciones.
6. `n = 0` y `n < 0`: no pertenecen a la entrada normal de LeetCode, pero el programa devuelve lista vacía para no romperse.

### Historial de commits

El historial se evidencia en el video.

### Declaración de autoría

Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.
