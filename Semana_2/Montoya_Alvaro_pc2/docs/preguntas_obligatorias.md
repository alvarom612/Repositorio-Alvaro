# Preguntas comunes obligatorias

## 7.1 Sobre el problema

### 1. ¿Cuál es el problema exacto que resolviste?

Resolví LeetCode 51, N-Queens. El problema pide encontrar todas las formas distintas de colocar `n` reinas en un tablero `n x n` sin que dos reinas se ataquen.

### 2. ¿Qué recibe la entrada y qué debe producir la salida?

Recibe un entero `n`. Produce una lista de tableros. Cada tablero se representa como un vector de cadenas donde `Q` indica una reina y `.` una celda vacía.

### 3. ¿Cuál es la restricción más importante del problema?

La restricción central es que dos reinas no pueden compartir fila, columna ni diagonal.

### 4. ¿Cuál sería una solución ingenua?

Una solución ingenua sería probar todas las formas posibles de elegir `n` casillas dentro del tablero y luego verificar si el tablero completo es válido.

### 5. ¿Por qué esa solución ingenua no basta?

Porque genera demasiadas combinaciones inválidas. También perdería tiempo verificando tableros completos que ya eran imposibles desde las primeras decisiones.

## 7.2 Sobre la estructura y la técnica

### 6. ¿Qué estructura de datos elegiste?

Uso un tablero `vector<string>`, un arreglo de columnas ocupadas y dos arreglos de diagonales ocupadas.

### 7. ¿Por qué esa estructura es apropiada?

Porque permite saber en `O(1)` si una nueva reina entra en conflicto. Además, el tablero se puede copiar directamente cuando se encuentra una solución.

### 8. ¿Qué invariante debes mantener?

Antes de entrar a `backtrack(row)`, las filas anteriores tienen una reina cada una, no hay conflictos y los arreglos auxiliares coinciden con esas reinas.

### 9. ¿Qué operación es la más importante del algoritmo?

La operación más importante es `canPlace(row, col)`, porque decide si se explora o se poda una rama.

### 10. ¿Qué parte del código sería más fácil romper?

Las actualizaciones simétricas entre `placeQueen` y `removeQueen`. Si se marca una columna o diagonal al colocar, se debe desmarcar exactamente la misma al retroceder.

## 7.3 Sobre complejidad

### 11. ¿Cuál es la complejidad temporal?

La cota usada es `O(n * n! + S * n^2)`, donde `S` es la cantidad de soluciones. La copia de cada solución cuesta `O(n^2)`.

### 12. ¿Cuál es la complejidad espacial?

Sin contar la salida, `O(n^2)` por el tablero. Los arreglos auxiliares y la recursión son `O(n)`. La salida ocupa `O(S * n^2)`.

### 13. ¿Hay costo amortizado? ¿Dónde?

El núcleo del algoritmo no se basa en costo amortizado. Solo `std::vector` puede crecer amortizadamente al guardar soluciones, pero la búsqueda combinatoria domina el tiempo.

### 14. ¿Qué operación domina el tiempo?

Domina la exploración de estados parciales del backtracking. En cada fila se prueban columnas y se podan ramas inválidas.

### 15. ¿Qué estructura alternativa podría usarse y qué perderías con ella?

Se podría verificar conflictos recorriendo el tablero en vez de usar arreglos auxiliares. Se perdería eficiencia porque cada verificación podría costar `O(n)` o más.

## 7.4 Sobre implementación

### 16. ¿Cómo representas internamente el estado?

El estado tiene el tablero actual, la columna elegida por fila, columnas ocupadas, diagonales principales ocupadas, diagonales secundarias ocupadas y la lista de soluciones.

### 17. ¿Qué variables o contenedores son críticas?

`board_`, `usedColumn_`, `usedMainDiagonal_`, `usedAntiDiagonal_` y `solutions_`.

### 18. ¿Qué ocurre en el caso vacío?

Para `n <= 0`, el solucionador devuelve una lista vacía y no entra a la recursión. LeetCode normalmente no usa ese caso, pero se maneja para robustez.

### 19. ¿Qué ocurre en el caso de un solo elemento?

Para `n = 1`, se coloca una reina en la única celda y se obtiene una solución: `["Q"]`.

### 20. ¿Qué ocurre en el caso extremo de entrada?

La cantidad de ramas crece muy rápido. La poda reduce estados inválidos, pero el problema sigue siendo exponencial.

## 7.5 Sobre validación

### 21. ¿Qué test propio escribiste?

Escribí tests para los conteos conocidos de `n = 1, 2, 3, 4, 5`, además de validación de tableros inválidos.

### 22. ¿Qué caso borde validaste?

Validé `n = 1`, `n = 2`, `n = 3`, `n = 0` y `n < 0`.

### 23. ¿Qué error tuviste y cómo lo corregiste?

Un error común en esta solución sería calcular mal la diagonal principal. Se corrige usando `row - col + n - 1`, lo que desplaza el rango a `[0, 2n - 2]`.

### 24. ¿Qué resultado muestra que tu implementación sí funciona?

Para `n = 4` devuelve exactamente dos soluciones válidas. Para `n = 5` devuelve diez soluciones válidas.

### 25. ¿Qué cambio pequeño podrías hacer sin romper la solución?

Podría cambiar el demo para imprimir solo la cantidad de soluciones o para activar trazas sin tocar el algoritmo de backtracking.
