# PC3 - CC232

## Estudiante
- Nombre: Alvaro Raul Montoya Dulanto
- Código: 20244154A

## Problema asignado
LeetCode 218 - The Skyline Problem  
https://leetcode.com/problems/the-skyline-problem/


## Descripción del problema
Se reciben edificios como intervalos:

[left, right, height]

El objetivo es construir el contorno superior (skyline) que resulta de la superposición de todos los edificios.

La salida es una lista de puntos clave [x, y] donde cambia la altura.


## Idea de solución
Se utiliza un enfoque de Sweep Line.

Cada edificio se transforma en dos eventos:
- inicio: (x = left, +height)
- fin: (x = right, -height)

Los eventos se procesan en orden de coordenada X.


## Algoritmo
1. Convertir edificios en eventos
2. Ordenar eventos por X
3. Mantener un heap de máximos con alturas activas
4. Usar lazy deletion para eliminar alturas inválidas
5. Detectar cambios en la altura máxima
6. Guardar puntos del skyline


## Estructuras utilizadas

### Max Heap
Mantiene la altura máxima activa en cada punto del barrido.

### Hash Map (lazy deletion)
Marca alturas eliminadas sin borrarlas directamente del heap.

### Vector de eventos
Almacena todos los inicios y finales de edificios.


## Relación con el curso (Semanas 4–6)
- Semana 4: simulación de eventos y estructuras lineales
- Semana 5: ordenamiento y manejo de intervalos
- Semana 6: heaps, priority queue, lazy deletion


## Invariante
El heap siempre contiene todas las alturas activas o pendientes de eliminación.

La cima del heap representa la altura máxima válida en el punto actual.


## Complejidad
- Tiempo: O(n log n)
- Espacio: O(n)


## Casos borde
- un solo edificio
- edificios completamente solapados
- múltiples eventos en el mismo X
- alturas repetidas consecutivas
- caída final a 0


## Pruebas
Se validan:
- casos mínimos
- solapamientos
- cambios múltiples en el mismo punto
- casos extremos


## Estructura del proyecto
- include/
- src/
- tests/
- demos/
- resultados/
- docs/

## Compilación 
```bash
cmake -S . -B build
cmake --build build

## Ejecución 
./build/pc3

## Tests
ctest --test-dir build

## Evidencia reproducible
- resultados/ejecucion_pc3.txt
- resultados/tests_pc3.txt
- resultados/casos_borde.txt

## Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.




