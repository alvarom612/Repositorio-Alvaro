## Actividad 3-CC232

### Integrantes
- Alvaro Raul Montoya Dulanto

---

## Bloque 0 - Instalación y preparación

1. Carpeta de trabajo: `Semana3/`.
2. Archivo de entrega creado: `actividad3-CC232.md`.
3. Lecturas revisadas: `Parte3-Deng.docx` y `Parte3-Morin.docx`.
4. Demo sugerida para verificar compilación:

```bash
g++ -std=c++17 -I Semana3/include Semana3/demos/demo_sllist.cpp -o demo_sllist
./demo_sllist
```

5. Prueba pública sugerida:

```bash
g++ -std=c++17 -I Semana3/include Semana3/pruebas_publicas/test_public_week3.cpp -o test_public_week3
./test_public_week3
```

El objetivo de esta verificación no es solo obtener una salida correcta, sino comprobar que las operaciones básicas respetan tamaño lógico, orden de los elementos, actualización de punteros e invariantes de cada estructura.

---

## Bloque 1 - Núcleo conceptual de la semana

### 1. ¿Qué cambia al pasar de almacenamiento contiguo a almacenamiento dinámico?

En almacenamiento contiguo, los elementos viven en posiciones consecutivas de memoria, como en un arreglo dinámico. Esto favorece el acceso por índice y la localidad de caché, pero insertar o eliminar en medio suele requerir desplazar elementos.

En almacenamiento dinámico enlazado, cada elemento vive en un nodo que puede estar en cualquier zona de memoria. El orden lógico no lo da la dirección física, sino los enlaces entre nodos. Esto permite insertar o eliminar localmente cambiando punteros, aunque empeora el acceso directo por índice porque hay que recorrer enlaces.

### 2. Diferencia entre acceso por rango y acceso por posición o enlace

El acceso por rango significa acceder mediante un índice entero, por ejemplo `get(i)`. En un arreglo esto es natural porque se calcula la dirección como base más desplazamiento.

El acceso por posición o enlace significa operar desde un nodo, cursor, iterador o referencia ya localizada. En una lista enlazada, tener la posición correcta es lo importante: si ya tenemos el nodo anterior o el nodo actual, insertar o eliminar puede ser constante. Si solo tenemos el índice, primero hay que recorrer.

### 3. ¿Por qué una lista enlazada mejora inserciones y eliminaciones locales, pero empeora el acceso por índice?

Mejora inserciones y eliminaciones locales porque no desplaza todos los elementos posteriores. Solo crea o libera un nodo y cambia un número pequeño de enlaces.

Empeora el acceso por índice porque la lista no permite saltar directamente a la posición `i`. Para encontrarla, hay que avanzar nodo por nodo desde algún extremo. Por eso el costo pasa de `O(1)` en un arreglo a `O(i)` o `O(n)` en una lista simplemente enlazada, y a `O(1 + min(i, n-i))` en una doblemente enlazada con acceso desde ambos extremos.

### 4. ¿Por qué `SLList` implementa bien operaciones de `Stack` y `Queue`?

`SLList` mantiene normalmente `head`, `tail` y `n`.

Como pila, puede hacer `push` y `pop` por el frente en `O(1)`: insertar en `head` y retirar de `head`.

Como cola, puede insertar al final usando `tail` en `O(1)` y retirar del frente usando `head` en `O(1)`. Eso respeta FIFO: el primero que entra por atrás es el primero que sale por adelante.

### 5. ¿Por qué `SLList` no implementa naturalmente todas las operaciones de un `Deque` con el mismo costo?

Un `Deque` necesita insertar y eliminar en ambos extremos. En una lista simplemente enlazada es fácil insertar al frente, eliminar al frente e insertar al final si se tiene `tail`. El problema es eliminar al final: para quitar `tail`, hay que conocer el nodo anterior al último, pero `tail` no apunta hacia atrás. Encontrarlo exige recorrer la lista desde `head`, por lo que esa operación cuesta `O(n)`.

### 6. ¿Qué aporta el nodo centinela `dummy` en `DLList`?

El nodo `dummy` actúa como centinela y evita tratar por separado los casos de lista vacía, inserción al inicio, inserción al final o eliminación del único nodo. En una implementación circular, `dummy.next` apunta al primer nodo y `dummy.prev` al último; si la lista está vacía, ambos apuntan a `dummy`.

Así, toda inserción se puede expresar como “insertar antes de un nodo existente” y toda eliminación como “desconectar un nodo existente”, sin preguntar constantemente si se está en un caso borde.

### 7. ¿Por qué `DLList` justifica `get(i)`, `set(i,x)`, `add(i,x)` y `remove(i)` con costo `O(1 + min(i, n-i))`?

Porque `DLList` puede buscar el nodo desde el extremo más cercano:

- si `i < n/2`, avanza desde el inicio;
- si `i >= n/2`, retrocede desde el final.

La búsqueda cuesta `O(1 + min(i, n-i))`. Después de encontrar el nodo, leer, escribir, insertar antes o eliminarlo cuesta `O(1)` porque solo se actualizan enlaces `prev` y `next`.

### 8. ¿Cuál es la idea espacial central de `SEList`?

`SEList` combina enlaces entre bloques con almacenamiento contiguo dentro de cada bloque. En vez de un nodo por elemento, usa nodos que contienen pequeños arreglos/deques de tamaño aproximadamente `b`. Esto reduce el costo espacial por elemento, porque se usan menos punteros que en una lista enlazada tradicional.

Su idea central es mantener bloques bastante llenos para que el desperdicio sea bajo, pero permitir inserciones y eliminaciones locales moviendo pocos elementos dentro de bloques cercanos.

### 9. ¿Por qué `SEList` reutiliza una `BDeque` basada en `ArrayDeque`?

Porque cada bloque necesita comportarse como un pequeño deque/arreglo circular: insertar, eliminar y desplazar localmente elementos dentro del bloque. `ArrayDeque` ya ofrece una representación contigua circular adecuada para ese trabajo. `SEList` reutiliza esa lógica para concentrarse en el manejo de bloques, balanceo, `spread()` y `gather()`.

### 10. ¿Qué papel cumple `DengList` y por qué no reemplaza a las estructuras de Morin?

`DengList` refuerza la interfaz de lista como ADT: operaciones de recorrido, inserción, eliminación, búsqueda, reversa, ordenamiento y eliminación de duplicados. Sirve como capa algorítmica más rica.

No reemplaza a `SLList`, `DLList` o `SEList` porque estas estructuras de Morin explican decisiones de representación, punteros, invariantes y costos concretos. `DengList` complementa: permite reutilizar algoritmos sobre una interfaz de lista, mientras las estructuras de Morin muestran cómo se implementa eficientemente cada representación.

---

## Bloque 2 - Demostración y trazado guiado

### Tabla de demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
|---|---|---|---|
| `demo_sllist.cpp` | Se observan inserciones y eliminaciones por frente y por final, además del cambio de tamaño. | Una `SLList` con `head`, `tail` y `n` puede comportarse como pila y como cola. | `push/pop` por el frente son `O(1)`; `add` al final con `tail` es `O(1)`; quitar el último no es natural en `O(1)`. |
| `demo_dllist.cpp` | Se observa inserción/eliminación en posiciones intermedias y recorrido en orden. | Lista doblemente enlazada con enlaces `prev` y `next`, usualmente con `dummy`. | Ubicar el nodo cuesta `O(1 + min(i,n-i))`; cambiar enlaces después de ubicarlo cuesta `O(1)`. |
| `demo_selist.cpp` | La salida conserva el orden lógico aunque internamente haya bloques. | Lista de bloques: cada nodo contiene una pequeña estructura contigua. | Reduce punteros por elemento y mantiene acceso/actualización local balanceados. |
| `demo_deng_list.cpp` | Se observan operaciones de ADT de lista más ricas: ordenar, invertir, eliminar duplicados o recorrer. | Lista como interfaz algorítmica completa. | Favorece reutilización de algoritmos sin atarse a una sola representación. |
| `demo_morin_deng_bridge.cpp` | Una estructura de Morin se transforma, procesa con Deng y vuelve con el resultado. | Puente entre representación estructural y algoritmos de lista. | Se paga conversión `O(n)`, pero se evita reescribir algoritmos para cada estructura. |
| `demo_capitulo3_panorama.cpp` | Compara varias estructuras del capítulo y muestra sus operaciones típicas. | Panorama de listas enlazadas y variantes. | Relaciona representación, operación dominante y costo esperado. |
| `demo_min_structures.cpp` | `min()` responde sin recorrer toda la estructura. | Se guarda información adicional junto con los valores. | Se usa espacio extra para conseguir mínimo en `O(1)` o amortizado `O(1)`. |
| `demo_xor_list.cpp` | Se recorre una lista que codifica enlaces mediante XOR. | Ahorro de punteros combinando anterior y siguiente. | Reduce espacio por nodo, pero complica implementación, seguridad y depuración. |
| `demo_linked_adapters.cpp` | Se usan `LinkedStack`, `LinkedQueue` y `LinkedDeque` con interfaces diferentes. | Adaptadores sobre estructuras enlazadas existentes. | Reutilizar evita duplicar lógica y permite defender costos heredados. |
| `demo_contiguous_vs_linked.cpp` | Contrasta acceso por índice, inserción local y memoria contigua/enlazada. | Comparación entre arreglo dinámico/deque contiguo y nodos enlazados. | Contiguo favorece caché e índice; enlazado favorece cambios locales por enlaces. |

### 1. En `demo_sllist.cpp`, ¿qué secuencia deja más clara la coexistencia de pila y cola?

La secuencia más clara es insertar elementos con operaciones tipo `push` en el frente y luego retirarlos con `pop`, mostrando LIFO, y después insertar con `add` al final y retirar con `remove` desde el frente, mostrando FIFO. Esa comparación evidencia que la misma `SLList` puede sostener ambas interfaces cuando las operaciones elegidas coinciden con sus extremos eficientes.

### 2. En `demo_dllist.cpp`, ¿qué operación muestra mejor la inserción en una posición intermedia?

La operación `add(i, x)` con un índice que no sea ni `0` ni `n`, por ejemplo insertar en la mitad de la lista. Esa operación obliga a localizar un nodo interno con `getNode(i)` y luego insertar antes de él actualizando cuatro enlaces: el anterior del nuevo nodo, el siguiente del nuevo nodo, el `next` del nodo previo y el `prev` del nodo siguiente.

### 3. En `demo_selist.cpp`, ¿qué observable permite defender que la lista mantiene orden lógico aunque internamente trabaje por bloques?

El observable es que al imprimir o recorrer la lista, los elementos aparecen en el orden lógico esperado después de inserciones y eliminaciones. Aunque internamente se hayan movido elementos entre bloques por `spread()` o `gather()`, la interfaz `get(i)` y el recorrido preservan la secuencia abstracta de la lista.

### 4. En `demo_deng_list.cpp`, ¿qué evidencia muestra que Deng ofrece operaciones más cercanas a un ADT de lista completo?

La evidencia es la disponibilidad de operaciones de alto nivel como ordenar, invertir, buscar, eliminar duplicados o recorrer mediante una interfaz uniforme. No se trabaja solo con punteros internos, sino con operaciones propias del tipo abstracto de datos lista.

### 5. En `demo_morin_deng_bridge.cpp`, ¿qué salida justifica reutilización de algoritmos?

La parte donde una lista de Morin aparece transformada después de aplicar una operación de Deng, por ejemplo ordenada, invertida o sin duplicados. Eso muestra que la estructura base no implementó necesariamente el algoritmo internamente; el puente convirtió a `DengList`, aplicó el algoritmo y asignó el resultado de vuelta.

### 6. En `demo_min_structures.cpp`, ¿qué diferencia conceptual hay entre almacenar valores y almacenar información adicional para `min()`?

Almacenar solo valores obliga a recorrer todos los elementos para calcular el mínimo. Almacenar información adicional, como el mínimo acumulado en cada nodo de una pila auxiliar, permite responder `min()` inmediatamente. Se cambia espacio extra por menor tiempo de consulta.

### 7. En `demo_linked_adapters.cpp`, ¿qué adaptador representa mejor la reutilización?

`LinkedQueue` es un ejemplo muy claro: reutiliza `SLList` y solo expone operaciones de cola. Internamente aprovecha `add` por `tail` y `remove` por `head`. También `LinkedDeque` es buen ejemplo porque reutiliza `DLList` para obtener operaciones eficientes en ambos extremos.

### 8. En `demo_contiguous_vs_linked.cpp`, ¿qué contraste se observa?

La representación contigua favorece acceso por índice y localidad de memoria, porque los elementos están cercanos físicamente. La representación enlazada favorece inserciones y eliminaciones locales cuando ya se conoce la posición, porque basta con cambiar enlaces. La desventaja enlazada es que el acceso por índice exige recorrido y los nodos pueden estar dispersos en memoria.

---

## Bloque 3 - Pruebas públicas, stress y correctitud

### 1. ¿Qué operaciones mínimas valida la prueba pública para `SLList`?

Valida que la lista simplemente enlazada mantenga correctamente inserción, eliminación, consulta de tamaño, estado vacío y orden observable. En particular, debe comprobar operaciones tipo pila/cola: insertar al frente, retirar del frente, insertar al final y verificar que `head`, `tail` y `n` sigan siendo coherentes.

### 2. ¿Qué operaciones mínimas valida la prueba pública para `DLList`?

Valida operaciones por índice: `get(i)`, `set(i,x)`, `add(i,x)` y `remove(i)`, además de tamaño y orden. También debe exponer que insertar o eliminar al inicio, en medio y al final no rompe los enlaces dobles ni el centinela.

### 3. ¿Qué operaciones mínimas valida la prueba pública para `SEList`?

Valida que `SEList` conserve el orden lógico y el tamaño después de inserciones, eliminaciones, consultas y actualizaciones. También busca detectar errores de balanceo entre bloques, especialmente cuando las operaciones obligan a redistribuir elementos.

### 4. ¿Qué operaciones nuevas quedan cubiertas por `test_public_extras.cpp`?

Cubre estructuras y operaciones adicionales de la semana, como variantes con mínimo (`MinStack`, `MinQueue`, `MinDeque`), listas limpias o auxiliares, `XorList` y operaciones extendidas como reversa, deduplicación, rotación o verificaciones de consistencia, según la organización del archivo. Su función es comprobar comportamiento más allá del núcleo `SLList`/`DLList`/`SEList`.

### 5. ¿Qué valida `test_public_linked_adapters.cpp`?

Valida que los adaptadores respeten su interfaz:

- `LinkedStack`: comportamiento LIFO.
- `LinkedQueue`: comportamiento FIFO.
- `LinkedDeque`: inserción y eliminación en ambos extremos.

También valida que adaptar una estructura existente no cambie su semántica ni rompa el tamaño lógico.

### 6. ¿Qué demuestra `test_public_deng_bridge.cpp`?

Demuestra que la conversión entre estructuras de Morin y `DengList` preserva elementos y orden cuando corresponde, y que algoritmos como ordenar, invertir o eliminar duplicados pueden aplicarse sin reescribir la lógica estructural de `DLList` o `SEList`.

### 7. En `stress_selist_week3.cpp`, ¿qué comportamiento intenta estresar?

Intenta estresar crecimiento, borrado masivo, inserciones en distintas posiciones, eliminaciones repetidas y mantenimiento del tamaño lógico. El objetivo es forzar situaciones donde `SEList` deba ejecutar `spread()` y `gather()` para mantener bloques balanceados y no perder elementos.

### 8. ¿Qué sí demuestra una prueba pública sobre una estructura enlazada?

Demuestra que, para ciertos casos observados, la estructura produce resultados correctos: orden esperado, tamaño correcto, operaciones básicas funcionales y ausencia de fallos evidentes de ejecución.

### 9. ¿Qué no demuestra una prueba pública por sí sola?

No demuestra correctitud total. Puede no cubrir todos los casos borde, todos los tamaños, todas las intercalaciones de operaciones ni todos los errores de memoria. Tampoco prueba por sí sola la complejidad asintótica.

### 10. ¿Por qué pasar pruebas no reemplaza explicar invariantes, punteros y complejidad?

Porque una estructura enlazada puede pasar casos simples y aun así tener errores latentes en punteros, memoria, casos borde o costos. La defensa debe explicar qué invariante se mantiene, qué enlaces cambian, por qué no se pierden nodos, por qué el tamaño es correcto y qué recorrido justifica el costo.

---

## Bloque 4 - `SLList`, `DLList` y `SEList`: lectura cercana del código

### 1. En `SLList`, ¿qué papel cumplen `head`, `tail` y `n`?

`head` apunta al primer nodo, `tail` apunta al último nodo y `n` guarda el número de elementos. Estos tres campos sostienen los invariantes principales:

- si `n == 0`, `head == nullptr` y `tail == nullptr`;
- si `n > 0`, `head` llega a todos los nodos siguiendo `next`;
- `tail->next == nullptr`;
- al contar nodos desde `head`, se obtiene exactamente `n`.

### 2. En `SLList::push`, `pop`, `add` y `remove`, ¿qué punteros cambian?

En `push(x)`, se crea un nuevo nodo `u`. El `next` de `u` apunta al antiguo `head`, luego `head` pasa a ser `u`. Si la lista estaba vacía, `tail` también pasa a ser `u`.

En `pop()`, se guarda el nodo actual de `head`, luego `head` avanza a `head->next`. Si la lista queda vacía, `tail` se vuelve `nullptr`.

En `add(x)` al final, se crea un nodo `u` con `u->next == nullptr`. Si la lista está vacía, `head` y `tail` apuntan a `u`; si no, `tail->next = u` y luego `tail = u`.

En `remove()`, si se refiere a retirar del frente, cambia igual que `pop`: se desconecta el primer nodo y `head` avanza. En todos los casos se actualiza `n`.

### 3. ¿Cómo funciona `secondLast()` y por qué no puede resolverse directamente con solo mirar `tail`?

`secondLast()` recorre desde `head` hasta encontrar un nodo `u` tal que `u->next == tail`. Ese nodo es el penúltimo.

No puede resolverse mirando solo `tail` porque en una lista simplemente enlazada no existe enlace hacia atrás. `tail` sabe cuál es el último nodo, pero no sabe quién lo precede.

### 4. ¿Cómo funciona `reverse()` y por qué no necesita estructura auxiliar?

`reverse()` invierte los enlaces `next` uno por uno. Usa tres referencias temporales:

1. `prev`, inicialmente `nullptr`;
2. `curr`, inicialmente `head`;
3. `next`, para no perder el resto de la lista.

En cada paso guarda `next = curr->next`, cambia `curr->next = prev`, avanza `prev = curr` y `curr = next`. Al final, el antiguo `head` se vuelve `tail` y `prev` se vuelve el nuevo `head`.

No necesita estructura auxiliar porque reutiliza los mismos nodos y solo cambia direcciones de enlaces. Su costo es `O(n)` y su espacio extra es `O(1)`.

### 5. ¿Qué verifica `checkSize()` y por qué ayuda a defender correctitud?

`checkSize()` recorre la lista y cuenta nodos. Luego compara ese conteo con `n`. También puede verificar invariantes como lista vacía coherente, `tail` alcanzable desde `head` y `tail->next == nullptr`.

Ayuda porque detecta inconsistencias comunes: olvidar incrementar o decrementar `n`, perder nodos, crear enlaces incorrectos o dejar `tail` apuntando a un nodo que ya no corresponde.

### 6. En `DLList`, ¿por qué `getNode(i)` puede empezar desde el inicio o desde el final?

Porque cada nodo tiene `next` y `prev`. Si el índice está cerca del inicio, conviene avanzar desde `dummy.next`. Si está cerca del final, conviene retroceder desde `dummy.prev`. Así se recorre la menor distancia posible.

### 7. En `DLList::addBefore`, ¿qué enlaces se actualizan y por qué el centinela elimina casos borde?

Para insertar un nuevo nodo `w` antes de un nodo `u`:

```text
w.prev = u.prev
w.next = u
u.prev.next = w
u.prev = w
```

El centinela elimina casos borde porque incluso insertar al inicio significa insertar antes del antiguo primer nodo, e insertar al final significa insertar antes de `dummy`. Siempre existen nodos vecinos válidos, por lo que no se necesitan ramas especiales para `nullptr`.

### 8. ¿Cómo funciona `rotate(r)` sin mover datos elemento por elemento?

`rotate(r)` normaliza `r` respecto a `n` y cambia qué segmento queda al inicio. En una lista doblemente enlazada se puede lograr reconectando enlaces: se corta la lista en una posición y se une el sufijo con el prefijo. Los datos no se copian ni se desplazan uno por uno; solo cambian punteros entre nodos.

### 9. ¿Cómo `isPalindrome()` aprovecha la naturaleza doblemente enlazada?

Usa dos punteros: uno desde el inicio (`dummy.next`) y otro desde el final (`dummy.prev`). Compara valores y avanza el primero hacia adelante mientras el segundo retrocede. Se detiene cuando se cruzan o se encuentran. Esto es natural en `DLList` porque se puede avanzar y retroceder en `O(1)` por paso.

### 10. En `SEList`, ¿qué representa `Location`?

`Location` representa una posición física dentro de la estructura: normalmente un par formado por el nodo/bloque y el índice local dentro de ese bloque. Traduce un índice lógico `i` de la lista a una ubicación concreta `(bloque, posición interna)`.

### 11. ¿Qué hacen `spread()` y `gather()`?

`spread()` aparece cuando se intenta insertar cerca de una zona con bloques llenos. Redistribuye elementos entre varios bloques, e incluso crea un bloque nuevo, para dejar espacio sin desplazar toda la lista.

`gather()` aparece cuando se elimina y quedan bloques demasiado vacíos. Recolecta elementos de bloques vecinos y puede eliminar un bloque sobrante para recuperar densidad.

Ambas funciones mantienen el invariante de que los bloques estén suficientemente ocupados, salvo posibles excepciones controladas cerca del final.

### 12. ¿Cómo afecta el tamaño de bloque `b`?

Un `b` grande reduce la cantidad de nodos y punteros, mejorando el uso espacial y la localidad dentro de cada bloque. Pero puede aumentar el costo de mover elementos dentro de un bloque.

Un `b` pequeño reduce el trabajo local al insertar o eliminar, pero aumenta el número de bloques y de enlaces. Por eso `SEList` es un compromiso entre acceso, actualización local y espacio.

---

## Bloque 5 - Adaptadores y estructuras derivadas

### 1. ¿Cómo reutiliza `LinkedStack` a `SLList`?

`LinkedStack` encapsula una `SLList` y expone operaciones de pila. `push(x)` se implementa con inserción al frente de `SLList`, y `pop()` con eliminación del frente. Así obtiene LIFO en `O(1)`.

### 2. ¿Cómo reutiliza `LinkedQueue` a `SLList`?

`LinkedQueue` usa `SLList` para implementar FIFO. Inserta al final usando `tail` y elimina del frente usando `head`. Ambas operaciones son `O(1)` en una `SLList` con `head` y `tail`.

### 3. ¿Por qué `LinkedDeque` se construye naturalmente sobre `DLList` y no sobre `SLList`?

Porque un deque necesita operar eficientemente en ambos extremos. `DLList` permite insertar y eliminar al inicio y al final en `O(1)` usando enlaces dobles y centinela. `SLList`, en cambio, no puede eliminar el último nodo en `O(1)` porque no tiene enlace al nodo anterior a `tail`.

### 4. En `MinStack`, ¿por qué cada entrada guarda valor y mínimo acumulado?

Porque así `min()` puede responder en `O(1)`. Cada nodo o entrada guarda el valor insertado y el menor valor visto desde el fondo hasta esa posición. Al desapilar, también se elimina el mínimo correspondiente al estado anterior.

### 5. En `MinQueue`, ¿por qué dos pilas mantienen FIFO y mínimo?

Una cola con dos pilas usa una pila de entrada y una pila de salida. Los elementos nuevos entran a la pila de entrada. Cuando se necesita desencolar y la pila de salida está vacía, se transfieren los elementos desde entrada hacia salida, invirtiendo el orden y restaurando FIFO.

Si ambas pilas son `MinStack`, el mínimo de la cola es el menor entre el mínimo de entrada y el mínimo de salida. Las transferencias cuestan `O(n)` en un momento puntual, pero cada elemento se mueve pocas veces, por lo que las operaciones son amortizadas `O(1)`.

### 6. En `MinDeque`, ¿qué problema resuelve el rebalanceo entre `front_` y `back_`?

Resuelve el problema de mantener operaciones eficientes en ambos extremos. Si un lado queda vacío y se necesita eliminar desde ese extremo, se redistribuyen elementos desde el otro lado para restaurar capacidad de operación. El rebalanceo evita que una operación quede bloqueada y mantiene los costos amortizados.

### 7. Comparen implementar una estructura y adaptar una estructura existente

Implementar una estructura significa definir su representación interna, memoria, punteros e invariantes. Por ejemplo, implementar `DLList` requiere manejar nodos, `prev`, `next`, `dummy` y tamaño.

Adaptar una estructura existente significa reutilizar una implementación ya correcta y exponer otra interfaz. Por ejemplo, `LinkedStack` adapta `SLList` para ofrecer pila; `LinkedDeque` adapta `DLList` para ofrecer deque. El adaptador no reinventa los punteros: delega en la estructura base.

### 8. ¿Qué operaciones pueden defender como constantes y cuáles amortizadas?

Constantes `O(1)`:

- `LinkedStack::push`, `LinkedStack::pop`, `top`, `empty`, `size`.
- `LinkedQueue::enqueue` y `dequeue` si usan `tail` y `head`.
- Operaciones en extremos de `LinkedDeque` basado en `DLList`.
- `MinStack::push`, `pop` y `min`.

Amortizadas `O(1)`:

- `MinQueue::enqueue`, `dequeue` y `min`, porque las transferencias entre pilas se distribuyen sobre muchas operaciones.
- Operaciones de `MinDeque` que requieran rebalanceo ocasional entre `front_` y `back_`.

---

## Bloque 6 - Deng como refuerzo algorítmico y puente de integración

### 1. ¿Qué operaciones del ADT de lista aparecen reforzadas en `DengList`?

Aparecen reforzadas operaciones como insertar, eliminar, consultar, modificar, recorrer, buscar, invertir, ordenar y eliminar duplicados. Esto acerca la estructura a una lista abstracta completa, no solo a una colección de nodos.

### 2. ¿Qué ventaja tiene encapsular una lista más rica sin cambiar las estructuras de Semana 3?

Permite agregar algoritmos de alto nivel sin alterar `SLList`, `DLList` o `SEList`. Eso reduce duplicación, mantiene separada la representación de los algoritmos y evita introducir errores en estructuras que ya tienen invariantes delicados.

### 3. ¿Qué hacen `to_deng` y `assign_from_deng`?

`to_deng` recorre una estructura de Morin y copia sus elementos a una `DengList`.

`assign_from_deng` toma el contenido de una `DengList` y lo asigna de vuelta a la estructura original, reconstruyendo o reemplazando su contenido lógico.

Ambas funciones actúan como conversores entre una representación estructural y una interfaz algorítmica.

### 4. ¿Por qué `stable_sort_with_deng` no obliga a reimplementar ordenamiento en `DLList` o `SEList`?

Porque el ordenamiento se aplica en `DengList`. El proceso es:

1. convertir la lista de Morin a `DengList`;
2. aplicar ordenamiento estable en la lista de Deng;
3. copiar el resultado de vuelta.

Así, `DLList` y `SEList` no necesitan conocer los detalles del algoritmo de ordenamiento.

### 5. ¿Qué hace `dedup_with_deng` y qué relación tiene con `deduplicate()` o `uniquify()`?

`dedup_with_deng` elimina elementos repetidos usando las operaciones de Deng y luego refleja el resultado en la estructura original. Se relaciona con `deduplicate()` cuando elimina duplicados en una lista no necesariamente ordenada, y con `uniquify()` cuando aprovecha que elementos iguales están consecutivos en una lista ordenada.

### 6. ¿Por qué `reverse_with_deng` es reutilización sobre una interfaz común?

Porque invertir una secuencia es un algoritmo sobre el orden lógico de los elementos, no necesariamente sobre punteros concretos. Si varias estructuras pueden convertirse a una interfaz común, el mismo algoritmo de reversa se reutiliza para todas sin reescribirlo para cada representación.

### 7. ¿Qué costo adicional introduce la conversión y cuándo vale la pena?

La conversión introduce costo `O(n)` en tiempo y, normalmente, `O(n)` en espacio adicional. Vale la pena cuando el algoritmo que se reutiliza es complejo, cuando se aplica pocas veces en comparación con el tamaño del proyecto, cuando se busca claridad o cuando evita implementar y depurar versiones repetidas para cada estructura.

---

## Bloque 7 - Comparación enlazado vs contiguo, variantes y evidencia experimental

### 1. Comparen `ArrayDeque` y `LinkedDeque`

`ArrayDeque` usa un arreglo circular contiguo. Sus elementos están en una zona compacta de memoria y el índice lógico se traduce a una posición física mediante aritmética modular. Las operaciones en extremos son amortizadas `O(1)`, pero cuando el arreglo crece puede requerir realocar y copiar.

`LinkedDeque` usa nodos enlazados, normalmente con `prev` y `next`. Sus operaciones en extremos son `O(1)` sin copiar todo el contenido, pero cada elemento paga espacio adicional por punteros y pierde localidad de memoria.

### 2. ¿Qué significa mejor localidad de memoria en representación contigua?

Significa que elementos cercanos lógicamente también están cercanos físicamente. Esto favorece la caché del procesador: al leer un elemento, es probable que los siguientes ya estén cargados o sean más rápidos de acceder. Por eso, una estructura contigua puede ser más rápida en la práctica aunque dos estructuras tengan la misma complejidad asintótica.

### 3. ¿Qué operaciones favorecen más a la representación enlazada?

Favorece inserciones y eliminaciones locales cuando ya se tiene el nodo o posición cercana. También favorece operaciones en extremos en listas diseñadas para ello, porque no requiere desplazar elementos ni redimensionar arreglos.

### 4. En el benchmark, ¿qué comparación sirve para acceso aleatorio y cuál para extremos?

Para discutir acceso aleatorio, la comparación más útil es entre una estructura contigua como `ArrayDeque` o arreglo dinámico y una lista enlazada donde `get(i)` exige recorrido.

Para discutir operaciones en extremos, conviene comparar `ArrayDeque` y `LinkedDeque`, porque ambas ofrecen operaciones eficientes al inicio y al final, pero con costos prácticos distintos: arreglo circular con posible realocación frente a nodos con punteros y asignaciones dinámicas.

### 5. ¿Por qué el benchmark no prueba superioridad absoluta?

Porque los resultados dependen del tamaño de entrada, compilador, optimizaciones, caché, asignador de memoria, patrón de operaciones y máquina usada. Un benchmark mide un escenario específico; no reemplaza el análisis de complejidad ni la explicación de invariantes.

### 6. ¿Qué idea muestra `XorList` respecto al ahorro de punteros?

`XorList` muestra que se puede guardar en un solo campo la combinación XOR de las direcciones del nodo anterior y del siguiente. Conociendo uno de los vecinos, se puede recuperar el otro. La idea es reducir de dos punteros por nodo a un campo combinado.

### 7. ¿Qué desventaja práctica introduce `XorList`?

Aunque ahorra espacio, complica mucho la implementación. Es más difícil de depurar, menos segura, depende de manipulación de direcciones, dificulta iteradores robustos y puede ser problemática con herramientas modernas de memoria, recolectores de basura o sanitizadores. Es interesante conceptualmente, pero menos práctica que una `DLList` convencional.

---

## Bloque 8 - Cierre comparativo y preparación de sustentación

Pasar de usar arreglos dinámicos a diseñar estructuras enlazadas y adaptadores sobre nodos cambia la forma de pensar la lista. En un arreglo dinámico, la representación principal es un bloque contiguo de memoria y el índice es el mecanismo natural de acceso. En una estructura enlazada, la representación principal son nodos conectados por punteros, y el orden lógico se obtiene siguiendo enlaces.

Esto cambia el acceso importante: en estructuras contiguas domina el acceso por rango o índice, porque `get(i)` puede resolverse con aritmética de direcciones. En listas enlazadas domina el acceso por posición, nodo o enlace, porque una operación es eficiente cuando ya se tiene cerca el nodo donde se modificará la estructura.

También cambian las inserciones y eliminaciones locales. En un arreglo, insertar o eliminar en medio requiere desplazar elementos; en una lista enlazada, si ya se tiene la posición, basta con actualizar punteros. Esa ventaja local se paga con peor acceso aleatorio y, muchas veces, con peor localidad de memoria.

En complejidad, `SLList` ofrece muy buen soporte para pila y cola: operaciones por el frente y encolado por atrás pueden ser `O(1)`, pero no implementa naturalmente todas las operaciones de deque en `O(1)` porque no puede encontrar el penúltimo nodo desde `tail`. `DLList` mejora la navegación al tener `prev` y `next`; con nodo centinela puede insertar y eliminar limpiamente, y sus operaciones por índice cuestan `O(1 + min(i,n-i))`. `SEList` busca un compromiso: usa bloques para reducir el espacio por punteros y conservar un acceso/actualización local razonable, con costos dependientes de la búsqueda de bloque y del tamaño `b`.

Los adaptadores y puentes muestran otra idea importante: no siempre se necesita reimplementar una estructura. `LinkedStack`, `LinkedQueue` y `LinkedDeque` reutilizan `SLList` o `DLList` para ofrecer nuevas interfaces. `MorinDengBridge` permite usar algoritmos de `DengList`, como ordenar, invertir o eliminar duplicados, sobre estructuras de Morin mediante conversión.

La comparación final es que la representación contigua suele ganar en acceso por índice, compacidad y localidad de caché, mientras la representación enlazada gana en flexibilidad local y cambios por enlaces. Elegir una u otra depende de la operación dominante: si se consulta mucho por índice, conviene contiguo; si se insertan y eliminan posiciones ya localizadas, conviene enlazado; si se busca equilibrio entre espacio, acceso y actualización local, una estructura por bloques como `SEList` es una alternativa intermedia.

---

## Autoevaluación breve

### Qué podemos defender con seguridad

Podemos defender la diferencia entre representación contigua y enlazada, los costos principales de `SLList`, `DLList` y `SEList`, el papel de `head`, `tail`, `n` y `dummy`, y la utilidad de adaptadores y puentes para reutilizar lógica.

### Qué todavía confundimos

Debemos revisar con más detalle las salidas exactas de cada demo y los nombres precisos de las funciones en los archivos de la semana. También conviene practicar el trazado de `spread()` y `gather()` con un ejemplo concreto de bloques.

### Qué evidencia usaríamos en una sustentación

Usaríamos:

- una ejecución de `demo_sllist.cpp` para mostrar pila y cola;
- una ejecución de `demo_dllist.cpp` para explicar inserción intermedia y nodo centinela;
- una ejecución de `demo_selist.cpp` para mostrar orden lógico por bloques;
- pruebas públicas para evidenciar comportamiento correcto;
- un trazado manual de punteros para demostrar invariantes;
- el demo del puente Morin-Deng para defender reutilización de algoritmos.