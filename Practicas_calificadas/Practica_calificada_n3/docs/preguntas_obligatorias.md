# Respuestas obligatorias - PC3 CC232

# 1. Problema asignado

Se implementa la solución del problema:

**LeetCode 218 - The Skyline Problem**

El objetivo es construir el contorno superior de un conjunto de edificios representados como intervalos.

# 2. Entrada y salida

## Entrada
Lista de edificios:
[left, right, height]

## Salida
Lista de puntos clave:
[x,y]

donde cada punto indica un cambio en la altura del skyline.


# 3. Restricción clave del problema

Una solución ingenua recalcula la altura en cada punto del eje X, lo cual resulta ineficiente:

O(n * X)

donde X es el rango total del eje.

Esto no escala para entradas grandes.


# 4. Idea de solución

Se utiliza un enfoque de:

Sweep Line + Max Heap + Lazy Deletion

Cada edificio se transforma en eventos:

- inicio: (+height)
- fin: (-height)

Se procesan en orden de coordenada X.


# 5. Estructura elegida

Se utiliza:

- Max Heap → mantener alturas activas
- HashMap → marcar eliminaciones (lazy deletion)
- Vector de eventos → procesamiento ordenado


# 6. Justificación de la estructura

El heap permite obtener la altura máxima en O(1), mientras que las inserciones/eliminaciones son O(log n).

La eliminación directa en heap no es eficiente, por lo que se usa lazy deletion.


# 7. Operación dominante

La operación más costosa es:

- inserción en heap → O(log n)
- limpieza de heap → O(log n)


# 8. Invariante del algoritmo

En todo momento:

> El heap contiene todas las alturas activas o pendientes de eliminación.

Y:

> La cima del heap representa la altura máxima válida en la posición actual del sweep line.


# 9. Ubicación del invariante en el código

El invariante se mantiene en:

- `getSkyline()`
- `cleanHeap()`

Cada vez que se procesa un evento se actualiza la estructura y se restaura consistencia.


# 10. Casos borde

- Un solo edificio
- Edificios completamente solapados
- Edificios con misma altura
- Eventos en la misma coordenada X
- Caída final a 0


# 11. Manejo de duplicados

Los duplicados no afectan la lógica porque:

- el heap puede contener repeticiones
- lazy deletion elimina inconsistencias progresivamente


# 12. Complejidad por operación

- Inserción en heap: O(log n)
- Eliminación lógica: O(1)
- Limpieza de heap: O(log n)


# 13. Complejidad total

O(nlog(n))

Justificación:

- n eventos
- cada evento implica operaciones logarítmicas en heap


# 14. Complejidad espacial

O(n)


Se almacena:

- eventos
- heap
- estructura de eliminación


# 15. Alternativa de estructura

Una alternativa sería usar:

- multiset en lugar de heap

Ventaja:
- eliminación directa O(log n)

Desventaja:
- mayor overhead constante
- menos alineado con estructura del curso (heap + invariantes)


# 16. Justificación de diseño

Este diseño sigue el principio:

> mantener una estructura dinámica que represente solo el estado activo del problema

En lugar de recomputar el skyline, se mantiene incrementalmente.

Esto reduce el problema de recomputación global a actualización local eficiente.


# 17. Conexión con estructuras del curso

- Semana 4: simulación de eventos
- Semana 5: ordenamiento de intervalos
- Semana 6: heap + priority queue + lazy deletion


# 18. Correctitud

El algoritmo es correcto porque:

1. Procesa eventos en orden creciente de X
2. Mantiene el conjunto activo correctamente
3. Siempre usa el máximo válido
4. Registra cambios solo cuando la altura cambia


