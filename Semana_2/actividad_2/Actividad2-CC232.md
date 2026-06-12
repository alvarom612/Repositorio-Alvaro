# Actividad 2 - CC232

## Integrantes

- Alvaro Raul Montoya Dulanto

---

## Bloque 1 - Núcleo conceptual de la semana

### 1. ¿Qué significa que un arreglo use memoria contigua?

Un arreglo usa memoria contigua cuando sus elementos están guardados en posiciones consecutivas de memoria. Si el primer elemento está en una dirección base `B`, entonces el elemento `A[i]` está a una distancia fija de esa base: aproximadamente `B + i * sizeof(T)`, donde `T` es el tipo del elemento.

La idea importante es que no hay que seguir punteros ni buscar nodo por nodo. La posición lógica `i` se traduce directamente en una posición física.

### 2. ¿Por qué acceder a `A[i]` cuesta `O(1)`?

El acceso a `A[i]` cuesta `O(1)` porque la dirección del elemento se calcula con aritmética simple sobre la dirección base. No depende de cuántos elementos tenga el arreglo.

La operación hace, conceptualmente:

```cpp
direccion(A[i]) = direccion_base + i * tamaño_del_elemento
```

Mientras `i` sea válido, no se recorren los elementos anteriores. Por eso el acceso aleatorio en arreglos es constante.

### 3. Diferencia entre `size` y `capacity`

`size` es la cantidad de elementos que realmente pertenecen a la estructura.

`capacity` es la cantidad de espacios reservados en el arreglo interno.

Por ejemplo, un vector puede tener:

```text
size = 5
capacity = 8
```

Eso significa que hay 5 elementos válidos y 3 posiciones libres preparadas para futuras inserciones. Las posiciones libres no forman parte lógica de la lista.

### 4. ¿Por qué un arreglo dinámico no puede crecer siempre "en el mismo sitio"?

Un arreglo dinámico necesita un bloque contiguo. Si se llena, no basta con pedir una celda más: tendría que existir memoria libre justo después del bloque actual. En general, el programa no puede garantizar eso porque esa memoria puede estar ocupada por otros objetos.

Por eso `resize()` normalmente hace lo siguiente:

1. reserva un bloque nuevo más grande;
2. copia o mueve los elementos antiguos;
3. libera el bloque anterior;
4. actualiza el puntero interno.

La estructura conserva la misma secuencia lógica, pero cambia su representación física.

### 5. ¿Por qué duplicar capacidad permite costo amortizado `O(1)` al insertar al final?

Insertar al final suele costar `O(1)` si todavía hay espacio. Cuando el arreglo se llena, se hace un `resize()` y se copian todos los elementos, lo cual cuesta `O(n)`.

La clave es que el costo caro no ocurre en cada inserción. Si la capacidad se duplica:

```text
1, 2, 4, 8, 16, ...
```

entonces, antes de volver a redimensionar, hay muchas inserciones baratas. En una secuencia de `n` inserciones, el costo total de todas las copias es una suma geométrica:

```text
1 + 2 + 4 + 8 + ... < 2n
```

Entonces el costo total de `n` inserciones es `O(n)`, y el costo promedio por inserción es `O(1)` amortizado.

### 6. Comparación entre `ArrayStack` y `DengVector`

Ambas estructuras usan la misma idea central: un arreglo interno, un tamaño lógico y una capacidad física. También comparten la necesidad de redimensionar y desplazar elementos cuando se inserta o elimina en posiciones intermedias.

La diferencia principal está en la intención de la interfaz:

- `ArrayStack` se presenta como una implementación de lista basada en arreglo, con operaciones como `get(i)`, `set(i, x)`, `add(i, x)` y `remove(i)`.
- `DengVector` se parece más a una abstracción didáctica de vector, con operaciones como `insert(r, e)`, `remove(r)`, `find(e)`, `traverse()` y `operator[]`.

En resumen, `ArrayStack` enfatiza la estructura de lista; `DengVector` enfatiza la interfaz de vector y su relación con el uso cotidiano de arreglos dinámicos.

### 7. ¿Qué mejora `FastArrayStack` respecto a `ArrayStack`?

`FastArrayStack` conserva la misma representación básica de `ArrayStack`, pero mejora la forma de mover elementos. En vez de desplazar elemento por elemento con ciclos manuales, usa operaciones de copia por bloques, como `copy` o `copy_backward`.

La complejidad asintótica no cambia:

- insertar en la posición `i` puede costar `O(n - i)`;
- eliminar en la posición `i` puede costar `O(n - i)`;
- insertar al final sigue siendo `O(1)` amortizado.

La mejora está en los factores constantes: la implementación puede ser más rápida porque delega los movimientos a rutinas optimizadas.

### 8. Idea espacial central de `RootishArrayStack`

`RootishArrayStack` reduce el desperdicio de espacio evitando un único arreglo grande con mucha capacidad libre. En su lugar, usa varios bloques:

```text
bloque 0: tamaño 1
bloque 1: tamaño 2
bloque 2: tamaño 3
bloque 3: tamaño 4
...
```

Con esta representación, la estructura puede crecer agregando bloques de tamaño incremental. El desperdicio de espacio queda acotado por `O(√n)`, en vez de poder ser lineal como en un arreglo dinámico que duplica capacidad.

### 9. ¿Por qué usa bloques de tamaños `1, 2, 3, ...`?

Porque la suma de los tamaños forma números triangulares:

```text
1 + 2 + 3 + ... + r = r(r + 1)/2
```

Esto permite que con `r` bloques se almacenen aproximadamente `r²/2` elementos. Por tanto, para almacenar `n` elementos se necesitan alrededor de `√n` bloques.

Esa relación es la razón de la palabra "Rootish": el número de bloques y el espacio sobrante crecen como una raíz cuadrada de `n`.

### 10. Relación entre representación, costo temporal y desperdicio espacial

La representación determina qué operaciones son fáciles, cuáles son costosas y cuánto espacio se desperdicia.

- Un arreglo contiguo permite acceso `O(1)` por índice.
- Una estructura dinámica basada en arreglo necesita capacidad extra para no redimensionar en cada inserción.
- Duplicar capacidad da inserciones al final `O(1)` amortizado, pero puede dejar espacio libre `O(n)`.
- `FastArrayStack` mantiene la misma representación que `ArrayStack`, pero mueve datos de forma más eficiente.
- `RootishArrayStack` cambia la representación a bloques crecientes para reducir el desperdicio espacial a `O(√n)`, pagando con un mapeo de índice más elaborado.

---

## Bloque 2 - Demostración y trazado guiado

### Tabla de demos

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo o espacio |
|---|---|---|---|
| `demo_array_basico.cpp` | Se observa que el arreglo tiene longitud fija y que sus posiciones se acceden por índice. También puede mostrar direcciones o valores consecutivos. | Un arreglo es un bloque de memoria contigua con posiciones numeradas. | Acceder a `A[i]` cuesta `O(1)` porque se calcula la dirección directamente. La longitud física no cambia sola. |
| `demo_arraystack.cpp` | Se insertan, consultan, modifican y eliminan elementos manteniendo el orden lógico. | `ArrayStack` implementa una lista sobre un arreglo dinámico. | `get` y `set` cuestan `O(1)`. `add(i, x)` y `remove(i)` pueden costar `O(n - i)` por desplazamientos. |
| `demo_arraystack_explicado.cpp` | Muestra con más detalle cuándo se desplazan elementos y cuándo ocurre `resize()`. | La estructura mantiene el invariante `0 <= size <= capacity`. | Los desplazamientos cuestan lineal en la cantidad de elementos movidos. El crecimiento por duplicación justifica costo amortizado `O(1)` al final. |
| `demo_fastarraystack.cpp` | Produce la misma secuencia lógica que `ArrayStack`, pero usando movimientos más eficientes. | Misma estructura lógica; distinta implementación del movimiento de elementos. | No cambia la complejidad asintótica, pero reduce constantes al usar copias por bloques. |
| `demo_rootisharraystack.cpp` | Se observa que los elementos se almacenan en bloques de tamaños crecientes. | Lista representada por bloques `1, 2, 3, ...`. | Acceder exige mapear índice a bloque y desplazamiento. El desperdicio espacial baja a `O(√n)`. |
| `demo_rootisharraystack_explicado.cpp` | Muestra el mapeo desde índice lógico hacia bloque y offset. | La posición lógica no coincide con una sola dirección base; se calcula con números triangulares. | Con `r` bloques hay capacidad `r(r+1)/2`. El número de bloques es `O(√n)`. |
| `demo_deng_vector.cpp` | Se observa el crecimiento de `capacity` cuando `size` alcanza la capacidad disponible. | Vector dinámico con `_size`, `_capacity` y `_elem`. | `expand()` copia elementos ocasionalmente; por duplicación, las inserciones al final son `O(1)` amortizado. |
| `demo_stl_vector_contraste.cpp` | Se comparan `size` y `capacity` de `std::vector` con el vector propio. | `std::vector` usa la misma idea conceptual de arreglo dinámico. | También reserva más espacio del usado para conseguir inserciones eficientes al final. |

### 1. En `demo_array_basico.cpp`, ¿qué deja claro sobre arreglo, longitud y asignación?

Deja claro que un arreglo tiene una longitud física determinada al momento de su creación. Esa longitud no representa necesariamente una lista dinámica; representa cuántas posiciones fueron reservadas.

También muestra que la asignación de memoria y el acceso por índice son ideas distintas: reservar un arreglo crea espacio para varios elementos; acceder a `A[i]` usa la posición `i` dentro de ese espacio.

### 2. En `demo_arraystack_explicado.cpp`, ¿qué operación muestra mejor el costo por desplazamientos?

La mejor operación para ver el costo por desplazamientos es insertar al comienzo, por ejemplo `add(0, x)` o `insert(0, x)`.

Si hay `n` elementos, insertar en la posición `0` obliga a mover todos los elementos una posición hacia la derecha. Por eso cuesta `O(n)`. Insertar en una posición intermedia mueve solo el sufijo desde esa posición, por lo que cuesta `O(n - i)`.

Eliminar al comienzo también es un buen ejemplo, porque todos los elementos restantes deben desplazarse una posición hacia la izquierda.

### 3. En `demo_fastarraystack.cpp`, ¿qué cambia aunque no cambie la complejidad asintótica?

Cambia la manera de copiar o desplazar elementos. La estructura sigue haciendo las mismas operaciones lógicas, pero usa movimientos por bloques en lugar de ciclos manuales.

La complejidad sigue siendo la misma: mover `k` elementos cuesta `O(k)`. Sin embargo, en la práctica puede ser más rápido porque las rutinas de copia están optimizadas.

### 4. En `demo_rootisharraystack_explicado.cpp`, ¿qué ejemplo explica mejor el mapeo de índice lógico a bloque y offset?

Un buen ejemplo es usar bloques de tamaños:

```text
bloque 0: tamaño 1 -> índice 0
bloque 1: tamaño 2 -> índices 1, 2
bloque 2: tamaño 3 -> índices 3, 4, 5
bloque 3: tamaño 4 -> índices 6, 7, 8, 9
```

Así, el índice lógico `7` cae en el bloque `3`, con offset `1`, porque el bloque `3` empieza en el índice `6`.

```text
i = 7
bloque = 3
offset = 7 - 6 = 1
```

Este ejemplo muestra que la estructura no busca linealmente el bloque: usa la relación con números triangulares.

### 5. En `demo_deng_vector.cpp`, ¿qué observable permite defender el crecimiento de `capacity`?

El observable clave es que `capacity` no aumenta en cada inserción. Aumenta solo cuando `size == capacity`.

Una secuencia típica puede verse así:

```text
size:     1  2  3  4  5  6  7  8  9
capacity: 1  2  4  4  8  8  8  8 16
```

Esto permite defender que el vector reserva espacio extra para evitar copiar en cada inserción.

### 6. En `demo_stl_vector_contraste.cpp`, ¿qué similitud conceptual se observa con `DengVector`?

La similitud principal es la separación entre `size` y `capacity`. Tanto `std::vector` como `DengVector` almacenan los elementos en un arreglo dinámico, reservan más espacio del usado y redimensionan cuando se agota la capacidad.

La diferencia es que `std::vector` es una implementación industrial robusta, mientras que `DengVector` sirve para entender la mecánica interna.

### 7. ¿Qué demo sirve mejor para defender amortización y cuál sirve mejor para defender uso de espacio?

Para defender amortización, las mejores demos son `demo_deng_vector.cpp` y `demo_arraystack_explicado.cpp`, porque muestran crecimiento de capacidad, copias ocasionales y muchas inserciones baratas entre redimensionamientos.

Para defender uso de espacio, la mejor demo es `demo_rootisharraystack_explicado.cpp`, porque muestra los bloques crecientes y la capacidad total `r(r+1)/2`.

---

## Bloque 3 - Pruebas públicas, stress y correctitud

### 1. ¿Qué operaciones mínimas valida la prueba pública para `ArrayStack`?

Una prueba pública mínima para `ArrayStack` debe validar:

- creación de una estructura vacía;
- consulta de `size`;
- inserción al final;
- inserción en una posición específica;
- lectura con `get(i)`;
- modificación con `set(i, x)`;
- eliminación con `remove(i)`;
- preservación del orden después de insertar y eliminar.

Lo más importante es verificar que después de cada operación se mantenga la secuencia esperada.

### 2. ¿Qué operaciones mínimas valida la prueba pública para `FastArrayStack`?

Para `FastArrayStack`, la prueba debe validar esencialmente las mismas operaciones que para `ArrayStack`, porque la interfaz lógica es la misma.

La diferencia es que aquí interesa confirmar que las copias por bloques no rompen el orden. En especial, deben probarse inserciones y eliminaciones al comienzo, en el medio y al final.

### 3. ¿Qué operaciones mínimas valida la prueba pública para `RootishArrayStack`?

Para `RootishArrayStack`, además de las operaciones normales de lista, es importante validar casos que crucen fronteras entre bloques.

Debe revisarse:

- insertar varios elementos hasta crear nuevos bloques;
- consultar índices ubicados en distintos bloques;
- modificar elementos con `set`;
- eliminar elementos y verificar que el orden se conserva;
- probar posiciones cercanas a límites triangulares, como `0`, `1`, `2`, `3`, `5`, `6`, `9`.

Esos índices ayudan a detectar errores en el mapeo índice-bloque-offset.

### 4. ¿Qué sí demuestra una prueba pública sobre una estructura?

Una prueba pública demuestra que la estructura funciona correctamente para un conjunto finito de casos conocidos. Sirve para detectar errores evidentes de implementación, como:

- tamaños mal actualizados;
- elementos en orden incorrecto;
- errores de frontera;
- fallas en inserción o eliminación;
- errores simples de redimensionamiento.

### 5. ¿Qué no demuestra una prueba pública?

Una prueba pública no demuestra correctitud completa. No prueba todos los posibles tamaños, órdenes de operación ni casos extremos.

Tampoco demuestra por sí sola:

- que la complejidad sea la prometida;
- que no haya desperdicio espacial excesivo;
- que no existan fugas de memoria;
- que los invariantes se mantengan para cualquier secuencia de operaciones;
- que el código sea robusto ante todos los casos límite.

Por eso las pruebas son evidencia, no una demostración matemática.

### 6. En `resize_stress_week2.cpp`, ¿qué comportamiento intenta estresar?

El archivo de stress intenta forzar muchos crecimientos y posiblemente reducciones de capacidad. La idea es ejecutar suficientes inserciones y eliminaciones para que la estructura tenga que llamar varias veces a `resize()`, `expand()`, `grow()` o `shrink()`.

Lo que se busca verificar es que:

- los elementos no se pierdan durante una copia;
- el orden lógico se mantenga;
- `size` y `capacity` no se contradigan;
- la estructura siga estable después de muchas operaciones;
- las reducciones no eliminen elementos válidos;
- los casos cercanos a capacidad llena o casi vacía funcionen correctamente.

### 7. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes y complejidad?

Porque una prueba solo observa algunos ejemplos. En cambio, un invariante explica qué debe ser verdadero después de toda operación.

Por ejemplo, en `ArrayStack` un invariante básico es:

```text
0 <= size <= capacity
los elementos válidos están en a[0], a[1], ..., a[size - 1]
```

Si se puede explicar por qué cada operación conserva ese invariante, se tiene una defensa más general que una prueba puntual.

La complejidad también necesita argumento. Que una prueba termine rápido no demuestra que la operación sea `O(1)` amortizado o `O(n)`: para eso hay que contar copias, desplazamientos y redimensionamientos.

---

## Bloque 4 - Vector como puente entre teoría y código

### 1. ¿Qué papel cumplen `_size`, `_capacity` y `_elem`?

`_size` representa cuántos elementos válidos contiene el vector.

`_capacity` representa cuántas posiciones tiene reservadas el arreglo interno.

`_elem` es el puntero al bloque de memoria donde se guardan los elementos.

Juntos forman la representación básica del vector dinámico:

```cpp
T* _elem;          // arreglo interno
int _size;         // elementos usados
int _capacity;     // espacios reservados
```

El invariante principal es:

```text
0 <= _size <= _capacity
```

### 2. ¿Cuándo debe ejecutarse `expand()`?

`expand()` debe ejecutarse antes de insertar un nuevo elemento cuando ya no hay espacio libre, es decir, cuando:

```text
_size == _capacity
```

En ese caso se reserva un arreglo más grande, se copian los elementos existentes y se actualiza `_elem`.

La expansión no debe ocurrir en cada inserción, porque eso haría que insertar repetidamente fuera demasiado costoso.

### 3. ¿Por qué `insert(r, e)` necesita desplazar elementos?

Porque para insertar en la posición `r` hay que abrir un hueco sin destruir los elementos que ya están desde `r` hasta `_size - 1`.

El desplazamiento típico va de derecha a izquierda:

```cpp
for (int i = _size; i > r; --i) {
    _elem[i] = _elem[i - 1];
}
_elem[r] = e;
_size++;
```

Se recorre de derecha a izquierda para no sobrescribir valores que todavía deben copiarse.

El costo es `O(_size - r)`, porque se desplazan los elementos del sufijo.

### 4. Diferencia conceptual entre `remove(r)` y `remove(lo, hi)`

`remove(r)` elimina un solo elemento en la posición `r`.

`remove(lo, hi)` elimina un rango de elementos, normalmente desde `lo` hasta `hi - 1`.

Conceptualmente:

```text
remove(r)       elimina 1 elemento
remove(lo, hi)  elimina hi - lo elementos
```

Una implementación limpia puede hacer que `remove(r)` use internamente `remove(r, r + 1)`. Así se evita duplicar lógica.

### 5. ¿Qué evidencia de copia profunda aparece en la demo?

La evidencia de copia profunda aparece cuando se copia un vector y luego se modifica una de las copias sin afectar a la otra.

Por ejemplo:

```text
v1 = [1, 2, 3]
v2 = copia de v1
v2[0] = 99
```

Si la copia es profunda, el resultado debe ser:

```text
v1 = [1, 2, 3]
v2 = [99, 2, 3]
```

Eso demuestra que los dos vectores no comparten el mismo arreglo interno. Cada uno tiene su propio bloque de memoria.

### 6. ¿Por qué `traverse()` es una buena interfaz didáctica?

`traverse()` es didáctica porque muestra que la estructura puede aplicar una operación uniforme a todos sus elementos sin exponer directamente la representación interna.

Permite razonar así:

```text
para cada elemento válido:
    aplicar una acción
```

También refuerza que recorrer toda la estructura cuesta `O(n)`, porque se visita cada elemento una vez.

### 7. ¿Qué ventaja tiene implementar un vector propio antes de depender de `std::vector`?

Implementar un vector propio obliga a entender lo que `std::vector` oculta:

- reserva de memoria;
- diferencia entre `size` y `capacity`;
- expansión;
- copia profunda;
- destructor;
- desplazamientos;
- costo amortizado;
- errores de frontera.

Después de entender eso, usar `std::vector` es más seguro, porque se comprende qué costos e invariantes hay detrás de su interfaz.

---

## Bloque 5 - `RootishArrayStack`: espacio y mapeo

### 1. ¿Cómo se distribuyen los elementos entre bloques?

Los elementos se guardan en bloques de tamaños crecientes. Con bloques numerados desde `0`, la distribución es:

```text
bloque 0: capacidad 1
bloque 1: capacidad 2
bloque 2: capacidad 3
bloque 3: capacidad 4
...
bloque b: capacidad b + 1
```

Los elementos se colocan en orden lógico, llenando primero los bloques anteriores.

Ejemplo con 10 elementos:

```text
bloque 0: [0]
bloque 1: [1, 2]
bloque 2: [3, 4, 5]
bloque 3: [6, 7, 8, 9]
```

### 2. ¿Por qué con `r` bloques la capacidad total es `r(r+1)/2`?

Porque las capacidades de los bloques son:

```text
1, 2, 3, ..., r
```

La suma de los primeros `r` enteros positivos es:

```text
1 + 2 + 3 + ... + r = r(r + 1)/2
```

Esa fórmula da la capacidad total disponible con `r` bloques.

### 3. ¿Qué problema resuelve `i2b(i)`?

`i2b(i)` resuelve el problema de encontrar en qué bloque está el índice lógico `i`.

En un arreglo normal, `A[i]` se calcula con una sola dirección base. En `RootishArrayStack`, no hay un único bloque contiguo para todos los elementos. Por eso hay que traducir:

```text
índice lógico i -> bloque b -> offset dentro del bloque
```

Con bloques numerados desde `0`, el bloque `b` empieza en:

```text
b(b + 1)/2
```

Entonces, después de encontrar `b`, el offset se calcula como:

```text
offset = i - b(b + 1)/2
```

Una fórmula típica para el bloque es:

```text
b = ceil((-3 + sqrt(9 + 8i)) / 2)
```

Lo importante no es memorizar la fórmula, sino entender que viene de invertir una suma triangular.

### 4. ¿Qué información produce `locate(i)` en la versión explicada?

`locate(i)` produce la ubicación física del índice lógico `i`. Normalmente informa:

```text
bloque b
offset j
```

Es decir, transforma una pregunta lógica:

```text
¿dónde está el elemento i?
```

en una posición concreta:

```text
blocks[b][j]
```

Esto hace visible el mapeo que en la versión normal puede estar oculto dentro de `get`, `set`, `add` o `remove`.

### 5. ¿Qué se gana en espacio frente a `ArrayStack`?

Se gana una reducción del desperdicio espacial.

En un arreglo dinámico con duplicación, la capacidad puede ser casi el doble del tamaño lógico. Por eso el espacio libre puede ser `O(n)`.

En `RootishArrayStack`, si hay `r` bloques, el desperdicio está acotado por el tamaño del último bloque, que es `O(r)`. Como `r = O(√n)`, el desperdicio es `O(√n)`.

Esa es la ventaja central: menos espacio sobrante sin abandonar la idea de acceso por índice.

### 6. ¿Qué se conserva igual respecto a la interfaz?

Se conserva la interfaz de lista:

```cpp
get(i)
set(i, x)
add(i, x)
remove(i)
size()
```

El usuario puede seguir pensando en una secuencia lineal de elementos:

```text
0, 1, 2, 3, ..., n - 1
```

La diferencia está debajo de la interfaz: internamente ya no hay un solo arreglo, sino varios bloques.

### 7. ¿Qué parte parece más difícil de defender oralmente?

La parte más difícil de defender oralmente es el mapeo de índice lógico a bloque y offset.

La razón es que mezcla tres ideas:

1. bloques de tamaños crecientes;
2. números triangulares;
3. una fórmula con raíz cuadrada para invertir la suma.

El análisis espacial es más fácil una vez que se ve que la capacidad total es `r(r+1)/2`. El costo amortizado de `grow()` y `shrink()` también puede defenderse comparando el costo de crear o borrar un bloque con la cantidad de operaciones necesarias para volver a necesitar otro cambio.

---

## Bloque 6 - Refuerzo de lectura

### 1. ¿Qué aporta `operator[]` a la idea de vector?

`operator[]` permite usar el vector con notación de arreglo:

```cpp
v[i]
```

Esto refuerza la idea de acceso aleatorio por índice. Además, si devuelve una referencia, permite tanto leer como modificar:

```cpp
x = v[i];
v[i] = nuevo_valor;
```

Así, el vector se comporta externamente como un arreglo, aunque internamente tenga lógica de crecimiento dinámico.

### 2. ¿Qué supone `find(e)` sobre igualdad entre elementos?

`find(e)` supone que los elementos pueden compararse por igualdad. En C++, eso normalmente significa que existe una operación como:

```cpp
_elem[i] == e
```

La búsqueda es lineal: revisa elementos hasta encontrar uno igual o hasta terminar. Por eso su costo es `O(n)` en el peor caso.

### 3. ¿Qué muestra `traverse()` sobre procesamiento uniforme de toda la estructura?

`traverse()` muestra que todos los elementos válidos pueden procesarse con la misma acción, uno por uno.

La operación no depende de la capacidad, sino del tamaño lógico. Debe visitar:

```text
_elem[0], _elem[1], ..., _elem[_size - 1]
```

Por eso su costo es `O(n)`.

### 4. ¿Por qué esta lectura refuerza naturalmente `DengVector`?

Porque la lectura muestra cómo pasar de un arreglo básico a una estructura con interfaz de vector. Refuerza las mismas preguntas que aparecen en `DengVector`:

- cómo se almacena la secuencia;
- cómo se accede por índice;
- cómo se inserta;
- cómo se elimina;
- cuándo se expande;
- cómo se recorre;
- qué significa copiar correctamente una estructura con memoria dinámica.

La lectura funciona como puente entre la teoría del arreglo y la implementación de una estructura dinámica.

---

## Bloque 7 - Cierre comparativo

### ¿Qué cambia cuando pasamos de "usar un arreglo" a "diseñar una estructura dinámica basada en arreglo"?

Cuando usamos un arreglo, pensamos principalmente en posiciones: `A[0]`, `A[1]`, `A[2]`, etc. La longitud física ya está dada y el programador solo accede o modifica elementos.

Cuando diseñamos una estructura dinámica basada en arreglo, además de usar posiciones, debemos diseñar una representación. Esa representación incluye el arreglo interno, el tamaño lógico, la capacidad física y las reglas para crecer, reducir, insertar, eliminar y conservar el orden.

Desde el punto de vista de representación, `ArrayStack` y `FastArrayStack` usan un único bloque contiguo. En cambio, `RootishArrayStack` usa varios bloques de tamaños `1, 2, 3, ...`. Las tres estructuras ofrecen una interfaz de lista, pero no almacenan necesariamente los datos de la misma manera.

Desde el punto de vista de correctitud, ya no basta con que `A[i]` funcione. Hay que mantener invariantes después de cada operación. Por ejemplo:

```text
0 <= size <= capacity
los elementos válidos están en orden lógico
no se leen posiciones fuera del tamaño
las inserciones y eliminaciones preservan la secuencia esperada
```

En `RootishArrayStack`, además, debe cumplirse que el mapeo de índice a bloque y offset sea correcto.

Desde el punto de vista de costo amortizado, una estructura dinámica acepta que algunas operaciones sean caras ocasionalmente. Un `resize()` puede costar `O(n)`, pero si la capacidad se duplica, una secuencia de inserciones al final tiene costo total `O(n)`. Por eso cada inserción al final cuesta `O(1)` amortizado.

Desde el punto de vista del uso de espacio, el diseño también cambia. Un arreglo fijo no decide cómo crecer. Un arreglo dinámico sí debe decidir cuánta memoria extra reservar. Reservar demasiado desperdicia espacio; reservar muy poco obliga a copiar constantemente. `ArrayStack` puede desperdiciar `O(n)` espacio por la estrategia de duplicación. `RootishArrayStack` reduce ese desperdicio a `O(√n)` usando bloques crecientes.

La comparación final es:

- `ArrayStack` es la versión simple: un arreglo dinámico, acceso `O(1)`, inserción al final `O(1)` amortizado, inserciones y eliminaciones intermedias `O(n)`, y posible desperdicio espacial `O(n)`.
- `FastArrayStack` conserva la misma idea y los mismos costos asintóticos, pero mejora la implementación práctica de los desplazamientos usando copias más eficientes.
- `RootishArrayStack` cambia la representación para ahorrar espacio: mantiene la interfaz de lista, conserva acceso por índice mediante un cálculo de bloque y offset, y reduce el desperdicio espacial a `O(√n)`.

En conclusión, diseñar una estructura dinámica basada en arreglo significa controlar explícitamente la relación entre representación, invariantes, costo temporal y uso de memoria. Ese es el paso conceptual importante: dejar de ver el arreglo como una herramienta fija y empezar a verlo como una pieza dentro de una estructura con reglas de crecimiento y garantías de complejidad.

---

## Autoevaluación breve

### Qué podemos defender con seguridad

Podemos defender con seguridad:

- la diferencia entre `size` y `capacity`;
- por qué los arreglos permiten acceso `O(1)`;
- por qué insertar en medio requiere desplazamientos;
- por qué duplicar capacidad da costo amortizado `O(1)` al insertar al final;
- qué mejora `FastArrayStack`;
- por qué `RootishArrayStack` reduce desperdicio espacial.

### Qué todavía confundimos

Lo más fácil de confundir es:

- la fórmula exacta de `i2b(i)`;
- los límites entre bloques en `RootishArrayStack`;
- cuándo conviene ejecutar `shrink()`;
- la diferencia entre costo peor caso y costo amortizado.

### Qué evidencia usaríamos en una sustentación

Usaríamos tres tipos de evidencia:

1. las salidas de las demos para mostrar comportamiento observable;
2. las pruebas públicas y de stress para mostrar que varias secuencias funcionan;
3. los invariantes y argumentos de complejidad para justificar que el diseño funciona más allá de los ejemplos probados.

Una defensa sólida debería combinar las tres: ejecución, explicación de representación y análisis de costo.
