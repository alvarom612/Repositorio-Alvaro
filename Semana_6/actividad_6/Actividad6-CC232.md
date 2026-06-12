## Actividad 6 - CC232

### Estudiante
- Nombre: Alvaro Raul Montoya Dulanto
- Código: 20244154A
- Fecha: 29/05/2026

---

## Resumen de modificaciones

| Bloque | Archivo modificado | Cambio realizado | Evidencia |
|---|---|---|---|
| 2 | `Semana6/include/PQ_ComplHeap_macro.h` | Se agregan funciones `constexpr` para hijos, hoja e interno. | Compilación y uso desde `percolateDown`. |
| 2 | `Semana6/include/PQ_ComplHeap_percolateDown.h` | Se reemplazan cálculos directos por auxiliares. | Demo de `delMax` y pruebas de heap. |
| 3 | `Semana6/include/PQ_ComplHeap_percolateUp.h` | Se agrega `complHeapPercolateUpCount`. | Demo con inserciones instrumentadas. |
| 4 | `Semana6/include/PQ_ComplHeap_percolateDown.h` | Se agrega `complHeapPercolateDownCount`. | Demo de eliminaciones instrumentadas. |
| 5 | `Semana6/include/PQ_ComplHeap.h` | Se agrega `isValidHeap()` o función libre equivalente. | Pruebas con vacío, repetidos, heapify y `delMax`. |
| 6 | `Semana6/demos/demo_heapify_floyd.cpp` | Comparación entre inserciones sucesivas y Floyd. | Tabla de arreglos finales y validación. |
| 7 | `Semana6/include/vector_heapSort.h` | Se agrega `heapSort(a, comp, ascending)`. | Demo ascendente y descendente con repetidos. |
| 8 | `Semana6/include/PQ_LeftHeap.h` | Se agrega `isValidLeftHeap()`. | Demo de `merge`, `insert` y `delMax`. |
| 9 | `Semana6/include/Huffman_PQ_generateTree.h` | Se documenta desempate y caso de un símbolo. | Tabla de códigos y prueba de prefijo libre. |
| 10 | `Semana6/include/Treap.h` | Se agregan contadores de rotaciones, validaciones y operaciones controladas. | Demo determinística y pruebas. |
| 11 | `Semana6/demos/demo_compare_with_semana5.cpp` | Comparación observable entre heap, PQ, BST y Treap. | Tabla comparativa. |
| 12 | `Semana6/pruebas_publicas/test_public_week6.cpp` y `Semana6/pruebas_internas/test_internal_week6.cpp` | Se amplían pruebas de invariantes y casos borde. | `ctest --output-on-failure`. |

---

# Bloque 1 - Diagnóstico inicial

### Comandos iniciales

| Comando ejecutado | Resultado | Error si hubo | Interpretación |
|---|---|---|---|
| `cmake -S . -B build` | **Pendiente de ejecutar localmente** | N/A | Debe configurar los targets de Semana 6 y reutilizar cabeceras de Semana 5. |
| `cmake --build build` | **Pendiente de ejecutar localmente** | N/A | Debe compilar demos y pruebas. |
| `ctest --test-dir build --output-on-failure` | **Pendiente de ejecutar localmente** | N/A | Sirve como línea base antes de modificar código. |

### Targets esperados de Semana 6

Los targets de demostración esperados, según el material, son:

- `demo_pq_complheap_basico`
- `demo_heapify_floyd`
- `demo_heapsort`
- `demo_left_heap_merge`
- `demo_huffman`
- `demo_compare_with_semana5`
- `demo_bst_rotations`
- `demo_treap_basico`
- `demo_capitulo6_panorama`
- pruebas públicas e internas de Semana 6.

### Archivos incluidos desde `Capitulo6.h`

`Capitulo6.h` debe actuar como cabecera panorámica del capítulo de colas de prioridad. Conceptualmente incluye o agrupa:

- interfaz `PQ`;
- heap binario completo `PQ_ComplHeap`;
- operaciones `getMax`, `insert`, `delMax`;
- `percolateUp`, `percolateDown`;
- `heapifyFloyd`;
- `heapSort`;
- heap izquierdista `PQ_LeftHeap`;
- Huffman basado en PQ.

### Diferencia entre `Capitulo6.h` y `Capitulo10.h`

`Capitulo6.h` agrupa estructuras de prioridad pura: heaps, colas de prioridad y aplicaciones como Huffman. `Capitulo10.h` se relaciona con estructuras de búsqueda ordenada avanzadas o híbridas, en particular Treap, que mezcla propiedad BST sobre claves y propiedad heap sobre prioridades.

### Dependencia conceptual de Semana 5

Semana 6 depende de Semana 5 porque compara:

- `BinaryHeap` con `PQ_ComplHeap`;
- `BinarySearchTree` con `Treap`;
- recorridos de `BinaryTree` con recorridos de BST/Treap;
- rotaciones de BST con rotaciones usadas por Treap.

### Estructuras por propósito

| Pregunta | Respuesta |
|---|---|
| ¿Qué estructura se usa para prioridad pura? | `PQ_ComplHeap`, `PQ_LeftHeap`, `BinaryHeap`. |
| ¿Qué estructura se usa para búsqueda ordenada? | `BinarySearchTree`. |
| ¿Qué estructura mezcla búsqueda ordenada con prioridad? | `Treap`. |
| ¿Qué evidencia inicial se obtiene sin modificar nada? | Compilación, demos y pruebas base. Deben guardarse las salidas reales de `ctest`. |

### Archivos planeados para modificar

1. `Semana6/include/PQ_ComplHeap_macro.h`
2. `Semana6/include/PQ_ComplHeap_percolateUp.h`
3. `Semana6/include/PQ_ComplHeap_percolateDown.h`
4. `Semana6/include/PQ_ComplHeap.h`
5. `Semana6/include/vector_heapSort.h`
6. `Semana6/include/PQ_LeftHeap.h`
7. `Semana6/include/Huffman_PQ_generateTree.h`
8. `Semana6/include/Treap.h`
9. `Semana6/demos/demo_pq_complheap_basico.cpp`
10. `Semana6/demos/demo_heapify_floyd.cpp`
11. `Semana6/demos/demo_heapsort.cpp`
12. `Semana6/demos/demo_left_heap_merge.cpp`
13. `Semana6/demos/demo_huffman.cpp`
14. `Semana6/demos/demo_treap_basico.cpp`
15. `Semana6/demos/demo_compare_with_semana5.cpp`
16. `Semana6/pruebas_publicas/test_public_week6.cpp`
17. `Semana6/pruebas_internas/test_internal_week6.cpp`

---

# Bloque 2 - Utilidades de heap completo

## Código propuesto para `PQ_ComplHeap_macro.h`

```cpp
#pragma once
#include <cstddef>

// MOD-A6-B2: utilidades constexpr para heap implícito sin macros.

constexpr std::size_t pqParent(std::size_t i) {
    return (i - 1) / 2;
}

constexpr std::size_t pqLeftChild(std::size_t i) {
    return 2 * i + 1;
}

constexpr std::size_t pqRightChild(std::size_t i) {
    return 2 * i + 2;
}

constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) {
    return pqLeftChild(i) < n;
}

constexpr bool pqHasRightChild(std::size_t i, std::size_t n) {
    return pqRightChild(i) < n;
}

constexpr bool pqIsLeaf(std::size_t i, std::size_t n) {
    return !pqHasLeftChild(i, n);
}

constexpr bool pqIsInternal(std::size_t i, std::size_t n) {
    return pqHasLeftChild(i, n);
}
```

## Uso en `percolateDown`

```cpp
// MOD-A6-B2: percolateDown expresado con utilidades constexpr.
// Convención: comp(a, b) es true si b tiene mayor prioridad que a.
// Con std::less<T>, esto implementa max-heap.

template<class T, class Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a,
                                   std::size_t n,
                                   std::size_t i,
                                   Compare comp) {
    while (pqIsInternal(i, n)) {
        std::size_t child = pqLeftChild(i);

        if (pqHasRightChild(i, n) && comp(a[child], a[pqRightChild(i)])) {
            child = pqRightChild(i);
        }

        if (!comp(a[i], a[child])) {
            break;
        }

        std::swap(a[i], a[child]);
        i = child;
    }
    return i;
}
```

## Respuestas

**¿Por qué conviene expresar `parent`, `left`, `right` y pruebas de frontera como funciones pequeñas?**  
Porque centralizan la aritmética de la representación implícita. Así se evita repetir fórmulas, disminuye el riesgo de errores de índice y se vuelve más claro qué relación del árbol se está usando.

**¿Qué ventaja tiene `constexpr` frente a macros?**  
`constexpr` respeta tipos, alcance y depuración de C++. Una macro solo sustituye texto y puede producir errores difíciles de rastrear. Además, una función `constexpr` puede evaluarse en compilación cuando sus argumentos son constantes.

**¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?**  
Puede ocurrir en el último nodo interno de un heap completo. En ese caso, no se debe consultar el hijo derecho porque estaría fuera del vector; se compara solo contra el hijo izquierdo.

**¿Qué condición identifica una hoja en la representación implícita?**  
Un nodo `i` es hoja si `2*i + 1 >= n`, es decir, si no tiene hijo izquierdo. En un heap completo no puede existir hijo derecho sin hijo izquierdo.

**¿Qué cambió en `percolateDown` después de usar las funciones auxiliares?**  
No cambió el algoritmo ni el costo. Cambió la legibilidad: ahora el código expresa “tiene hijo izquierdo”, “tiene hijo derecho” y “es interno” en vez de mezclar la lógica con fórmulas aritméticas.

**Complejidad:**  
La complejidad sigue siendo `O(log n)` en el peor caso, porque el elemento puede bajar a lo sumo la altura del heap.

**Evidencia de compilación:**  
Pendiente de reemplazar con salida real:

```text
cmake --build build
[100%] Built target ...
```

---

# Bloque 3 - Conteo en `percolateUp`

## Función nueva

```cpp
// MOD-A6-B3: versión instrumentada de percolateUp.

template<class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a,
                                      std::size_t i,
                                      Compare comp) {
    std::size_t swaps = 0;

    while (i > 0) {
        std::size_t p = pqParent(i);

        if (!comp(a[p], a[i])) {
            break;
        }

        std::swap(a[p], a[i]);
        i = p;
        ++swaps;
    }

    return swaps;
}
```

## Demo sugerida

```cpp
// MOD-A6-B3: demo de inserciones instrumentadas.
std::vector<int> heap;
std::vector<int> values = {40, 10, 70, 30, 90, 20, 80, 60};

for (int x : values) {
    heap.push_back(x);
    std::size_t swaps =
        complHeapPercolateUpCount(heap, heap.size() - 1, std::less<int>{});

    std::cout << "insertado=" << x
              << " swaps=" << swaps
              << " heap=" << heap
              << " valido=" << std::boolalpha
              << complHeapIsValid(heap, std::less<int>{})
              << '\n';
}
```

## Salida esperada razonable

| Insertado | Intercambios | Arreglo interno resultante | ¿Heap válido? |
|---:|---:|---|---|
| 40 | 0 | `[40]` | sí |
| 10 | 0 | `[40, 10]` | sí |
| 70 | 1 | `[70, 10, 40]` | sí |
| 30 | 1 | `[70, 30, 40, 10]` | sí |
| 90 | 2 | `[90, 70, 40, 10, 30]` | sí |
| 20 | 0 | `[90, 70, 40, 10, 30, 20]` | sí |
| 80 | 1 | `[90, 70, 80, 10, 30, 20, 40]` | sí |
| 60 | 1 | `[90, 70, 80, 60, 30, 20, 40, 10]` | sí |

## Respuestas

**¿En qué casos `percolateUp` hace cero intercambios?**  
Cuando el elemento insertado no tiene mayor prioridad que su padre o cuando se inserta como raíz.

**¿En qué casos puede hacer `O(log n)` intercambios?**  
Cuando el elemento insertado tiene mayor prioridad que todos sus ancestros y sube desde una hoja hasta la raíz.

**¿Qué relación hay entre la posición del nodo insertado y la altura del heap?**  
El nuevo elemento se inserta al final del vector, que corresponde a la siguiente posición libre del árbol completo. Su número máximo de ascensos es la profundidad de esa posición, que es `O(log n)`.

**¿Por qué el arreglo interno no necesariamente queda ordenado?**  
Porque el heap solo garantiza prioridad padre-hijo. No exige que los hermanos estén ordenados ni que el vector completo esté en orden ascendente o descendente.

**¿Qué propiedad sí queda garantizada?**  
En un max-heap, cada padre tiene prioridad mayor o igual que sus hijos. Por eso el máximo queda en la raíz.

---

# Bloque 4 - Conteo en `percolateDown`

## Función instrumentada

```cpp
// MOD-A6-B4: versión instrumentada de percolateDown.

template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a,
                                        std::size_t n,
                                        std::size_t i,
                                        Compare comp) {
    std::size_t swaps = 0;

    while (pqIsInternal(i, n)) {
        std::size_t child = pqLeftChild(i);

        if (pqHasRightChild(i, n) && comp(a[child], a[pqRightChild(i)])) {
            child = pqRightChild(i);
        }

        if (!comp(a[i], a[child])) {
            break;
        }

        std::swap(a[i], a[child]);
        i = child;
        ++swaps;
    }

    return swaps;
}
```

## Demo sugerida

```cpp
// MOD-A6-B4: demo de eliminaciones instrumentadas.
std::vector<int> heap = {90, 70, 80, 60, 30, 20, 40, 10};

while (!heap.empty()) {
    int maxValue = heap.front();

    std::swap(heap.front(), heap.back());
    heap.pop_back();

    std::cout << "eliminado=" << maxValue
              << " antes_reparar=" << heap << '\n';

    std::size_t swaps = 0;
    if (!heap.empty()) {
        swaps = complHeapPercolateDownCount(heap, heap.size(), 0, std::less<int>{});
    }

    std::cout << "swaps=" << swaps
              << " despues_reparar=" << heap
              << " valido=" << complHeapIsValid(heap, std::less<int>{})
              << '\n';
}
```

## Salida esperada aproximada

| Máximo eliminado | Arreglo antes de reparar | Intercambios | Arreglo después de reparar |
|---:|---|---:|---|
| 90 | `[10,70,80,60,30,20,40]` | 2 | `[80,70,40,60,30,20,10]` |
| 80 | `[10,70,40,60,30,20]` | 2 | `[70,60,40,10,30,20]` |
| 70 | `[20,60,40,10,30]` | 1 | `[60,30,40,10,20]` |
| 60 | `[20,30,40,10]` | 1 | `[40,30,20,10]` |
| 40 | `[10,30,20]` | 1 | `[30,10,20]` |
| 30 | `[20,10]` | 0 | `[20,10]` |
| 20 | `[10]` | 0 | `[10]` |
| 10 | `[]` | 0 | `[]` |

## Trazado manual de una eliminación

Heap inicial: `[90, 70, 80, 60, 30, 20, 40, 10]`.

1. Se elimina `90`.
2. Se mueve el último elemento `10` a la raíz.
3. Queda `[10, 70, 80, 60, 30, 20, 40]`.
4. Se compara `10` con sus hijos `70` y `80`; domina `80`.
5. Se intercambia `10` con `80`: `[80, 70, 10, 60, 30, 20, 40]`.
6. Ahora `10` tiene hijos `20` y `40`; domina `40`.
7. Se intercambia `10` con `40`: `[80, 70, 40, 60, 30, 20, 10]`.
8. El nodo queda como hoja; la propiedad heap se restauró.

## Respuestas

**¿Por qué después de `delMax` se mueve el último elemento a la raíz?**  
Porque al quitar la raíz se genera un hueco. Mover el último elemento mantiene la forma de árbol completo sin dejar huecos internos.

**¿Por qué la reparación baja y no sube?**  
El único posible conflicto queda entre la nueva raíz y sus hijos. Como se colocó arriba un elemento que antes estaba al final, puede tener menor prioridad que sus descendientes; por eso debe bajar.

**¿Cómo se decide entre hijo izquierdo e hijo derecho?**  
Se elige el hijo dominante: en un max-heap, el hijo con mayor valor según el comparador.

**¿Qué pasa si el nodo actual tiene un solo hijo?**  
Se compara solo con ese hijo. El algoritmo no debe acceder al hijo derecho si no existe.

**¿Por qué `delMax` tiene costo `O(log n)`?**  
Porque el elemento movido a la raíz puede bajar como máximo una cantidad de niveles igual a la altura del heap, que es `O(log n)`.

---

# Bloque 5 - Validación explícita de la propiedad heap

## Función libre

```cpp
// MOD-A6-B5: validación explícita de la propiedad heap.

template<class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
    const std::size_t n = a.size();

    for (std::size_t i = 0; i < n; ++i) {
        const std::size_t l = pqLeftChild(i);
        const std::size_t r = pqRightChild(i);

        if (l < n && comp(a[i], a[l])) {
            return false;
        }

        if (r < n && comp(a[i], a[r])) {
            return false;
        }
    }

    return true;
}
```

## Método dentro de `PQ_ComplHeap`

```cpp
// MOD-A6-B5: método de validación dentro de la clase.
bool isValidHeap() const {
    return complHeapIsValid(_elem, _comp);
}
```

## Pruebas agregadas

```cpp
// MOD-A6-B5: pruebas de validez de heap.

TEST(PQComplHeapExtra, ValidEmptyAndSingle) {
    PQ_ComplHeap<int> pq;
    EXPECT_TRUE(pq.isValidHeap());
    pq.insert(10);
    EXPECT_TRUE(pq.isValidHeap());
}

TEST(PQComplHeapExtra, ValidWithRepeatedValues) {
    PQ_ComplHeap<int> pq;
    for (int x : {5, 5, 5, 3, 3, 8, 8}) {
        pq.insert(x);
        EXPECT_TRUE(pq.isValidHeap());
    }
}

TEST(PQComplHeapExtra, ValidAfterSeveralDeletes) {
    PQ_ComplHeap<int> pq;
    for (int x : {4, 17, 3, 90, 55, 21, 8}) {
        pq.insert(x);
    }

    while (!pq.empty()) {
        EXPECT_TRUE(pq.isValidHeap());
        pq.delMax();
        EXPECT_TRUE(pq.isValidHeap());
    }
}
```

## Respuestas

**¿Qué invariante verifica la función?**  
Verifica que ningún hijo tenga mayor prioridad que su padre. En un max-heap, eso significa que cada padre es mayor o igual que sus hijos.

**¿Por qué basta revisar relaciones padre-hijo?**  
Porque la propiedad heap es local. Si todos los enlaces padre-hijo cumplen la prioridad, entonces por transitividad ningún descendiente puede superar a todos sus ancestros.

**¿Por qué no es necesario comparar cada nodo con todos sus descendientes?**  
Porque sería redundante. Si `padre >= hijo` y `hijo >= nieto`, entonces `padre >= nieto`.

**¿Cuál es el costo de validar todo el heap?**  
`O(n)`, porque se revisa cada nodo y como máximo dos hijos.

**¿Por qué esta función es útil en pruebas pero no necesariamente en producción?**  
En producción agregaría un costo lineal después de operaciones que ya deberían mantener el invariante. En pruebas es útil porque detecta errores de implementación.

**Evidencia de `ctest`:**

```text
ctest --test-dir build --output-on-failure
# Pendiente de reemplazar con salida real.
```

---

# Bloque 6 - Inserciones sucesivas vs Floyd

## Demo modificada

Entrada:

```cpp
std::vector<int> input = {4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89};
```

Construcción A:

```cpp
// MOD-A6-B6: construcción por inserciones.
std::vector<int> byInsert;
std::size_t insertSwaps = 0;

for (int x : input) {
    byInsert.push_back(x);
    insertSwaps += complHeapPercolateUpCount(
        byInsert, byInsert.size() - 1, std::less<int>{});
}
```

Construcción B:

```cpp
// MOD-A6-B6: construcción por Floyd.
std::vector<int> byFloyd = input;
std::size_t floydSwaps = complHeapifyFloydCount(byFloyd, std::less<int>{});
```

Si no se implementa `complHeapifyFloydCount`, se puede mostrar solo la validación.

## Tabla comparativa esperada

| Construcción | Arreglo inicial | Arreglo final | Intercambios | ¿Heap válido? |
|---|---|---|---:|---|
| Inserciones sucesivas | `[4,17,3,90,55,21,8,13,34,2,1,89]` | Depende del orden de ascensos | Exacto si se usa contador | sí |
| Floyd | `[4,17,3,90,55,21,8,13,34,2,1,89]` | Puede ser distinto al anterior | Exacto si se instrumenta | sí |

## Respuestas

**¿Por qué ambos resultados pueden ser heaps válidos aunque sus arreglos finales no sean idénticos?**  
Porque la propiedad heap no define un único arreglo. Solo exige prioridad padre-hijo. Hay muchas configuraciones válidas para los mismos elementos.

**¿Por qué insertar `n` elementos puede costar `O(n log n)`?**  
Cada inserción puede ejecutar `percolateUp` hasta la raíz, con costo `O(log n)`. Repetido `n` veces da `O(n log n)`.

**¿Por qué Floyd puede construir el heap en `O(n)`?**  
Porque aplica `percolateDown` desde los últimos nodos internos hacia la raíz. La mayoría de nodos están cerca de las hojas y bajan poco. La suma total de alturas procesadas es lineal.

**¿Qué nodos procesa Floyd primero?**  
Procesa desde el último nodo interno, índice `(n/2) - 1`, hasta la raíz.

**¿Por qué Floyd no necesita llamar a `percolateDown` desde las hojas?**  
Porque una hoja ya cumple trivialmente la propiedad heap: no tiene hijos con los cuales violar prioridad.

---

# Bloque 7 - `heapSort`

## Código propuesto

```cpp
// MOD-A6-B7: núcleo de heapsort in situ.

template<class T, class Compare>
void heapSortImpl(std::vector<T>& a, Compare comp) {
    const std::size_t n = a.size();
    if (n < 2) return;

    // Construir heap.
    for (std::size_t i = n / 2; i > 0; --i) {
        complHeapPercolateDown(a, n, i - 1, comp);
    }

    // Extraer raíz hacia el sufijo final.
    for (std::size_t heapSize = n; heapSize > 1; --heapSize) {
        std::swap(a[0], a[heapSize - 1]);
        complHeapPercolateDown(a, heapSize - 1, 0, comp);
    }
}

template<class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
    if (ascending) {
        // Con std::less, el máximo se mueve al final y queda ascendente.
        heapSortImpl(a, comp);
    } else {
        // Para descendente, se invierte la prioridad.
        auto reverseComp = [comp](const T& x, const T& y) {
            return comp(y, x);
        };
        heapSortImpl(a, reverseComp);
    }
}
```

## Prueba con repetidos

Entrada:

```text
[5, 1, 5, 3, 8, 2, 8, 0]
```

| Sentido | Resultado esperado |
|---|---|
| Ascendente | `[0, 1, 2, 3, 5, 5, 8, 8]` |
| Descendente | `[8, 8, 5, 5, 3, 2, 1, 0]` |

## Respuestas

**¿Por qué heapsort puede ordenar in situ?**  
Porque usa el mismo arreglo como heap y luego como zona ordenada. No necesita una estructura auxiliar proporcional a `n`.

**¿Qué parte del algoritmo destruye gradualmente el heap?**  
Cada intercambio de la raíz con el último elemento del heap reduce `heapSize`. El sufijo final queda ordenado y ya no pertenece al heap activo.

**¿Por qué heapsort cuesta `O(n log n)`?**  
La construcción con Floyd cuesta `O(n)`, pero luego hay `n - 1` extracciones, cada una con `percolateDown` de costo `O(log n)`.

**¿Es heapsort estable?**  
No. Dos elementos iguales pueden intercambiar su orden relativo debido a los swaps con la raíz y los swaps internos de `percolateDown`. Por ejemplo, si se distinguen `5a` y `5b`, pueden salir en orden invertido.

**¿Qué diferencia hay entre usar `heapSort` y extraer todos los elementos con `delMax`?**  
Ambos usan la idea de heap, pero `heapSort` reutiliza el arreglo in situ. Extraer con `delMax` normalmente produce una secuencia externa o destruye una cola de prioridad separada.

---

# Bloque 8 - Heap izquierdista

## Validación propuesta

```cpp
// MOD-A6-B8: validación recursiva de heap izquierdista.
// Adaptar nombres de campos: data, left, right, npl, etc.

struct LeftCheckResult {
    bool ok;
    std::size_t size;
    int npl;
};

LeftCheckResult checkLeftHeap(Node* u) const {
    if (u == nullptr) {
        return {true, 0, -1};
    }

    auto L = checkLeftHeap(u->left);
    auto R = checkLeftHeap(u->right);

    bool heapOk = true;
    if (u->left  && _comp(u->data, u->left->data))  heapOk = false;
    if (u->right && _comp(u->data, u->right->data)) heapOk = false;

    bool leftistOk = L.npl >= R.npl;
    int expectedNpl = 1 + std::min(L.npl, R.npl);
    bool nplOk = (u->npl == expectedNpl);

    return {L.ok && R.ok && heapOk && leftistOk && nplOk,
            1 + L.size + R.size,
            expectedNpl};
}

bool isValidLeftHeap() const {
    auto r = checkLeftHeap(_root);
    return r.ok && r.size == _size;
}
```

## Demo de `merge`

```cpp
// MOD-A6-B8: validación después de merge.
PQ_LeftHeap<int> a;
PQ_LeftHeap<int> b;

for (int x : {50, 20, 40}) a.insert(x);
for (int x : {60, 10, 30}) b.insert(x);

std::cout << "a valido=" << a.isValidLeftHeap() << '\n';
std::cout << "b valido=" << b.isValidLeftHeap() << '\n';

a.merge(b);

std::cout << "merge valido=" << a.isValidLeftHeap() << '\n';
std::cout << "max=" << a.getMax() << '\n';
```

## Trazado de fusión pequeña

Se fusionan dos heaps con raíces `50` y `60`. Como es max-heap, `60` domina y queda como raíz. Luego se fusiona el subárbol derecho de `60` con el heap de raíz `50`. Al terminar, si la distancia nula del hijo izquierdo es menor que la del derecho, se intercambian hijos para restaurar la propiedad izquierdista.

## Respuestas

**¿Por qué `merge` es la operación central del heap izquierdista?**  
Porque `insert` se implementa fusionando con un heap de un solo nodo y `delMax` se implementa fusionando los dos subárboles de la raíz eliminada.

**¿Cómo se implementa `insert` usando `merge`?**  
Se crea un heap temporal con el nuevo elemento y se fusiona con el heap actual.

**¿Cómo se implementa `delMax` usando `merge`?**  
Se elimina la raíz y se fusionan su subárbol izquierdo y derecho.

**¿Qué propiedad adicional diferencia un heap izquierdista de un heap binario completo?**  
Además de la propiedad heap, mantiene una propiedad de distancia nula: el camino más corto hacia un nodo nulo debe estar preferentemente por la derecha, y el subárbol izquierdo debe tener `npl` mayor o igual que el derecho.

**¿Qué ventaja conceptual tiene frente a un heap binario completo?**  
Permite fusionar heaps eficientemente. En un heap binario completo representado en arreglo, fusionar dos heaps no es una operación natural de bajo costo.

---

# Bloque 9 - Huffman

## Modificación de desempate

Para que el resultado sea determinístico, cada nodo de Huffman puede guardar:

- frecuencia;
- símbolo si es hoja;
- menor símbolo del subárbol;
- número de creación o `id`.

Comparador sugerido:

```cpp
// MOD-A6-B9: desempate determinístico para Huffman.
struct HuffmanCompare {
    bool operator()(const Node* a, const Node* b) const {
        if (a->freq != b->freq) {
            return a->freq > b->freq; // min-priority usando cola invertida
        }
        if (a->minSymbol != b->minSymbol) {
            return a->minSymbol > b->minSymbol;
        }
        return a->id > b->id;
    }
};
```

## Caso de un símbolo

```cpp
// MOD-A6-B9: caso extremo de un solo símbolo.
if (root && root->isLeaf()) {
    codes[root->symbol] = "0";
    return codes;
}
```

## Tabla para `{A:5, B:5, C:10, D:10, E:20}`

Un conjunto válido de códigos, dependiendo del desempate, es:

| Símbolo | Frecuencia | Código | Longitud |
|---|---:|---|---:|
| A | 5 | `000` | 3 |
| B | 5 | `001` | 3 |
| C | 10 | `01` | 2 |
| D | 10 | `10` | 2 |
| E | 20 | `11` | 2 |

Longitud ponderada:

```text
5*3 + 5*3 + 10*2 + 10*2 + 20*2 = 110
```

## Caso de un símbolo

| Símbolo | Frecuencia | Código | Longitud |
|---|---:|---|---:|
| X | 100 | `0` | 1 |

## Verificación de prefijo libre

Un conjunto de códigos es libre de prefijos si ningún código completo aparece como prefijo de otro. En la tabla anterior, `000`, `001`, `01`, `10` y `11` no violan esa condición.

## Respuestas

**¿Por qué Huffman necesita una cola de prioridad?**  
Porque en cada paso necesita extraer los dos nodos de menor frecuencia.

**¿Qué elementos se extraen repetidamente?**  
Los dos árboles o nodos con menor frecuencia acumulada.

**¿Qué nodo se vuelve a insertar?**  
Un nodo interno cuya frecuencia es la suma de las dos frecuencias extraídas.

**¿Por qué el caso de un solo símbolo requiere cuidado especial?**  
Porque si no hay bifurcación, el recorrido normal podría asignar cadena vacía. Para codificar bits reales, se asigna un código como `"0"`.

**¿Qué significa que el conjunto de códigos sea libre de prefijos?**  
Que ningún código es prefijo de otro, lo cual permite decodificación no ambigua de izquierda a derecha.

**¿Cómo afecta el desempate a la forma del árbol?**  
Puede cambiar qué símbolos quedan a izquierda o derecha y, en empates, qué subárbol se combina primero.

**¿El desempate cambia necesariamente la longitud total ponderada?**  
No necesariamente. Si solo rompe empates entre frecuencias iguales, puede producir árboles distintos con el mismo costo óptimo total.

---

# Bloque 10 - Treap

## Parte A - Construcción determinística con prioridades fijas

Secuencia:

```text
{ {50,50}, {30,30}, {70,70}, {20,20}, {40,40}, {60,60}, {80,80} }
```

Como en esta implementación una prioridad menor sube, se rota mientras el padre tiene prioridad mayor que el nodo insertado.

## Demo sugerida

```cpp
// MOD-A6-B10A: demo determinística con prioridades fijas.
Treap<int> tr;

std::vector<std::pair<int, std::uint64_t>> seq = {
    {50, 50}, {30, 30}, {70, 70}, {20, 20},
    {40, 40}, {60, 60}, {80, 80}
};

for (auto [key, pr] : seq) {
    tr.addWithPriority(key, pr);

    std::cout << "insert key=" << key
              << " priority=" << pr << '\n';
    std::cout << "inorden=" << tr.inorderValues() << '\n';
    std::cout << "niveles=" << tr.levelOrderValues() << '\n';
    std::cout << "raiz=" << tr.rootValue() << '\n';
    std::cout << "isBST=" << tr.isBST()
              << " isHeapByPriority=" << tr.isHeapByPriority()
              << " isTreap=" << tr.isTreap() << "\n\n";
}
```

## Salida esperada de al menos cinco inserciones

| Inserción | Inorden | Recorrido por niveles | Raíz | BST | Heap prioridad | Treap |
|---|---|---|---:|---|---|---|
| `(50,50)` | `[50]` | `[50]` | 50 | sí | sí | sí |
| `(30,30)` | `[30,50]` | `[30,50]` | 30 | sí | sí | sí |
| `(70,70)` | `[30,50,70]` | `[30,50,70]` | 30 | sí | sí | sí |
| `(20,20)` | `[20,30,50,70]` | `[20,30,50,70]` | 20 | sí | sí | sí |
| `(40,40)` | `[20,30,40,50,70]` | `[20,30,40,50,70]` | 20 | sí | sí | sí |
| `(60,60)` | `[20,30,40,50,60,70]` | `[20,30,40,50,60,70]` | 20 | sí | sí | sí |
| `(80,80)` | `[20,30,40,50,60,70,80]` | `[20,30,40,50,60,70,80]` | 20 | sí | sí | sí |

Con estas claves y prioridades iguales, el árbol final queda degenerado hacia la derecha:

```text
20
  \
   30
     \
      40
        \
         50
           \
            60
              \
               70
                 \
                  80
```

## Respuestas Parte A

**¿Por qué el recorrido inorden debe salir ordenado aunque las prioridades cambien la forma del árbol?**  
Porque las rotaciones preservan la propiedad BST sobre las claves. La prioridad solo decide la forma, no el orden inorden.

**¿Por qué la raíz no necesariamente es la primera clave insertada?**  
Porque una clave insertada después puede tener prioridad menor y rotar hacia arriba.

**¿Qué nodo debe subir cuando se inserta una clave con prioridad menor que la de sus ancestros?**  
Debe subir el nodo insertado, rotando contra sus padres hasta que su padre tenga prioridad menor o igual, o hasta llegar a la raíz.

**¿Qué propiedad conserva una rotación local sobre las claves?**  
Conserva la partición BST: todas las claves del subárbol izquierdo siguen siendo menores y las del derecho siguen siendo mayores.

**¿Qué propiedad intenta restaurar `bubbleUp` sobre las prioridades?**  
Restaura la propiedad heap de prioridad: el padre debe tener prioridad menor o igual que sus hijos.

---

## Parte B - Instrumentación de `bubbleUp`

## Código sugerido

```cpp
// MOD-A6-B10B: bubbleUp instrumentado.
std::size_t bubbleUpCount(Node* u) {
    std::size_t rotations = 0;

    while (u != nullptr && u->parent != nullptr &&
           u->priority < u->parent->priority) {
        if (u == u->parent->left) {
            rotateRight(u->parent);
        } else {
            rotateLeft(u->parent);
        }
        ++rotations;
    }

    return rotations;
}

// MOD-A6-B10B: inserción controlada sin romper add ni addWithPriority.
std::size_t addWithPriorityCount(const T& x, std::uint64_t priority) {
    Node* u = bstInsertNode(x, priority); // adaptar al nombre real
    if (u == nullptr) {
        return 0; // duplicado rechazado
    }
    ++size_;
    return bubbleUpCount(u);
}
```

## Tabla con secuencia que fuerza rotaciones

Secuencia:

```text
{ {100,100}, {90,90}, {80,80}, {70,70}, {60,60} }
```

| Clave | Prioridad | Rotaciones | Raíz después |
|---:|---:|---:|---:|
| 100 | 100 | 0 | 100 |
| 90 | 90 | 1 | 90 |
| 80 | 80 | 2 | 80 |
| 70 | 70 | 3 | 70 |
| 60 | 60 | 4 | 60 |

## Respuestas Parte B

**¿Por qué esta secuencia tiende a producir rotaciones repetidas?**  
Cada nueva clave es menor que las anteriores y también tiene prioridad menor. Se inserta profundo por la izquierda y luego debe subir hasta la raíz.

**¿Cuándo `bubbleUpCount` retorna cero?**  
Cuando el nodo queda como raíz inicial, cuando su prioridad no viola la propiedad heap con su padre, o cuando la inserción fue duplicada y no se agregó.

**¿Cuál es el peor caso de rotaciones durante una inserción?**  
`O(h)`, donde `h` es la altura del treap. En el peor caso degenerado, puede ser `O(n)`.

**¿Por qué una rotación no rompe la propiedad BST?**  
Porque solo cambia relaciones locales preservando los intervalos de claves de cada subárbol.

**¿Por qué el treap busca mantener altura esperada logarítmica, no garantizada logarítmica?**  
Porque depende de prioridades aleatorias. Con prioridades aleatorias independientes, la altura esperada es `O(log n)`, pero una mala secuencia de prioridades puede producir altura lineal.

---

## Parte C - Instrumentación de `trickleDown` y eliminación

## Código sugerido

```cpp
// MOD-A6-B10C: trickleDown instrumentado.
std::size_t trickleDownCount(Node* u) {
    std::size_t rotations = 0;

    while (u != nullptr && u->left != nullptr && u->right != nullptr) {
        if (u->left->priority < u->right->priority) {
            rotateRight(u);
        } else {
            rotateLeft(u);
        }
        ++rotations;
    }

    return rotations;
}

// MOD-A6-B10C: eliminación controlada.
std::size_t removeCount(const T& x) {
    Node* u = findNode(x);
    if (u == nullptr) {
        return 0;
    }

    std::size_t rotations = trickleDownCount(u);

    // Ahora u tiene a lo más un hijo.
    splice(u);       // adaptar al nombre real
    delete u;
    --size_;

    return rotations;
}
```

## Eliminaciones pedidas sobre el Treap de Parte A

| Clave eliminada | Rotaciones esperadas con el árbol final de Parte A | Inorden posterior | Invariantes |
|---:|---:|---|---|
| 50 | 0 | `[20,30,40,60,70,80]` | BST y heap por prioridad se conservan |
| 20 | 0 | `[30,40,60,70,80]` | BST y heap por prioridad se conservan |
| 70 | 0 | `[30,40,60,80]` | BST y heap por prioridad se conservan |

Observación importante: con la secuencia exacta de la Parte A, el árbol queda como cadena hacia la derecha. Por eso las eliminaciones solicitadas no fuerzan rotaciones. Para evidenciar rotación durante eliminación, conviene agregar un caso adicional con un nodo que tenga dos hijos.

## Trazado manual adicional con rotación

Árbol:

```text
      50(p10)
     /      \
 30(p20)   70(p15)
```

Eliminar `50`:

1. `50` tiene dos hijos.
2. Se elige el hijo de menor prioridad: `70(p15)` frente a `30(p20)`.
3. Se aplica `rotateLeft(50)`.
4. `70` sube y `50` baja a la izquierda de `70`.
5. Ahora se continúa bajando `50` hasta que tenga a lo más un hijo.
6. Se aplica `splice`.
7. El árbol resultante conserva BST y heap por prioridad.

## Respuestas Parte C

**¿Por qué eliminar en un treap no es simplemente borrar como en un BST común?**  
Porque además de conservar la propiedad BST hay que conservar la propiedad heap sobre prioridades. Borrar directamente un nodo con dos hijos podría romper esa propiedad.

**¿Por qué `trickleDown` elige rotar con el hijo de menor prioridad?**  
Porque en esta implementación menor prioridad significa mayor prioridad de heap. El hijo con menor prioridad debe quedar más cerca de la raíz.

**¿Qué ocurre si el nodo tiene solo hijo izquierdo?**  
Ya puede aplicarse `splice` reemplazándolo por ese hijo, actualizando enlaces parent.

**¿Qué ocurre si el nodo tiene solo hijo derecho?**  
También puede aplicarse `splice` reemplazándolo por el hijo derecho.

**¿Qué invariantes deben seguir siendo verdaderos después de `splice`?**  
Los enlaces `parent`, `left`, `right`, el tamaño, la propiedad BST y la propiedad heap por prioridad.

---

## Parte D - Búsqueda ordenada en Treap

## Consultas

Con claves `{20,30,40,50,60,70,80}`:

| Operación | Resultado esperado Treap | Resultado esperado BST | Propiedad usada |
|---|---|---|---|
| `findEQ(40)` | 40 | 40 | BST |
| `findEQ(35)` | no encontrado | no encontrado | BST |
| `lowerBound(35)` | 40 | 40 | BST |
| `lowerBound(40)` | 40 | 40 | BST |
| `upperBound(40)` | 50 | 50 | BST |
| `upperBound(75)` | 80 | 80 | BST |

## Respuestas Parte D

**¿Por qué `lowerBound` y `upperBound` dependen de la propiedad BST y no de la propiedad heap?**  
Porque buscan por orden de claves, no por prioridad.

**¿Qué parte del treap se comporta igual que un BST?**  
La ubicación de claves: menores a la izquierda, mayores a la derecha.

**¿Qué parte del treap se comporta como heap?**  
La relación de prioridades entre padre e hijos.

**¿Por qué el treap no reemplaza directamente a una cola de prioridad si solo quieres extraer máximos o mínimos repetidamente?**  
Porque el treap está organizado principalmente por claves y balanceado por prioridades. Una PQ pura ofrece operaciones de prioridad más directas y simples.

**¿En qué situación conviene usar un treap?**  
Cuando se necesita búsqueda ordenada (`find`, `lowerBound`, `upperBound`) con balanceo probabilístico y operaciones dinámicas.

---

## Parte E - Pruebas específicas para Treap

## Pruebas propuestas

```cpp
// MOD-A6-B10E: pruebas de Treap.

TEST(TreapExtra, EmptyTreapIsValid) {
    Treap<int> tr;
    EXPECT_TRUE(tr.empty());
    EXPECT_EQ(tr.size(), 0);
    EXPECT_TRUE(tr.isBST());
    EXPECT_TRUE(tr.isHeapByPriority());
    EXPECT_TRUE(tr.isTreap());
}

TEST(TreapExtra, FixedPrioritiesKeepInorderSorted) {
    Treap<int> tr;
    for (auto [x, p] : std::vector<std::pair<int, uint64_t>>{
        {50,50}, {30,30}, {70,70}, {20,20}, {40,40}
    }) {
        EXPECT_TRUE(tr.addWithPriority(x, p));
        EXPECT_TRUE(tr.isBST());
        EXPECT_TRUE(tr.isHeapByPriority());
        EXPECT_TRUE(tr.isTreap());
    }

    EXPECT_EQ(tr.inorderValues(), std::vector<int>({20,30,40,50,70}));
}

TEST(TreapExtra, RejectsDuplicates) {
    Treap<int> tr;
    EXPECT_TRUE(tr.addWithPriority(10, 5));
    EXPECT_FALSE(tr.addWithPriority(10, 1));
    EXPECT_EQ(tr.size(), 1);
}

TEST(TreapExtra, BoundsWorkLikeBST) {
    Treap<int> tr;
    for (auto [x, p] : std::vector<std::pair<int, uint64_t>>{
        {50,50}, {30,30}, {70,70}, {20,20}, {40,40}, {60,60}, {80,80}
    }) tr.addWithPriority(x, p);

    EXPECT_EQ(*tr.findEQ(40), 40);
    EXPECT_EQ(tr.findEQ(35), tr.end());
    EXPECT_EQ(*tr.lowerBound(35), 40);
    EXPECT_EQ(*tr.lowerBound(40), 40);
    EXPECT_EQ(*tr.upperBound(40), 50);
    EXPECT_EQ(*tr.upperBound(75), 80);
}

TEST(TreapExtra, RemoveKeepsInvariants) {
    Treap<int> tr;
    for (auto [x, p] : std::vector<std::pair<int, uint64_t>>{
        {50,50}, {30,30}, {70,70}, {20,20}, {40,40}, {60,60}, {80,80}
    }) tr.addWithPriority(x, p);

    for (int x : {50, 20, 70}) {
        tr.removeCount(x);
        EXPECT_TRUE(tr.isBST());
        EXPECT_TRUE(tr.isHeapByPriority());
        EXPECT_TRUE(tr.isTreap());
    }
}
```

## Respuestas Parte E

**¿Qué bug atraparía una prueba de enlaces `parent`?**  
Detectaría rotaciones o `splice` que actualizan hijos pero olvidan actualizar el padre del subárbol movido.

**¿Qué bug atraparía una prueba de `size()`?**  
Detectaría inserciones duplicadas contadas indebidamente o eliminaciones que no decrementan el tamaño.

**¿Qué bug atraparía una prueba de inorden ordenado?**  
Detectaría rotaciones mal implementadas que rompen la propiedad BST.

**¿Qué bug atraparía una prueba de prioridad padre-hijo?**  
Detectaría `bubbleUp` incompleto, `trickleDown` incorrecto o comparación de prioridades invertida.

**¿Por qué conviene usar prioridades fijas en pruebas unitarias?**  
Porque hacen el resultado determinístico. Así la prueba no depende de aleatoriedad y puede verificar forma, raíz, rotaciones e invariantes exactos.

**Resultado de `ctest`:**

```text
ctest --test-dir build-debug -R semana6 --output-on-failure
# Pendiente de reemplazar con salida real.
```

---

# Bloque 11 - Comparación con Semana 5

## Demo comparativa sugerida

```cpp
// MOD-A6-B11: comparación observable.
std::cout << "| estructura | operacion principal | propiedad | eficiente | no conviene | evidencia |\n";
std::cout << "|---|---|---|---|---|---|\n";
std::cout << "| BinaryHeap S5 | prioridad educativa | heap mínimo/máximo | top/remove | búsqueda ordenada | extracción ordenada |\n";
std::cout << "| PQ_ComplHeap S6 | cola de prioridad | max-heap completo | getMax/delMax | lowerBound | raíz máxima |\n";
std::cout << "| BinarySearchTree S5 | búsqueda por clave | BST | find/lowerBound/inorden | extraer prioridad | inorden ordenado |\n";
std::cout << "| Treap S6 | búsqueda + prioridad aleatoria | BST + heap prioridad | búsqueda balanceada esperada | PQ pura | inorden + prioridad |\n";
```

## Tabla de comparación

| Estructura | Operación principal | Propiedad mantenida | Operación eficiente | Operación que no conviene | Evidencia producida |
|---|---|---|---|---|---|
| `BinaryHeap` Semana 5 | Prioridad básica | Propiedad heap | Consultar y extraer raíz | Buscar clave arbitraria | Extracciones salen ordenadas por prioridad |
| `PQ_ComplHeap` Semana 6 | Interfaz PQ | Max-heap completo | `getMax`, `insert`, `delMax` | `lowerBound`, recorrido ordenado | Máximo en raíz y heap válido |
| `BinarySearchTree` Semana 5 | Búsqueda ordenada | Propiedad BST | `find`, `lowerBound`, `upperBound`, inorden | Extraer máximo repetidamente si no está balanceado | Inorden ordenado |
| `Treap` Semana 6 | Búsqueda ordenada balanceada esperada | BST + heap por prioridad | Búsqueda, inserción y eliminación esperadas `O(log n)` | Reemplazar una PQ pura | Inorden ordenado y prioridad padre-hijo |

## Respuestas

**¿Qué diferencia hay entre un heap de prioridad y un árbol de búsqueda?**  
El heap organiza por prioridad local padre-hijo. El BST organiza por orden global de claves: todo el subárbol izquierdo es menor y todo el derecho es mayor.

**¿Por qué un BST permite recorrido ordenado y un heap no?**  
Porque el inorden de un BST respeta la propiedad de claves. En un heap, los hijos no tienen relación ordenada entre sí ni con subárboles completos.

**¿Qué agrega `PQ_ComplHeap` frente a un `BinaryHeap` educativo?**  
Una interfaz abstracta de cola de prioridad y operaciones centradas en `getMax`, `insert`, `delMax`, además de separación modular de operaciones.

**¿Qué combina un Treap?**  
Combina propiedad BST sobre claves y propiedad heap sobre prioridades.

**¿Qué estructura usarías para extraer máximos repetidamente?**  
`PQ_ComplHeap`.

**¿Qué estructura usarías para responder `lowerBound` o `upperBound`?**  
`BinarySearchTree` o `Treap`.

**¿Qué estructura usarías si quieres búsqueda ordenada con balanceo probabilístico?**  
`Treap`.

---

# Bloque 12 - Pruebas obligatorias después de modificar código

## Lista de pruebas agregadas

| Prueba | Bug que atraparía |
|---|---|
| `PQ_ComplHeap` conserva heap después de cada inserción | Error en `percolateUp`. |
| `PQ_ComplHeap` conserva heap después de cada eliminación | Error en `percolateDown` o `delMax`. |
| `getMax` no cambia tamaño | Implementación que extrae accidentalmente. |
| `delMax` sí cambia tamaño | Eliminación incompleta. |
| `heapifyFloyd` produce heap válido | Recorrido incorrecto desde hojas o índices malos. |
| `heapSort` ordena con repetidos | Comparador incorrecto o pérdida de elementos iguales. |
| `PQ_LeftHeap` válido después de `merge` | Violación de heap, propiedad izquierdista o `npl`. |
| `PQ_LeftHeap` válido después de `insert` | `insert` no usa correctamente `merge`. |
| `PQ_LeftHeap` válido después de `delMax` | Fusión incorrecta de subárboles. |
| Huffman produce códigos para frecuencias positivas | Símbolos omitidos. |
| Huffman produce códigos libres de prefijos | Árbol o generación de códigos incorrecta. |
| Huffman maneja un símbolo | Código vacío no deseado. |
| Treap conserva BST después de insertar | Rotaciones mal implementadas. |
| Treap conserva heap por prioridad después de insertar | `bubbleUp` incorrecto. |
| Treap conserva ambas propiedades después de eliminar | `trickleDown` o `splice` incorrectos. |

## Fragmentos de pruebas

```cpp
// MOD-A6-B12: getMax no cambia tamaño.
TEST(PQComplHeapExtra, GetMaxDoesNotChangeSize) {
    PQ_ComplHeap<int> pq;
    for (int x : {4, 10, 7}) pq.insert(x);

    auto before = pq.size();
    EXPECT_EQ(pq.getMax(), 10);
    EXPECT_EQ(pq.size(), before);
}

// MOD-A6-B12: delMax sí cambia tamaño.
TEST(PQComplHeapExtra, DelMaxChangesSize) {
    PQ_ComplHeap<int> pq;
    for (int x : {4, 10, 7}) pq.insert(x);

    auto before = pq.size();
    pq.delMax();
    EXPECT_EQ(pq.size(), before - 1);
    EXPECT_TRUE(pq.isValidHeap());
}

// MOD-A6-B12: heapSort con repetidos.
TEST(HeapSortExtra, SortsRepeatedAscendingAndDescending) {
    std::vector<int> a = {5, 1, 5, 3, 8, 2, 8, 0};
    heapSort(a, std::less<int>{}, true);
    EXPECT_EQ(a, std::vector<int>({0, 1, 2, 3, 5, 5, 8, 8}));

    std::vector<int> b = {5, 1, 5, 3, 8, 2, 8, 0};
    heapSort(b, std::less<int>{}, false);
    EXPECT_EQ(b, std::vector<int>({8, 8, 5, 5, 3, 2, 1, 0}));
}

// MOD-A6-B12: Huffman caso de un símbolo.
TEST(HuffmanExtra, SingleSymbolGetsNonEmptyCode) {
    auto codes = huffmanCodes({{'X', 100}});
    ASSERT_EQ(codes.size(), 1);
    EXPECT_EQ(codes['X'], "0");
}
```

## Resultado completo de `ctest`

```text
ctest --test-dir build --output-on-failure
# Pendiente de reemplazar con la salida real después de compilar.
```

---

# Bloque 13 - Defensa escrita de modificaciones

Modificar código de prioridad, heaps, Huffman y Treap enseña algo que no aparece con la misma fuerza al solo leer o ejecutar demos: obliga a defender invariantes en cada línea que cambia. La interfaz `PQ` deja claro que una cola de prioridad no es una lista ordenada completa, sino un ADT donde importan operaciones como `getMax`, `insert` y `delMax`. La representación implícita del heap binario completo muestra que no siempre se necesitan punteros: con un vector y las fórmulas de padre e hijos se representa la forma completa del árbol.

Al instrumentar `percolateUp`, se observa que insertar no significa ordenar todo el arreglo. Solo se repara el camino entre el nuevo nodo y la raíz. Al instrumentar `percolateDown`, se entiende que después de eliminar el máximo el daño queda en la raíz y se corrige eligiendo siempre el hijo dominante. Floyd refuerza una idea importante: construir un heap desde abajo puede ser lineal porque casi todos los nodos están cerca de las hojas. `heapSort` conecta esa estructura con ordenamiento in situ: el heap se destruye gradualmente para formar un sufijo ordenado, aunque el algoritmo no sea estable.

El heap izquierdista enseña que la operación central puede cambiar. En un heap completo la operación natural es subir o bajar en un arreglo; en un heap izquierdista, la operación fundamental es `merge`. Por eso `insert` y `delMax` se reducen a fusiones. Huffman muestra una aplicación real de colas de prioridad: extraer dos frecuencias mínimas, combinarlas y reinsertar el nodo resultante. El caso de un solo símbolo y los empates demuestran que los casos borde también forman parte de la correctitud.

Treap fue la modificación más importante porque combina dos invariantes simultáneos: propiedad BST sobre claves y propiedad heap sobre prioridades. Las rotaciones no son decorativas; son el mecanismo que permite restaurar prioridad sin destruir el orden de búsqueda. `bubbleUp` repara inserciones, `trickleDown` ayuda en eliminaciones, y las búsquedas `lowerBound` y `upperBound` siguen dependiendo del orden BST, no de la prioridad.

Comparar con `BinaryHeap` y `BinarySearchTree` aclara que no hay una estructura universal. Para prioridad pura conviene heap; para búsqueda ordenada conviene BST o Treap; para balanceo esperado con búsqueda dinámica, Treap es razonable. Finalmente, las pruebas no sustituyen la explicación, pero la fortalecen: validar heap, propiedad izquierdista, códigos libres de prefijo, enlaces `parent`, tamaños e invariantes después de operaciones mixtas permite encontrar errores que una demo simple no mostraría. La evidencia completa combina pruebas, trazados, invariantes, casos borde y complejidad.

---

# Autoevaluación breve

- Qué puedo defender con seguridad: la diferencia entre heap completo, heap izquierdista, Huffman, BST y Treap; además de los invariantes de prioridad y búsqueda.
- Qué todavía confundo: los nombres exactos de campos internos del repositorio si difieren de los usados en los fragmentos (`_elem`, `_root`, `_size`, `_comp`, `npl`).
- Qué evidencia usaría en una sustentación: salidas de demos instrumentadas, `ctest`, trazados de rotaciones y validadores `isValidHeap`, `isValidLeftHeap`, `isTreap`.
- Qué parte del código me parece más importante para revisar otra vez: `Treap.h`, especialmente rotaciones, `bubbleUp`, `trickleDown`, `splice` y actualización de enlaces `parent`.
