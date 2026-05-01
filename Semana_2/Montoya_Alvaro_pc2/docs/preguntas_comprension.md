# Preguntas de comprensión

### 1. ¿Cuál es el invariante antes y después de cada operación?

Antes de `backtrack(row)`, las filas `0..row-1` están correctamente ocupadas y no tienen conflictos. Después de `placeQueen`, el invariante vale para una fila más. Después de `removeQueen`, el estado vuelve al que existía antes de probar esa columna.

### 2. ¿Qué línea o bloque del código asegura ese invariante?

Los bloques `placeQueen` y `removeQueen` aseguran el invariante porque actualizan el tablero, la columna y ambas diagonales de forma simétrica.

### 3. ¿Qué pasaría si cambias esa línea?

Si se marca o desmarca una diagonal incorrecta, el algoritmo puede aceptar tableros inválidos o podar soluciones válidas.

### 4. ¿Dónde se actualiza el tamaño lógico?

En la solución principal no hay un tamaño lógico manual. `solutions_` crece con `push_back` cuando se encuentra una solución. En las actividades de arreglo dinámico sí existe `size_`.

### 5. ¿Qué diferencia hay entre tamaño lógico y capacidad?

El tamaño lógico es la cantidad de elementos usados. La capacidad es el espacio reservado. En `std::vector`, la capacidad puede ser mayor que el tamaño para permitir crecimiento amortizado.

### 6. ¿Qué ocurre si un índice queda fuera de rango?

En el backtracking no debería ocurrir porque `row` va de `0` a `n` y `col` de `0` a `n - 1`. Las diagonales se transforman para caer en `[0, 2n - 2]`.

### 7. ¿Cómo detectas un caso inválido?

En una casilla se detecta conflicto con `canPlace`. En un tablero ya construido, `isValidBoard` rechaza tamaños incorrectos, caracteres inválidos, filas sin una reina o conflictos.

### 8. ¿Qué parte sería distinta si la estructura fuera enlazada en lugar de contigua?

Consultar `board[row][col]` y acceder a arreglos de diagonales sería más lento o más incómodo. Las listas enlazadas no ofrecen acceso directo por índice.

### 9. ¿Qué parte sería distinta si la estructura fuera contigua en lugar de enlazada?

La solución ya usa estructuras contiguas. Esto favorece acceso directo y buena localidad de memoria.

### 10. ¿Qué error de memoria o puntero podría aparecer aquí?

La solución principal usa `std::vector` y `std::string`, por lo que evita manejo manual de memoria. En las actividades con punteros, un error posible sería no actualizar `tail_` al borrar el último nodo.

### 11. ¿Qué hace tu solución mejor que una simulación simple?

No espera a construir un tablero completo para verificar. Detecta conflictos inmediatamente y poda ramas.

### 12. ¿Qué subrutina podrías reutilizar en otro problema?

`backtrack` como patrón general, `canPlace` como verificador de restricciones y `isValidBoard` como validador observable.

### 13. ¿Tu solución depende del lenguaje o de la idea algorítmica?

Depende de la idea algorítmica. En otro lenguaje se podría usar el mismo estado: tablero, columnas y diagonales.

### 14. ¿Qué pasa si duplicas el tamaño de la entrada?

El tiempo no se duplica; crece de forma combinatoria. Por eso la poda es importante, aunque no elimina el carácter exponencial.

### 15. ¿Qué prueba te daría más confianza antes de entregar?

Comparar los conteos conocidos para varios `n`, validar cada tablero con `isValidBoard` y ejecutar `ctest` para todos los casos.