## Actividad 5 - CC232

### Estudiante

- Nombre: **Alvaro Raul Montoya Dulanto**

---

### Bloque 1 - Núcleo conceptual

**1. Diferencia entre árbol binario enlazado y árbol binario implícito en arreglo.**  
Un árbol binario enlazado representa cada nodo como un objeto con punteros hacia su padre, hijo izquierdo e hijo derecho. La forma del árbol está dada por enlaces explícitos. En cambio, un árbol binario implícito en arreglo no guarda punteros: la posición `i` del arreglo determina las posiciones de sus hijos y de su padre mediante fórmulas. Esta representación es natural para heaps completos o casi completos, pero no para árboles con forma arbitraria.

**2. Información que guarda un `BinNode`.**  
Un `BinNode` normalmente guarda:
- `data`: el valor almacenado.
- `parent`: puntero al nodo padre.
- `left`: puntero al hijo izquierdo.
- `right`: puntero al hijo derecho.
- `height`: altura del subárbol con raíz en ese nodo.

Estos campos permiten navegar, modificar, recorrer y mantener información estructural del árbol.

**3. Utilidad de `parent` para `succ()`, `pred()` y alturas.**  
El puntero `parent` permite subir desde un nodo hacia sus ancestros. Esto es clave para encontrar el sucesor o predecesor inorden cuando no basta con bajar a un subárbol. También permite actualizar alturas desde un nodo modificado hasta la raíz, sin recorrer todo el árbol.

**4. Responsabilidad de `BinTree` frente a `BinNode`.**  
`BinNode` representa un nodo individual y sus relaciones locales. `BinTree` administra el árbol completo: raíz, tamaño, inserciones, adjuntar subárboles, separar subárboles, eliminar subárboles, actualizar alturas y verificar enlaces.

**5. Qué agrega `BinaryTree` sobre `BinTree`.**  
`BinaryTree` agrega una interfaz de navegación y recorrido más cómoda: iteradores inorden, acceso al primer y último nodo, avance al siguiente y anterior nodo, recorridos, impresión ASCII y operaciones orientadas al uso del árbol como colección navegable.

**6. Propiedad adicional de un `BinarySearchTree`.**  
Un árbol binario se convierte en BST si para cada nodo `u`, todos los valores del subárbol izquierdo son menores que `u->data` y todos los valores del subárbol derecho son mayores que `u->data`. Si se permitieran duplicados, habría que definir una política; en esta semana se asume que no se aceptan duplicados.

**7. Propiedad adicional de un `BinaryHeap` mínimo.**  
Un arreglo representa un min-heap si cumple dos condiciones: estructura completa por niveles y prioridad mínima local. Para todo índice `i`, el valor en `i` debe ser menor o igual que los valores de sus hijos, si existen.

**8. BST vs heap.**  
El BST mantiene una propiedad de orden global relativa: izquierda < nodo < derecha. Esto permite búsquedas ordenadas, `lowerBound`, `upperBound` e inorden ordenado. El heap mantiene solo una propiedad de prioridad local: cada padre tiene prioridad mayor que sus hijos en un min-heap, es decir, valor menor o igual. Esto permite consultar y extraer rápido el mínimo, pero no buscar cualquier clave eficientemente.

**9. Por qué el inorden de un BST sale ordenado.**  
El recorrido inorden visita primero el subárbol izquierdo, luego el nodo y luego el subárbol derecho. Por la propiedad BST, todo lo de la izquierda es menor, luego viene el nodo, y todo lo de la derecha es mayor. Aplicando el mismo argumento recursivamente, la secuencia queda ordenada.

**10. Por qué un heap no permite recorrer ordenadamente sin destruir o copiar.**  
En un heap solo se garantiza que la raíz sea el mínimo y que cada padre sea menor o igual que sus hijos. No hay orden total entre hermanos ni entre ramas. Para obtener todos los elementos ordenados, normalmente se extrae repetidamente el mínimo, lo que modifica la estructura, o se copia el heap y se extrae desde la copia.

---

### Bloque 2 - Navegación, altura, profundidad y tamaño

**1. Significado de métodos básicos en `BinNode`.**

| Método | Significado |
|---|---|
| `hasLeft()` | El nodo tiene hijo izquierdo. |
| `hasRight()` | El nodo tiene hijo derecho. |
| `isRoot()` | El nodo no tiene padre. |
| `isLeaf()` | El nodo no tiene hijos. |
| `isLeftChild()` | El nodo es el hijo izquierdo de su padre. |
| `isRightChild()` | El nodo es el hijo derecho de su padre. |

**2. Caso de `succ()` bajando al subárbol derecho.**  
Si un nodo tiene hijo derecho, su sucesor inorden es el nodo más a la izquierda dentro de ese subárbol derecho. Esto ocurre porque el sucesor debe ser el menor elemento mayor que el nodo actual.

**3. Caso de `succ()` subiendo por ancestros.**  
Si el nodo no tiene hijo derecho, se sube por `parent` hasta encontrar el primer ancestro para el cual el nodo actual pertenece al lado izquierdo. Ese ancestro es el sucesor, porque es el primer nodo mayor que todavía no ha sido visitado en inorden.

**4. Funcionamiento simétrico de `pred()`.**  
Si el nodo tiene hijo izquierdo, su predecesor es el nodo más a la derecha del subárbol izquierdo. Si no tiene hijo izquierdo, se sube por ancestros hasta encontrar el primer ancestro para el cual se viene desde el lado derecho.

**5. Árbol de ejemplo con sucesores y predecesores.**

Árbol usado:

```text
        7
      /   \
     3     10
    / \    / \
   1   5  8  12
      / \
     4   6
```

Secuencia inorden:

```text
1, 3, 4, 5, 6, 7, 8, 10, 12
```

| Nodo | Predecesor inorden | Sucesor inorden |
|---:|---:|---:|
| 3 | 1 | 4 |
| 5 | 4 | 6 |
| 10 | 8 | 12 |

**6. Qué calcula `depth(u)`.**  
`depth(u)` calcula la cantidad de aristas desde la raíz hasta `u`. Puede implementarse subiendo por `parent` y contando pasos hasta llegar a la raíz.

**7. Qué calcula `height(u)`.**  
`height(u)` calcula la longitud del camino más largo desde `u` hasta una hoja de su subárbol. Suele implementarse bajando recursivamente por los hijos, porque depende de la altura de los subárboles izquierdo y derecho.

**8. Qué calcula `subtreeSize(u)`.**  
Calcula cuántos nodos hay en el subárbol cuya raíz es `u`. Se obtiene como:

```text
1 + size(left) + size(right)
```

**9. Demostración de `depth(u) + height(u) <= height(T)`.**  
`depth(u)` mide el camino de la raíz hasta `u`. `height(u)` mide el camino más largo desde `u` hasta alguna hoja descendiente. Al unir ambos caminos se obtiene un camino desde la raíz hasta una hoja que pasa por `u`. Como `height(T)` es la longitud máxima entre todos los caminos raíz-hoja, entonces ese camino no puede ser mayor que `height(T)`.

**10. Condición para que haya igualdad.**  
La igualdad se alcanza si `u` pertenece a algún camino máximo desde la raíz hasta una hoja más profunda del árbol. En otras palabras, `u` debe estar sobre una rama que realiza la altura total del árbol.

---

### Bloque 3 - Recorridos y trazado guiado

Árbol de prueba usado para la tabla:

```text
        7
      /   \
     3     10
    / \    / \
   1   5  8  12
      / \
     4   6
```

| Recorrido | Versión revisada | Estructura auxiliar usada | Secuencia producida en el árbol de prueba | Argumento de correctitud y costo |
|---|---|---|---|---|
| Preorden | Recursivo | Pila de llamadas | `7, 3, 1, 5, 4, 6, 10, 8, 12` | Visita nodo antes que hijos. Cada nodo se visita una vez: O(n). |
| Preorden | Iterativo | Pila explícita | `7, 3, 1, 5, 4, 6, 10, 8, 12` | Se apila primero derecho y luego izquierdo para procesar izquierdo antes. O(n). |
| Inorden | Recursivo | Pila de llamadas | `1, 3, 4, 5, 6, 7, 8, 10, 12` | Visita izquierda, nodo, derecha. Cada arista se usa acotadamente: O(n). |
| Inorden | Iterativo #1 | Pila explícita | `1, 3, 4, 5, 6, 7, 8, 10, 12` | Baja a la izquierda apilando; al desapilar visita y pasa a derecha. O(n). |
| Inorden | Iterativo #2 | Puntero `succ()` | `1, 3, 4, 5, 6, 7, 8, 10, 12` | Empieza en `leftmost()` y avanza por sucesores. O(n) si cada avance es amortizado. |
| Inorden | Iterativo #3 | Iterador | `1, 3, 4, 5, 6, 7, 8, 10, 12` | Encapsula `firstNode()` y `nextNode()`. Produce inorden por definición de sucesor. O(n). |
| Postorden | Recursivo | Pila de llamadas | `1, 4, 6, 5, 3, 8, 12, 10, 7` | Visita hijos antes que nodo. O(n). |
| Postorden | Iterativo | Pila explícita y/o marca de visita | `1, 4, 6, 5, 3, 8, 12, 10, 7` | Asegura procesar un nodo después de sus hijos. O(n). |
| Por niveles | Iterativo | Cola | `7, 3, 10, 1, 5, 8, 12, 4, 6` | Procesa por distancia creciente desde la raíz usando FIFO. O(n). |

**1. Visitar en preorden.**  
Significa procesar el nodo antes de recorrer sus hijos.

**2. Visitar en inorden.**  
Significa procesar primero el subárbol izquierdo, luego el nodo y finalmente el subárbol derecho.

**3. Visitar en postorden.**  
Significa procesar primero los hijos y dejar el nodo para el final.

**4. Visitar por niveles.**  
Significa recorrer el árbol por profundidad: primero raíz, luego nodos de profundidad 1, luego profundidad 2, y así sucesivamente.

**5. Por qué los recorridos recursivos son O(n).**  
Cada nodo se visita una vez y cada llamada recursiva hace trabajo constante aparte de sus subllamadas. Por eso el costo total es lineal en el número de nodos.

**6. Por qué las versiones iterativas también son O(n).**  
Aunque cambian recursión por pila o cola explícita, cada nodo entra y sale de la estructura auxiliar una cantidad constante de veces.

**7. Memoria auxiliar recursiva en árbol balanceado.**  
En un árbol balanceado, la altura es O(log n), así que la pila de llamadas ocupa O(log n).

**8. Memoria auxiliar recursiva en árbol degenerado.**  
En un árbol degenerado, la altura puede ser O(n), así que la pila de llamadas puede crecer hasta O(n).

**9. Pila explícita vs pila de llamadas.**  
La pila de llamadas la administra automáticamente el lenguaje durante la recursión. La pila explícita la administra el programador y permite controlar exactamente qué estados se guardan y en qué orden se procesan.

**10. Por qué la cola por niveles puede crecer mucho en un árbol completo.**  
En un árbol completo, el último nivel puede contener cerca de la mitad de todos los nodos, por lo que la cola puede crecer hasta O(n). En un árbol degenerado, casi siempre hay pocos nodos pendientes por nivel, así que la cola suele ser O(1).

---

### Bloque 4 - Demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
|---|---|---|---|
| `demo_binary_tree.cpp` | Listas de recorridos, sucesor/predecesor, altura, profundidad y ASCII art. | Árbol enlazado con navegación por punteros. | Recorridos O(n), navegación local por `parent`, altura depende de forma del árbol. |
| `demo_bst.cpp` | Inserciones, búsquedas, inorden ordenado, eliminación y validación `isBST()`. | Propiedad BST y operaciones ordenadas. | Búsqueda O(h), O(log n) si balanceado, O(n) si degenerado. |
| `demo_heap.cpp` | `top()`, inserciones, heapify, extracciones ordenadas. | Heap mínimo implícito en arreglo. | `add` O(log n), `remove` O(log n), `heapify` O(n). |
| `demo_capitulo5_panorama.cpp` | Comparación de árbol binario, BST y heap. | Panorama de representaciones y aplicaciones. | Muestra que la forma y el invariante determinan costos y usos. |

**1. Salida que verifica recorridos en `demo_binary_tree.cpp`.**  
La evidencia principal son las secuencias impresas para preorden, inorden, postorden y niveles. Si coinciden con el árbol mostrado, se puede defender que cada recorrido visita los nodos en el orden esperado.

**2. Evidencia de `succ()` y `pred()`.**  
La demo debe mostrar pares nodo-sucesor y nodo-predecesor. Si esos pares coinciden con la secuencia inorden, entonces `succ()` y `pred()` respetan la navegación inorden.

**3. Evidencia del ASCII art.**  
La representación ASCII permite ver la forma del árbol: qué nodo es raíz, qué nodos son hijos izquierdos/derechos y qué ramas tienen mayor profundidad. Es útil para comparar estructura visual con recorridos.

**4. Observable del BST que defiende inorden ordenado.**  
La lista inorden del BST debe salir en orden ascendente. Esa salida conecta directamente el recorrido con la propiedad BST.

**5. Operaciones de búsqueda mejor distinguibles.**  
`findEQ`, `lowerBound` y `upperBound` se distinguen claramente porque no significan lo mismo:
- `findEQ(x)` busca exactamente `x`.
- `lowerBound(x)` busca el menor valor `>= x`.
- `upperBound(x)` busca el menor valor `> x`.
`find` puede depender de cómo se implemente: puede devolver nodo encontrado o último nodo visitado/candidato.

**6. Salida que defiende que el mínimo queda en la raíz.**  
En `demo_heap.cpp`, la evidencia es que `top()` muestra el menor elemento actual y que, tras cada `remove()`, el siguiente `top()` vuelve a ser el mínimo de los restantes.

**7. Evidencia para distinguir `add()` y `heapify()`.**  
`add()` mantiene el heap después de cada inserción usando `bubbleUp`. `heapify()` recibe varios elementos y reorganiza el arreglo completo desde los últimos padres hacia la raíz. La demo puede mostrar arreglos intermedios o comparar que ambos terminan en heaps válidos, aunque no necesariamente con la misma disposición interna.

**8. Comparación que resume la semana.**  
La mejor comparación es: árbol enlazado para estructura general y recorridos, BST para búsqueda ordenada, heap para prioridad mínima. Son árboles o formas arborescentes, pero con invariantes y objetivos distintos.

---

### Bloque 5 - Pruebas públicas, pruebas internas e invariantes

**1. Operaciones del BST validadas por prueba pública.**  
Usualmente se validan inserción, rechazo de duplicados, recorridos, búsqueda exacta, `lowerBound`, `upperBound`, eliminación e invariantes mediante `isBST()`.

**2. Casos que validan rechazo de duplicados.**  
Se intenta insertar una clave que ya existe y se espera que la estructura no cambie de tamaño o que la inserción retorne falso. También se puede verificar que el inorden no contenga repetidos.

**3. Comparación entre inorden recursivo e iterativos.**  
Valida que distintas implementaciones del mismo recorrido produzcan la misma secuencia. Esto no solo prueba la salida, también refuerza que la pila explícita, el iterador y la recursión codifican el mismo orden.

**4. Qué se espera de `findEQ(8)`.**  
Se espera que encuentre el nodo con clave `8`, si esa clave fue insertada en el árbol de prueba.

**5. Qué se espera de `lowerBound(9)` y `upperBound(8)`.**  
En el árbol con claves `1, 3, 4, 5, 6, 7, 8, 10, 12`, ambos deben devolver `10`:
- `lowerBound(9)` = menor clave `>= 9` = `10`.
- `upperBound(8)` = menor clave `> 8` = `10`.

**6. Propiedad validada con `isBST()`.**  
Verifica que para cada nodo se respete el orden BST: subárbol izquierdo menor, nodo en medio y subárbol derecho mayor. Idealmente valida la propiedad con rangos válidos, no solo comparando padre-hijo.

**7. Validación después de `remove()`.**  
Después de eliminar, se debe verificar que el elemento ya no esté, que el tamaño haya disminuido, que el inorden siga ordenado y que `isBST()` siga siendo verdadero.

**8. Qué valida `checkParentLinks()`.**  
Valida que si un nodo apunta a un hijo, ese hijo apunte de vuelta al mismo padre. También verifica que la raíz no tenga padre. Esto es crítico después de borrar, separar o adjuntar subárboles.

**9. Operaciones del heap validadas por prueba pública.**  
Se validan `add`, `top`, `remove`, construcción con `heapify`, tamaño, vacío/no vacío e `isHeap()`.

**10. Qué demuestra extraer repetidamente de un min-heap.**  
Demuestra que cada extracción devuelve el mínimo restante. Por eso la secuencia extraída debe estar en orden no decreciente.

**11. Operaciones de `BinTree` validadas con `attachAsRC`, `secede` y `removeSubtree`.**  
Se valida adjuntar un subárbol como hijo derecho, separar un subárbol sin destruirlo y eliminar un subárbol liberando nodos. También se revisan tamaño, raíz, alturas y enlaces `parent`.

**12. Qué agregan las pruebas internas.**  
Las pruebas internas suelen cubrir casos más finos: rotaciones izquierda/derecha, `bubbleUp`, `trickleDown`, cálculo de profundidad y altura, sucesor/predecesor en casos borde, eliminación con dos hijos y consistencia de enlaces después de operaciones complejas.

**13. Qué sí demuestra pasar las pruebas públicas.**  
Demuestra que el código funciona para los escenarios básicos previstos por el curso y que las operaciones principales producen las salidas esperadas.

**14. Qué no demuestra pasar las pruebas públicas.**  
No demuestra ausencia total de errores. Pueden faltar casos borde: árbol vacío, nodo raíz, eliminación compleja, duplicados, altura luego de múltiples cambios o heaps con muchos valores repetidos.

**15. Por qué mencionar invariantes y complejidad.**  
Las pruebas muestran ejemplos; los invariantes explican por qué el algoritmo es correcto en general. La complejidad permite defender eficiencia y comparar estructuras. Una sustentación sólida necesita resultados observables, invariantes mantenidos y costos.

---

### Bloque 6 - Lectura cercana de código

**1. Invariantes entre `parent`, `left` y `right`.**  
Si `u->left = v`, entonces `v->parent = u`. Si `u->right = w`, entonces `w->parent = u`. La raíz debe tener `parent = nullptr`. Un nodo no debe aparecer como hijo de dos padres distintos.

**2. Por qué `insertAsLC` e `insertAsRC` rechazan si ya existe hijo.**  
Si se sobrescribiera un hijo existente, se perdería todo el subárbol anterior o quedarían nodos desconectados. Rechazar la inserción protege la estructura y evita fugas o inconsistencias.

**3. Cómo `size()` de `BinNode` recorre el subárbol.**  
Calcula recursivamente el tamaño del subárbol:

```text
size(u) = 1 + size(u->left) + size(u->right)
```

Si un hijo es nulo, aporta 0.

**4. Cómo funcionan `leftmost()` y `rightmost()`.**  
`leftmost()` baja repetidamente por `left` hasta que no haya hijo izquierdo. `rightmost()` baja repetidamente por `right` hasta que no haya hijo derecho.

**5. Paso a paso de `succ()`.**
1. Si el nodo tiene hijo derecho, ir al hijo derecho.
2. Desde ahí, bajar al nodo más a la izquierda.
3. Si no tiene hijo derecho, subir mientras el nodo actual sea hijo derecho.
4. El primer ancestro para el que se viene desde la izquierda es el sucesor.
5. Si no existe ese ancestro, el nodo no tiene sucesor.

**6. Paso a paso de `pred()`.**
1. Si el nodo tiene hijo izquierdo, ir al hijo izquierdo.
2. Desde ahí, bajar al nodo más a la derecha.
3. Si no tiene hijo izquierdo, subir mientras el nodo actual sea hijo izquierdo.
4. El primer ancestro para el que se viene desde la derecha es el predecesor.
5. Si no existe ese ancestro, el nodo no tiene predecesor.

**7. Papel de `root_` y `size_` en `BinTree`.**  
`root_` apunta a la raíz del árbol. `size_` almacena la cantidad de nodos del árbol para no recalcularla recorriendo todo cada vez.

**8. Qué hace `updateHeight(Node*)`.**  
Recalcula la altura de un nodo usando las alturas de sus hijos:

```text
height(u) = 1 + max(height(left), height(right))
```

Para una hoja, la altura suele ser 0.

**9. Qué hace `updateHeightAbove(Node*)`.**  
Actualiza la altura del nodo recibido y luego sube por sus padres hasta la raíz. Es necesario porque insertar, borrar o adjuntar un subárbol puede cambiar la altura de todos sus ancestros.

**10. Cómo `attachAsLC` o `attachAsRC` transfieren un subárbol.**  
Toman la raíz de otro árbol y la conectan como hijo izquierdo o derecho de un nodo del árbol actual. Luego actualizan el `parent` de esa raíz, aumentan `size_` del árbol receptor, vacían el árbol donante y actualizan alturas.

**11. Diferencia entre `removeSubtree` y `secede`.**  
`removeSubtree` elimina físicamente los nodos del subárbol y libera memoria. `secede` separa el subárbol y lo devuelve como un nuevo árbol independiente.

**12. Por qué `secede` no destruye nodos.**  
Porque su objetivo es desprender y conservar el subárbol. Los nodos siguen existiendo, solo cambian de árbol propietario.

**13. Por qué `removeSubtree` sí libera nodos.**  
Porque su objetivo es borrar el subárbol. Si no libera memoria, los nodos quedarían inaccesibles y habría fuga de memoria.

**14. Qué verifica `checkParentLinks()`.**  
Verifica consistencia bidireccional entre padre e hijos: cada hijo debe apuntar a su padre real y la raíz debe tener padre nulo.

**15. `firstNode`, `lastNode`, `nextNode` y `prevNode` en `BinaryTree`.**  
`firstNode()` suele devolver el nodo más a la izquierda. `lastNode()` devuelve el más a la derecha. `nextNode()` aplica `succ()`. `prevNode()` aplica `pred()`.

**16. Por qué un iterador basado en `succ()` produce inorden.**  
Porque empieza en el menor nodo inorden (`leftmost`) y cada llamada a `succ()` avanza al siguiente nodo de la secuencia inorden.

**17. Aporte de `asciiArt()`.**  
Permite depurar y sustentar visualmente la forma del árbol. Es especialmente útil para verificar rotaciones, adjuntos, borrados, alturas y recorridos.

---

### Bloque 7 - BST

**1. Definición formal de propiedad BST.**  
Para todo nodo `u` con clave `k`, todas las claves del subárbol izquierdo de `u` son menores que `k`, y todas las claves del subárbol derecho son mayores que `k`. Además, ambos subárboles también deben cumplir la propiedad BST.

**2. Por qué el inorden de un BST es no decreciente.**  
El inorden visita primero claves menores, luego la clave del nodo y después claves mayores. Al aplicar esto recursivamente, la secuencia total queda en orden ascendente. Si hubiera duplicados permitidos, sería no decreciente; si no se permiten duplicados, estrictamente creciente.

**3. Diferencia entre `find`, `findEQ`, `lowerBound` y `upperBound`.**

| Operación | Significado |
|---|---|
| `find(x)` | Busca siguiendo la ruta BST; según implementación puede devolver coincidencia o último nodo visitado. |
| `findEQ(x)` | Devuelve el nodo cuya clave es exactamente `x`; si no existe, falla o devuelve nulo. |
| `lowerBound(x)` | Devuelve el menor nodo con clave `>= x`. |
| `upperBound(x)` | Devuelve el menor nodo con clave `> x`. |

**4. Por qué `findEQ(x)` puede fallar aunque `lowerBound(x)` no falle.**  
Porque `findEQ(x)` exige igualdad exacta. `lowerBound(x)` puede devolver una clave mayor si `x` no existe. Por ejemplo, con claves `1, 3, 5`, `findEQ(4)` falla, pero `lowerBound(4)` devuelve `5`.

**5. BST al insertar `7, 3, 10, 1, 5, 8, 12, 4, 6`.**

```text
        7
      /   \
     3     10
    / \    / \
   1   5  8  12
      / \
     4   6
```

**6. Recorridos del árbol.**

| Recorrido | Secuencia |
|---|---|
| Inorden | `1, 3, 4, 5, 6, 7, 8, 10, 12` |
| Preorden | `7, 3, 1, 5, 4, 6, 10, 8, 12` |
| Postorden | `1, 4, 6, 5, 3, 8, 12, 10, 7` |
| Por niveles | `7, 3, 10, 1, 5, 8, 12, 4, 6` |

**7. Simulación de `lowerBound(9)`.**

```text
Nodo 7: 7 < 9, ir a la derecha.
Nodo 10: 10 >= 9, guardar 10 como candidato e ir a la izquierda.
Nodo 8: 8 < 9, ir a la derecha.
Nulo: termina. Respuesta = 10.
```

**8. Simulación de `upperBound(8)`.**

```text
Nodo 7: 7 <= 8, ir a la derecha.
Nodo 10: 10 > 8, guardar 10 como candidato e ir a la izquierda.
Nodo 8: 8 <= 8, ir a la derecha.
Nulo: termina. Respuesta = 10.
```

**9. Casos de eliminación en BST.**
- **Hoja:** se desconecta directamente.
- **Un hijo:** el hijo reemplaza al nodo eliminado.
- **Dos hijos:** se reemplaza el nodo por su sucesor o predecesor inorden y luego se elimina ese nodo auxiliar, que tendrá a lo sumo un hijo.

**10. Papel de `splice`.**  
`splice` elimina físicamente un nodo que tiene a lo sumo un hijo, reconectando su padre con ese hijo. Es una operación local usada por `remove`.

**11. Invariantes después de eliminar.**  
Deben mantenerse:
- propiedad BST,
- enlaces `parent` correctos,
- tamaño actualizado,
- alturas actualizadas,
- raíz correcta si se eliminó la raíz,
- ausencia de nodos duplicados o desconectados.

**12. Por qué `remove(3)` debe conservar el inorden ordenado.**  
En el árbol de ejemplo, `3` tiene dos hijos. Al eliminarlo, se puede usar su sucesor `4` o su predecesor `1`. En ambos casos la reestructuración debe mantener que el subárbol izquierdo tenga claves menores y el derecho claves mayores. Por eso el inorden posterior debe seguir ordenado.

**13. Qué hace `rotateLeft`.**  
Una rotación izquierda sobre un nodo `x` sube a su hijo derecho `y`, mueve el subárbol izquierdo de `y` como hijo derecho de `x`, y deja a `x` como hijo izquierdo de `y`.

```text
    x                 y
     \               /
      y     ->      x
     /               \
    B                 B
```

**14. Qué hace `rotateRight`.**  
Una rotación derecha sobre un nodo `y` sube a su hijo izquierdo `x`, mueve el subárbol derecho de `x` como hijo izquierdo de `y`, y deja a `y` como hijo derecho de `x`.

```text
      y             x
     /               \
    x       ->        y
     \               /
      B             B
```

**15. Demostración de que una rotación preserva BST.**  
En una rotación izquierda, antes se tiene:

```text
A < x < B < y < C
```

Después de rotar, `x` conserva `A` a la izquierda y `B` a la derecha; `y` conserva `C` a la derecha y ahora tiene a `x` a la izquierda. El orden relativo de todas las claves no cambia, por lo que el inorden permanece igual. Lo mismo aplica simétricamente para rotación derecha.

**16. Para qué construir un BST balanceado desde arreglo ordenado.**  
Sirve para obtener altura O(log n) eligiendo la mediana como raíz, luego las medianas de cada mitad como subraíces. Así se evitan árboles degenerados y se mejora el costo de búsqueda.

**17. Costo de búsqueda balanceado vs degenerado.**  
En un BST balanceado, la altura es O(log n), por lo que buscar cuesta O(log n). En un BST degenerado, la altura es O(n), y buscar puede costar O(n), como en una lista.

---

### Bloque 8 - Heap

**1. Por qué un heap binario puede almacenarse en `std::vector` sin punteros.**  
Un heap binario mantiene forma completa por niveles. Eso permite guardar los nodos en orden de niveles dentro de un arreglo, sin huecos intermedios. Las relaciones padre-hijo se calculan con índices.

**2. Fórmulas de índices.**

Si los índices empiezan en 0, para un nodo en posición `i`:

```text
left(i)  = 2*i + 1
right(i) = 2*i + 2
parent(i) = (i - 1) / 2
```

Demostración breve: en un árbol completo almacenado por niveles, antes del nivel de los hijos de `i` ya están todos los nodos anteriores. Cada nodo antes de `i` aporta dos posiciones de hijo. Por eso los hijos de `i` quedan en las posiciones `2*i+1` y `2*i+2`. Invirtiendo la relación, el padre de un índice `j > 0` es `(j-1)/2` con división entera.

**3. Propiedad de min-heap.**  
Para todo índice `i`, si existen sus hijos, entonces:

```text
heap[i] <= heap[left(i)]
heap[i] <= heap[right(i)]
```

**4. Por qué `top()` devuelve el mínimo.**  
Si cada padre es menor o igual que sus hijos, ningún descendiente puede ser menor que la raíz. Por transitividad a lo largo de cualquier camino, la raíz contiene el menor elemento del heap.

**5. `bubbleUp(i)` paso a paso.**
1. Se inserta el nuevo elemento al final para conservar la forma completa.
2. Se compara con su padre.
3. Si el elemento es menor que el padre, se intercambian.
4. Se repite hasta llegar a la raíz o hasta que el padre sea menor o igual.
5. Así se restaura la propiedad de heap en la ruta hacia arriba.

**6. `trickleDown(i)` paso a paso.**
1. Se parte de un índice, normalmente la raíz.
2. Se compara el elemento con sus hijos.
3. Si alguno de los hijos es menor, se intercambia con el hijo menor.
4. Se continúa bajando por esa rama.
5. Se detiene cuando el elemento es menor o igual que sus hijos o llega a una hoja.

**7. Por qué `remove()` mueve el último elemento a la raíz.**  
Al quitar la raíz queda un hueco. Si se moviera cualquier elemento se podría romper la forma completa. Al mover el último elemento a la raíz y borrar la última posición, se conserva la forma completa y luego `trickleDown(0)` restaura la prioridad.

**8. Qué verifica `isHeap()`.**  
Verifica que para cada índice válido se cumpla que el padre sea menor o igual que sus hijos. También puede verificar que el arreglo representa una estructura completa, aunque eso ya lo garantiza el vector sin huecos.

**9. Insertar n elementos vs `heapify()`.**  
Insertar uno por uno usa `bubbleUp` en cada inserción y puede costar O(log n) por elemento. `heapify()` reorganiza un arreglo completo aplicando `trickleDown` desde los últimos nodos internos hacia la raíz, logrando O(n).

**10. Por qué insertar n elementos cuesta O(n log n).**  
Cada inserción puede subir desde una hoja hasta la raíz, lo que cuesta O(log n) en el peor caso. Para n inserciones, el peor caso total es O(n log n).

**11. Por qué `heapify()` es O(n).**  
Aunque `trickleDown` puede costar O(log n) en la raíz, la mayoría de nodos están cerca de las hojas y bajan muy poco. La suma de costos por niveles se acota por una serie lineal, por eso el costo total es O(n).

**12. Extracción completa para `{7, 3, 10, 1, 5, 8, 2}`.**

El conjunto ordenado esperado es:

```text
1, 2, 3, 5, 7, 8, 10
```

Una posible construcción por heapify produce un arreglo interno como:

```text
[1, 3, 2, 7, 5, 8, 10]
```

La extracción completa devuelve:

| Paso | Mínimo extraído | Restantes conceptuales |
|---:|---:|---|
| 1 | 1 | `2, 3, 5, 7, 8, 10` |
| 2 | 2 | `3, 5, 7, 8, 10` |
| 3 | 3 | `5, 7, 8, 10` |
| 4 | 5 | `7, 8, 10` |
| 5 | 7 | `8, 10` |
| 6 | 8 | `10` |
| 7 | 10 | vacío |

Sale ordenada porque cada `remove()` extrae el mínimo restante y luego restaura la propiedad de min-heap.

**13. Heap vs BST.**  
Para consultar y extraer repetidamente el mínimo conviene un min-heap: `top()` es O(1) y `remove()` O(log n). Para búsquedas ordenadas, rangos, sucesor, predecesor, `lowerBound` y recorrido inorden, conviene un BST balanceado.

---

### Bloque 9 - Cierre comparativo

Pasar de listas, pilas y colas a árboles binarios, heaps y BST cambia el tipo de razonamiento. En listas, pilas y colas domina una idea lineal: avanzar, apilar o encolar elementos en una secuencia. En árboles aparece una estructura jerárquica donde cada nodo puede abrir varias rutas y donde la forma influye directamente en el costo.

En un árbol enlazado, la representación depende de nodos y punteros: cada `BinNode` guarda su dato, su padre, sus hijos y su altura. Por eso la correctitud no depende solo de los valores, sino también de mantener consistentes los enlaces `parent`, `left` y `right`. En cambio, un heap usa representación implícita en arreglo: no necesita punteros porque la forma completa permite calcular hijos y padre con fórmulas de índices.

También cambia la distinción entre propiedad estructural y propiedad de orden. Un árbol binario puede tener cualquier forma; un BST agrega una propiedad de orden izquierda-nodo-derecha; un heap agrega una propiedad de prioridad padre-hijo. Los recorridos son la forma de convertir una estructura jerárquica en una secuencia observable: preorden, inorden, postorden y niveles muestran distintos modos de visitar el mismo árbol.

El mantenimiento de alturas y enlaces `parent` permite operaciones eficientes como calcular sucesores, predecesores y actualizar cambios hacia la raíz. En un BST, la búsqueda ordenada depende de comparar y descartar ramas; su inorden produce una secuencia ordenada. En un heap, la prioridad permite que el mínimo esté siempre en la raíz, con `add` y `remove` en O(log n), y construcción por `heapify` en O(n).

Para defender correctitud usaría varias evidencias: pruebas públicas e internas, salidas de demos, trazados manuales, invariantes y complejidad. Las pruebas muestran que ciertos casos funcionan; los invariantes explican por qué deben funcionar en general; los trazados permiten seguir punteros, rotaciones o cambios de arreglo; y la complejidad permite justificar por qué una estructura es adecuada para cierto problema.

---

### Autoevaluación breve

- **Qué puedo defender con seguridad:** la diferencia entre árbol enlazado, BST y heap; los recorridos; la relación entre inorden y orden en BST; y la razón por la cual `top()` en un min-heap devuelve el mínimo.
- **Qué todavía confundo:** algunos detalles de implementación pueden depender del código exacto de la semana, especialmente si `find()` devuelve solo coincidencias o también último nodo visitado.
- **Qué evidencia usaría en una sustentación:** secuencias de recorridos, inorden ordenado del BST, extracción ordenada del heap, `isBST()`, `isHeap()`, `checkParentLinks()` y trazados manuales de `lowerBound`, `upperBound`, rotaciones y eliminación.
- **Qué parte del código me parece más importante para revisar otra vez:** `succ()`, `pred()`, `remove()` en BST, `splice`, rotaciones, `bubbleUp`, `trickleDown`, `attachAsLC/RC`, `secede` y `removeSubtree`.
