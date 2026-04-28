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
