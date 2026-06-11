# Preguntas obligatorias - Skyline Problem (LeetCode 218)


## 1. ¿Cómo ordenas eventos que ocurren en la misma coordenada?

Los eventos en la misma coordenada X se ordenan con las siguientes reglas:

1. Primero los eventos de inicio (start) antes que los de fin (end).
2. Si ambos son de inicio, se prioriza la mayor altura primero.
3. Si ambos son de fin, se prioriza la menor altura primero.

Esto garantiza que el skyline se construya correctamente sin cortes incorrectos ni alturas intermedias inválidas.


## 2. ¿Por qué el heap puede contener edificios vencidos?

El heap puede contener alturas “vencidas” porque no se eliminan directamente al terminar un edificio.

En su lugar, se usa **lazy deletion**:

- Se marca la altura como eliminada en un hash map.
- Se mantiene en el heap hasta que llegue a la cima.
- Cuando aparece en el top, se elimina efectivamente.

Esto evita operaciones costosas de borrado en estructuras tipo priority_queue.


## 3. ¿Qué invariante mantiene la altura activa máxima?

El invariante principal es:

> En cualquier punto del sweep line, la cima del max heap representa la altura máxima de todos los edificios activos no eliminados.

Esto se garantiza porque:

- todos los eventos de inicio se insertan en el heap
- los eventos de fin se marcan como eliminados
- el heap se limpia antes de consultar la altura actual

Por lo tanto, el valor en `heap.top()` siempre es consistente con el skyline real en ese punto.


# Relación con implementación

Estas decisiones están implementadas en:

- `sortEvents()`: orden de procesamiento
- `getSkyline()`: construcción del skyline
- `cleanHeap()`: aplicación de lazy deletion


# Complejidad implícita

- Inserción en heap: O(log n)
- Limpieza amortizada: O(log n)
- Ordenamiento: O(n log n)


# Conclusión

El skyline se resuelve eficientemente usando:

- sweep line para ordenamiento espacial
- max heap para altura activa
- lazy deletion para eficiencia en eliminación

Esto permite evitar recalcular el perfil completo del skyline en cada punto.