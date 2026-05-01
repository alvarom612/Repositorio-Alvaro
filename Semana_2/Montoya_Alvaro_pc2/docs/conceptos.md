# Conceptos conectados con N-Queens

## ADT vs implementación concreta

El problema no exige crear un ADT nuevo como `Stack` o `Deque`; exige resolver una búsqueda. Sin embargo, sí se distingue entre la idea abstracta y la implementación:

- Idea abstracta: estado parcial de un tablero con reinas no conflictivas.
- Implementación concreta: `std::vector<std::string>` para el tablero y arreglos `std::vector<char>` para columnas y diagonales ocupadas.

## Invariante de estructura

Antes de explorar una fila `row`, las filas anteriores contienen una reina válida y las estructuras auxiliares reflejan exactamente esas posiciones. Este invariante se mantiene con `placeQueen` y `removeQueen`.

## Complejidad temporal por operación

- Consultar conflicto: `O(1)`.
- Colocar reina: `O(1)`.
- Retirar reina: `O(1)`.
- Guardar una solución: `O(n^2)`, porque se copia el tablero completo.
- Explorar todas las ramas: cota `O(n * n!)`, más la copia de soluciones.

## Complejidad espacial

El tablero usa `O(n^2)`. Los arreglos de columnas y diagonales usan `O(n)`. La pila recursiva usa `O(n)`. La salida ocupa `O(S * n^2)`.

## Peor caso vs costo amortizado

El backtracking se analiza en peor caso. No depende de una operación amortizada central. Sí hay crecimiento amortizado interno en `std::vector` cuando se agregan soluciones, pero eso no cambia la idea principal: la explosión combinatoria domina.

## Memoria contigua vs memoria enlazada

La implementación usa memoria contigua mediante `std::vector` y `std::string`. Esto permite acceso directo por índice a tablero, columnas y diagonales. Una lista enlazada no ayudaría aquí porque se consultan posiciones por índice.

## `resize` y crecimiento de capacidad

`solutions_` crece dinámicamente al guardar respuestas. `std::vector` administra capacidad y puede hacer `resize` o realocación. En el núcleo del algoritmo se evita crecer y reducir estructuras en cada rama; se inicializan una vez en `reset`.

## Índices modulares

No se usan índices modulares porque el tablero no es circular. El acceso se mantiene dentro de `[0, n)`. El concepto sí aparece en estructuras como arreglos circulares o deques.

## Arreglo circular

No se usa arreglo circular en N-Queens. Sería apropiado para colas o deques, pero no para consultar conflictos en un tablero.

## Deque y doble extremo

No se usa `deque`. El algoritmo no necesita insertar o borrar en ambos extremos; necesita marcar y desmarcar conflictos en `O(1)`.

## Stack monotónica

No se usa stack monotónica. Ese patrón corresponde a problemas de vecinos menores/mayores, histogramas o ventanas, no a N-Queens.

## Ventana deslizante

No se usa ventana deslizante porque no hay un intervalo móvil sobre una secuencia; hay una búsqueda en árbol de decisiones.

## Prefijos o sumas prefixadas

No se usan sumas prefijadas. Los conflictos se detectan por columnas y diagonales, no por acumulados numéricos.

## Vecinos vivos y borrado eficiente

No se usa una estructura de vecinos vivos. No hay borrado de segmentos o nodos; se hace retroceso de decisiones.

## Lista simple vs doble

No se usa lista enlazada. Una lista simple o doble empeoraría el acceso por índice y no aporta ventajas para las verificaciones de conflicto.

## Nodo, punteros y relinkeo

No hay nodos propios ni relinkeo en la solución principal. Este concepto sí aparece en las actividades incluidas.

## `HashMap + doubly linked list`

No se usa porque no hay operaciones de recencia como en LRU Cache. N-Queens necesita poda por restricciones, no cache con recencia.

## Parsing con stack

No se usa parsing en N-Queens. Se incluye una actividad separada con stack para cubrir ese tema del curso.

## Backtracking

Es la técnica central. Se toma una decisión, se avanza recursivamente y luego se deshace la decisión para probar otra opción.

## Poda

La poda evita explorar una casilla si su columna o diagonales ya están ocupadas. Esto evita construir tableros que nunca podrán ser solución.

## Casos borde

- `n = 1`: una solución.
- `n = 2` y `n = 3`: cero soluciones.
- `n = 0` o negativo: entrada inválida para LeetCode, manejada como lista vacía.
- Tableros con caracteres distintos de `Q` o `.` son rechazados por el validador.

## Correctitud observable

Se observa mediante el número conocido de soluciones para varios `n` y mediante `isValidBoard`, que verifica que cada tablero guardado tenga exactamente una reina por fila y ningún conflicto.

## Casos de prueba

Las pruebas cubren conteos conocidos, validez de tableros, wrapper compatible con LeetCode, entradas vacías o inválidas y rechazo de tableros incorrectos.

## Separación `.h` y `.cpp`

La API pública está en `include/NQueensSolver.h`. La representación interna y el algoritmo están en `src/NQueensSolver.cpp`. Solo se usan cabeceras `.h`.

## API pública y representación interna

La API pública expone `solve`, `solveWithTrace` e `isValidBoard`. La representación interna queda privada: tablero, columnas, diagonales, soluciones y funciones auxiliares de backtracking.
