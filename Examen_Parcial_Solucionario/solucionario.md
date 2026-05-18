# Solucionario — CC232 Parcial 1, Versión B


## Pregunta 1 — `CursorBuffer` como ADT

Se tiene el ADT:

```cpp
class CursorBuffer {
public:
    void insert(char c);   // inserta en la posición del cursor
    char erase();          // elimina el carácter bajo el cursor
    void moveLeft();
    void moveRight();
    char current() const;
    int size() const;
};
```

Se proponen dos representaciones:

- **A:** arreglo dinámico con índice de cursor.
- **B:** lista doblemente enlazada con nodo centinela y puntero al nodo del cursor.

---

### a) ¿Qué especifica el ADT y qué queda abierto a la implementación?

El **ADT `CursorBuffer`** especifica qué operaciones están disponibles y cuál debe ser su efecto observable:

- `insert(c)`: insertar un carácter en la posición del cursor.
- `erase()`: eliminar el carácter bajo el cursor y devolverlo.
- `moveLeft()`: mover el cursor una posición a la izquierda.
- `moveRight()`: mover el cursor una posición a la derecha.
- `current()`: consultar el carácter bajo el cursor.
- `size()`: devolver el número de caracteres almacenados.

El ADT no debería depender de cómo se almacenan internamente los datos. Por lo tanto, queda abierto a la implementación:

- si los caracteres se guardan en memoria contigua o enlazada;
- si se usa un índice de cursor o un puntero a nodo;
- cómo se maneja la capacidad interna;
- cómo se hacen los desplazamientos o relinkeos;
- qué representación concreta tiene el cursor;
- cómo se tratan exactamente los casos borde si el enunciado no los fija.

Un punto importante: el ADT debería dejar claras las precondiciones de operaciones como `erase()` y `current()`. Por ejemplo, si el buffer está vacío o si el cursor está al final, `current()` podría ser inválido. Si eso no se especifica, la implementación debe documentarlo.

---

### b) Costos de operaciones para A y B

#### Representación A: arreglo dinámico con índice de cursor

Supongamos que el arreglo almacena los caracteres en:

```text
_elem[0], _elem[1], ..., _elem[_size - 1]
```

y el cursor es un índice `cur`.

| Operación | Costo | Justificación |
|---|---:|---|
| `insert(c)` | `O(n)` peor caso | Para insertar en la posición `cur`, los elementos desde `cur` hasta `_size - 1` deben desplazarse una posición a la derecha. Si además no hay capacidad, hay `resize` y copia. |
| `erase()` | `O(n)` peor caso | Para eliminar el carácter bajo el cursor, los elementos posteriores deben desplazarse una posición a la izquierda. |
| `moveLeft()` | `O(1)` | Solo decrementa el índice del cursor si no está al inicio. |
| `moveRight()` | `O(1)` | Solo incrementa el índice del cursor si no está al final. |
| `current()` | `O(1)` | Acceso directo por índice al arreglo. |
| `size()` | `O(1)` | Devuelve la variable `_size`. |

Más precisamente:

```text
insert en cursor cur: O(_size - cur)
erase en cursor cur:  O(_size - cur - 1)
```

pero en el peor caso ambos son `O(n)`.

Si `insert` ocurre siempre al final, puede ser `O(1)` amortizado por el crecimiento dinámico. Pero como el ADT permite insertar en la posición del cursor, en general se requiere desplazar elementos.

#### Representación B: lista doblemente enlazada con nodo centinela

Supongamos un nodo centinela `dummy` y un puntero `cursor` al nodo actual o al centinela si el cursor representa el final.

| Operación | Costo | Justificación |
|---|---:|---|
| `insert(c)` | `O(1)` | Se crea un nodo y se relinkean punteros alrededor del cursor. No se desplazan datos. |
| `erase()` | `O(1)` | Se elimina el nodo del cursor actualizando `prev` y `next`. |
| `moveLeft()` | `O(1)` | Se mueve el puntero `cursor = cursor->prev`. |
| `moveRight()` | `O(1)` | Se mueve el puntero `cursor = cursor->next`. |
| `current()` | `O(1)` | Se lee el dato del nodo apuntado por el cursor. |
| `size()` | `O(1)` | Devuelve el contador de nodos reales. |

La lista doble es especialmente buena cuando las ediciones son locales alrededor del cursor.

---

### c) Dos invariantes de representación para cada alternativa

#### A: arreglo dinámico

Invariantes posibles:

1. **Tamaño y capacidad válidos**

```text
0 <= _size <= _capacity
```

2. **Cursor dentro del rango permitido**

Si el cursor puede estar entre caracteres:

```text
0 <= cur <= _size
```

Si `current()` requiere un carácter bajo el cursor:

```text
0 <= cur < _size
```

3. **Zona lógica contigua**

```text
Los caracteres válidos están exactamente en _elem[0.._size-1].
```

4. **Arreglo físico válido**

```text
_elem apunta a un bloque de memoria de longitud _capacity, si _capacity > 0.
```

#### B: lista doble con centinela

Invariantes posibles:

1. **Consistencia local de enlaces**

Para todo nodo real `x`:

```text
x->next->prev == x
x->prev->next == x
```

2. **Centinela correcto**

Si la lista está vacía:

```text
dummy.next == &dummy
dummy.prev == &dummy
```

Si no está vacía:

```text
dummy.next apunta al primer nodo real
dummy.prev apunta al último nodo real
```

3. **Cursor válido**

```text
cursor apunta a un nodo real o al centinela dummy, nunca a memoria liberada.
```

4. **Tamaño consistente**

```text
El número de nodos reales alcanzables desde dummy.next hasta volver a dummy es igual a _size.
```

---

### d) Elección para muchas ediciones locales y pocas consultas por índice

Elegiría la **lista doblemente enlazada con nodo centinela**.

Justificación:

- `insert` cerca del cursor cuesta `O(1)`.
- `erase` bajo el cursor cuesta `O(1)`.
- `moveLeft` y `moveRight` cuestan `O(1)`.
- No se desplazan caracteres al editar.
- Si hay pocas consultas por índice, la ventaja del arreglo dinámico —acceso aleatorio `O(1)`— no es decisiva.

El arreglo dinámico tiene mejor localidad de memoria y acceso directo por índice, pero para muchas ediciones locales alrededor del cursor sufre desplazamientos `O(n)`.

---

### e) Caso borde que puede romper cada implementación

#### A: arreglo dinámico

Casos peligrosos:

- `insert` cuando `_size == _capacity` sin hacer `resize`.
- `erase()` o `current()` cuando el buffer está vacío.
- `current()` cuando `cur == _size`, si el cursor está al final.
- `moveLeft()` con `cur == 0`.
- `moveRight()` cuando el cursor ya está al final.
- insertar en índice inválido.

Ejemplo:

```text
_size = 5, _capacity = 5
insert('x')
```

Si no se expande la capacidad antes de escribir, se accede fuera del arreglo.

#### B: lista doble

Casos peligrosos:

- lista vacía: `dummy.next == dummy`, `dummy.prev == dummy`;
- `erase()` cuando `cursor == dummy`;
- `current()` cuando `cursor == dummy`;
- olvidar actualizar uno de los cuatro enlaces al insertar o eliminar;
- dejar el cursor apuntando a un nodo liberado después de `erase()`.

Ejemplo:

```text
erase() sobre el único nodo real.
```

Después de borrar, debe cumplirse:

```text
dummy.next == &dummy
dummy.prev == &dummy
cursor == &dummy
```

o alguna política válida equivalente.

---

## Pregunta 2 — Algoritmo de Euclides

Código:

```cpp
int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
```

---

### a) Trace `gcd(252, 105)` mostrando `a`, `b` y `r`

| Iteración | `a` | `b` | `r = a % b` | Nuevo `a` | Nuevo `b` |
|---:|---:|---:|---:|---:|---:|
| 1 | 252 | 105 | 42 | 105 | 42 |
| 2 | 105 | 42 | 21 | 42 | 21 |
| 3 | 42 | 21 | 0 | 21 | 0 |

Cuando `b == 0`, termina y devuelve:

```text
gcd(252, 105) = 21
```

---

### b) Correctitud usando `gcd(a, b) = gcd(b, a mod b)`

El invariante del algoritmo es:

```text
gcd(a, b) se conserva en cada iteración.
```

En cada paso se calcula:

```text
r = a mod b
```

y luego se reemplaza:

```text
(a, b) <- (b, r)
```

Por la propiedad fundamental del algoritmo de Euclides:

```text
gcd(a, b) = gcd(b, a mod b)
```

entonces:

```text
gcd(a_original, b_original)
```

es igual al `gcd` del nuevo par después de cada iteración.

Al terminar:

```text
b == 0
```

y se sabe que:

```text
gcd(a, 0) = |a|
```

Si trabajamos con entradas no negativas, el algoritmo devuelve `a`, que es el máximo común divisor buscado.

Por lo tanto, el algoritmo es correcto porque conserva el valor buscado en cada iteración y al final lo deja explícitamente en `a`.

---

### c) Terminación

Suponiendo `a >= 0`, `b > 0`, en cada iteración se cumple:

```text
0 <= a mod b < b
```

Por lo tanto, el nuevo valor de `b` es estrictamente menor que el anterior:

```text
b_nuevo = a mod b < b
```

Así, `b` forma una secuencia decreciente de enteros no negativos:

```text
b > r1 > r2 > ... >= 0
```

No puede decrecer indefinidamente. Eventualmente llega a `0`, y el ciclo termina.

---

### d) Precondiciones razonables

Para evitar ambigüedades con negativos o con ambos argumentos cero, se puede exigir:

```text
a >= 0
b >= 0
a y b no son ambos cero
```

Si se quieren aceptar negativos, una política razonable es normalizar:

```cpp
a = abs(a);
b = abs(b);
```

antes del algoritmo.

El caso:

```text
gcd(0, 0)
```

normalmente se considera indefinido, porque todo entero divide a 0 y no hay máximo divisor positivo único.

Casos válidos:

```text
gcd(a, 0) = a, si a > 0
gcd(0, b) = b, si b > 0
```

---

### e) Comparación con probar divisores desde `min(a,b)` hacia abajo

Algoritmo alternativo:

```cpp
int gcdSlow(int a, int b) {
    int m = min(a, b);
    for (int d = m; d >= 1; --d) {
        if (a % d == 0 && b % d == 0) {
            return d;
        }
    }
    return 1;
}
```

#### Costo

En el peor caso puede probar todos los valores:

```text
min(a,b), min(a,b)-1, ..., 1
```

Por lo tanto:

```text
Tiempo: O(min(a,b))
Espacio: O(1)
```

El algoritmo de Euclides, en cambio, reduce rápidamente el segundo argumento mediante el módulo. Su número de iteraciones es logarítmico en el tamaño de los valores:

```text
Tiempo: O(log min(a,b))
Espacio: O(1)
```

#### Por qué pruebas pequeñas no demuestran eficiencia

Probar con números pequeños como:

```text
gcd(12, 8)
gcd(20, 15)
```

puede hacer que ambos algoritmos parezcan rápidos. Pero eso no muestra cómo crecen cuando la entrada aumenta.

El análisis asintótico sí muestra la diferencia:

```text
gcdSlow:  crecimiento lineal en min(a,b)
Euclides: crecimiento logarítmico
```

Por eso, pasar pruebas pequeñas puede sugerir corrección para esos casos, pero no demuestra eficiencia.

---

## Pregunta 3 — `DengVector`

Un `DengVector` mantiene:

```text
_elem, _size, _capacity
```

En `insert(i, x)`:

- si hay capacidad, desplaza a la derecha los elementos en posiciones:

```text
i, i+1, ..., _size - 1
```

- si no hay capacidad, primero duplica la capacidad y copia los elementos al nuevo arreglo;
- luego desplaza y escribe `x`.

---

### a) Caso `_size = 5`, `_capacity = 6`

Hay una posición libre, por lo tanto no hay `resize`.

El índice válido para insertar debe cumplir:

```text
0 <= i <= _size
```

Entonces, con `_size = 5`, los índices válidos para insertar son:

```text
0, 1, 2, 3, 4, 5
```

#### `insert(0, x)`

Se desplazan los elementos:

```text
0, 1, 2, 3, 4
```

Cantidad de desplazamientos:

```text
5
```

Luego se escribe `x`.

Costo en escrituras si se cuenta también la escritura de `x`:

```text
5 desplazamientos + 1 escritura = 6
```

#### `insert(3, x)`

Se desplazan los elementos:

```text
3, 4
```

Cantidad de desplazamientos:

```text
2
```

Luego se escribe `x`.

Costo total si se cuenta escritura:

```text
2 desplazamientos + 1 escritura = 3
```

#### `insert(7, x)`

Es inválido porque:

```text
7 > _size = 5
```

Además, `_capacity = 6`, así que escribir en la posición 7 estaría fuera del arreglo físico.

Una implementación robusta debe rechazar la operación, lanzar excepción o reportar error antes de desplazar.

---

### b) Caso sin capacidad: copia al nuevo arreglo y luego desplazamiento

La foto parece indicar un caso donde debe considerarse copia al nuevo arreglo. Eso ocurre cuando:

```text
_size == _capacity
```

Por coherencia con el texto "considerando el costo de copiar al nuevo arreglo", se interpreta el caso como:

```text
_size = 6
_capacity = 6
```

Si literalmente fuese `_size = 6`, `_capacity = 7`, entonces todavía hay capacidad y no habría copia; se resolvería solo con desplazamientos.

#### Interpretación principal: `_size = 6`, `_capacity = 6`

Primero se duplica la capacidad y se copian los 6 elementos existentes:

```text
6 copias
```

Luego se desplaza según la posición de inserción.

#### `insert(0, x)`

- Copias por `resize`: `6`
- Desplazamientos: elementos `0..5`, es decir `6`
- Escritura de `x`: `1`

Costo total:

```text
6 + 6 + 1 = 13 escrituras/copiados
```

#### `insert(3, x)`

- Copias por `resize`: `6`
- Desplazamientos: elementos `3, 4, 5`, es decir `3`
- Escritura de `x`: `1`

Costo total:

```text
6 + 3 + 1 = 10 escrituras/copiados
```

#### `insert(7, x)`

Con `_size = 6`, el índice 7 sigue siendo inválido:

```text
7 > _size
```

Duplicar la capacidad no convierte a `7` en índice lógico válido. La validez se mide contra `_size`, no contra `_capacity`.

Si el ítem hubiera querido preguntar por `insert(6, x)`, que es insertar al final, entonces:

```text
6 copias + 0 desplazamientos + 1 escritura = 7
```

#### Si se toma literalmente `_size = 6`, `_capacity = 7`

No hay `resize`.

- `insert(0, x)`: `6` desplazamientos + `1` escritura.
- `insert(3, x)`: `3` desplazamientos + `1` escritura.
- `insert(7, x)`: inválido porque `7 > _size`.

---

### c) Por qué `pushBack` puede ser amortizado `O(1)`, pero `insert(0, x)` no

`pushBack(x)` inserta al final:

```text
i = _size
```

Normalmente no desplaza elementos. Si hay capacidad:

```text
costo O(1)
```

Si no hay capacidad, se duplica el arreglo y se copian `n` elementos:

```text
costo O(n)
```

Pero esos redimensionamientos no ocurren en cada operación. Si la capacidad se duplica, el costo de copias se distribuye sobre muchas inserciones.

Para `m` operaciones `pushBack`, el número total de copias por expansión es proporcional a `m`, por lo tanto:

```text
pushBack: O(1) amortizado
```

En cambio, `insert(0, x)` desplaza todos los elementos actuales hacia la derecha en cada operación:

```text
insert(0, x): O(n)
```

Si se hacen muchas inserciones al inicio, cada una vuelve a mover casi todo el contenido. Ese costo no desaparece con amortización:

```text
m inserciones al inicio: Θ(m^2)
```

Por eso `insert(0,x)` no es amortizado `O(1)` bajo esta representación.

---

### d) Invariante con `_size`, `_capacity` y posiciones válidas

Invariantes razonables:

```text
0 <= _size <= _capacity
```

```text
_elem apunta a un bloque de memoria de longitud _capacity, si _capacity > 0
```

```text
Los elementos lógicos válidos están en _elem[0.._size-1]
```

```text
Las posiciones _elem[_size.._capacity-1] existen físicamente, pero no forman parte de la secuencia lógica
```

Para operaciones:

```text
get(i), set(i,x), remove(i): 0 <= i < _size
insert(i,x): 0 <= i <= _size
```

Estos invariantes separan claramente:

```text
tamaño lógico = _size
capacidad física = _capacity
```

---

### e) Política de expand/shrink

Una política común:

#### Expandir

Cuando:

```text
_size == _capacity
```

duplicar:

```text
_capacity = max(1, 2 * _capacity)
```

#### Reducir

Cuando:

```text
_size <= _capacity / 4
```

reducir a la mitad:

```text
_capacity = max(1, _capacity / 2)
```

#### Por qué usar umbral de 1/4 para reducir

Si se reduce apenas cuando `_size == _capacity / 2`, puede aparecer oscilación:

```text
add -> expand
remove -> shrink
add -> expand
remove -> shrink
```

Usar expansión al llenarse y reducción al cuarto crea una zona de histéresis que evita redimensionamientos excesivos.

#### Memoria desperdiciada y copias

Con duplicación:

```text
_capacity < 2 * _size
```

poco después de crecer, salvo casos pequeños. Por lo tanto, la memoria desperdiciada queda acotada por un factor constante.

Con reducción al cuarto, se evita que la capacidad sea demasiado mayor al tamaño durante mucho tiempo.

Esta política mantiene:

```text
pushBack/popBack: O(1) amortizado
```

aunque una operación individual de `resize` cueste `O(n)`.

---

## Pregunta 4 — `ArrayQueue` circular

Una `ArrayQueue` circular usa un arreglo de longitud 10.

```text
a[(j + k) mod 10]
```

es el elemento lógico `k`.

Inicialmente:

```text
j = 7
n = 5
contenido lógico = [4, 8, 15, 16, 23]
```

---

### a) Estado físico inicial

Para cada elemento lógico:

| k lógico | valor | posición física `(j+k) mod 10` |
|---:|---:|---:|
| 0 | 4 | 7 |
| 1 | 8 | 8 |
| 2 | 15 | 9 |
| 3 | 16 | 0 |
| 4 | 23 | 1 |

Estado físico:

| índice físico | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| valor | 16 | 23 | - | - | - | - | - | 4 | 8 | 15 |

---

### b) Operaciones

Convenciones:

- `add(x)` inserta al final lógico, en:

```text
(j + n) mod 10
```

- `remove()` elimina el primer elemento, en `j`, y luego:

```text
j = (j + 1) mod 10
n = n - 1
```

#### Estado inicial

```text
j = 7
n = 5
lógico = [4, 8, 15, 16, 23]
ocupadas = {7, 8, 9, 0, 1}
```

#### 1. `add(42)`

Posición:

```text
(j+n) mod 10 = (7+5) mod 10 = 2
```

Resultado:

```text
j = 7
n = 6
lógico = [4, 8, 15, 16, 23, 42]
ocupadas = {7, 8, 9, 0, 1, 2}
```

#### 2. `remove()`

Se elimina el elemento en `j = 7`, que es `4`.

```text
j = 8
n = 5
lógico = [8, 15, 16, 23, 42]
ocupadas = {8, 9, 0, 1, 2}
```

#### 3. `add(7)`

Posición:

```text
(j+n) mod 10 = (8+5) mod 10 = 3
```

Resultado:

```text
j = 8
n = 6
lógico = [8, 15, 16, 23, 42, 7]
ocupadas = {8, 9, 0, 1, 2, 3}
```

#### 4. `add(9)`

Posición:

```text
(j+n) mod 10 = (8+6) mod 10 = 4
```

Resultado:

```text
j = 8
n = 7
lógico = [8, 15, 16, 23, 42, 7, 9]
ocupadas = {8, 9, 0, 1, 2, 3, 4}
```

#### 5. `remove()`

Se elimina el elemento en `j = 8`, que es `8`.

Resultado final:

```text
j = 9
n = 6
lógico = [15, 16, 23, 42, 7, 9]
ocupadas = {9, 0, 1, 2, 3, 4}
```

Estado físico final:

| índice físico | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| valor lógico vigente | 16 | 23 | 42 | 7 | 9 | - | - | - | - | 15 |

---

### c) Por qué el módulo es necesario

El módulo permite que el arreglo se use como si fuera circular.

Si `j = 7` y se tienen elementos en posiciones lógicas sucesivas, después de la posición física 9 se debe volver a la posición 0.

Por ejemplo:

```text
(j + 3) mod 10 = (7 + 3) mod 10 = 0
```

Si se usara simplemente:

```text
j + k
```

entonces:

```text
7 + 3 = 10
```

pero el índice 10 no existe en un arreglo de longitud 10, cuyos índices válidos son:

```text
0..9
```

El error sería acceso fuera de rango.

---

### d) Comparación con una cola implementada usando `ArrayStack` que elimina en posición 0

#### `ArrayQueue` circular

- `add(x)` al final: `O(1)` amortizado.
- `remove()` al inicio: `O(1)`.
- No desplaza todos los elementos.
- Solo mueve el índice `j`.

#### Cola con `ArrayStack` que elimina en posición 0

Si se almacena la cola en un arreglo normal y se elimina siempre en índice 0, después de cada eliminación se deben desplazar todos los elementos restantes a la izquierda.

Costo:

```text
remove(): O(n)
```

`add(x)` al final puede ser `O(1)` amortizado, pero las eliminaciones son costosas.

Conclusión:

```text
ArrayQueue circular es mejor para una cola FIFO porque evita desplazamientos.
```

---

### e) `DualArrayDeque`

Un `DualArrayDeque` representa una secuencia con dos arreglos dinámicos:

```text
front
back
```

La parte frontal se guarda normalmente en orden invertido para que agregar o eliminar al inicio sea eficiente. La parte posterior se guarda en orden normal.

Idea:

```text
front contiene la primera mitad
back contiene la segunda mitad
```

Permite operaciones en ambos extremos:

```text
addFirst, removeFirst, addLast, removeLast
```

con costo amortizado `O(1)`.

#### Por qué necesita rebalanceo

Si un lado crece demasiado y el otro queda casi vacío, algunas operaciones o el uso de memoria se vuelven desbalanceados.

Por eso, periódicamente se redistribuyen los elementos para que ambos lados tengan tamaños comparables.

Propiedad que debe mantener el rebalanceo:

```text
front.size() y back.size() deben estar dentro de un factor constante.
```

Una forma típica:

```text
front.size() <= 3 * back.size() + 1
back.size() <= 3 * front.size() + 1
```

o equivalentemente, para `n` suficientemente grande:

```text
cada lado contiene una fracción constante de n.
```

Esto garantiza que el costo de reequilibrar se amortice y que las operaciones de doble extremo sean eficientes.

---

## Pregunta 5 — `DLList<T>` con centinela

Una `DLList<T>` usa un nodo centinela `dummy`.

```text
dummy.next apunta al primer nodo real
dummy.prev apunta al último nodo real
```

Si la lista está vacía:

```text
dummy.next == dummy
dummy.prev == dummy
```

---

### a) Pseudocódigo de `addBefore(Node* w, T x)`

La operación inserta un nuevo nodo antes del nodo `w`.

```cpp
Node* addBefore(Node* w, T x) {
    Node* u = new Node;
    u->x = x;

    u->prev = w->prev;
    u->next = w;

    w->prev->next = u;
    w->prev = u;

    ++n;
    return u;
}
```

Orden de enlaces:

1. El nuevo nodo `u` apunta a su predecesor:

```text
u->prev = w->prev
```

2. El nuevo nodo `u` apunta a su sucesor:

```text
u->next = w
```

3. El antiguo predecesor ahora apunta a `u`:

```text
w->prev->next = u
```

4. `w` reconoce a `u` como nuevo predecesor:

```text
w->prev = u
```

---

### b) Por qué el centinela elimina casos especiales

Sin centinela, insertar al inicio o al final requiere tratar casos separados:

```text
si la lista está vacía
si se inserta antes del primer nodo
si se inserta después del último nodo
```

Con centinela, siempre existe un nodo antes y un nodo después desde el punto de vista de la operación.

Ejemplos:

- Insertar al inicio equivale a:

```cpp
addBefore(dummy.next, x);
```

- Insertar al final equivale a:

```cpp
addBefore(&dummy, x);
```

Incluso si la lista está vacía:

```text
dummy.next == dummy
dummy.prev == dummy
```

la operación sigue funcionando porque `dummy` actúa como predecesor y sucesor ficticio.

---

### c) Por qué `getNode(i)` puede implementarse en `O(1 + min{i, n-i})`

En una lista doblemente enlazada se puede recorrer desde ambos extremos.

Si se quiere obtener el nodo en índice `i`:

- Si `i < n/2`, conviene empezar desde el inicio:

```text
dummy.next
```

y avanzar `i` veces.

Costo:

```text
O(1 + i)
```

- Si `i >= n/2`, conviene empezar desde el final:

```text
dummy.prev
```

y retroceder `n - 1 - i` veces.

Costo:

```text
O(1 + (n - 1 - i))
```

Asintóticamente:

```text
O(1 + min{i, n - i})
```

El `+1` cubre los casos donde `i = 0` o `i` está muy cerca del final, para que el costo mínimo siga siendo constante.

---

### d) Diseñe `rotate(r)` que rota la lista `r` posiciones a la derecha sin mover datos elemento por elemento

Rotar a la derecha `r` posiciones significa que los últimos `r` nodos pasan al inicio.

Ejemplo:

```text
[1, 2, 3, 4, 5], r = 2
```

resultado:

```text
[4, 5, 1, 2, 3]
```

No se deben copiar datos. Solo se cambian enlaces.

#### Pseudocódigo

```cpp
void rotate(int r) {
    if (n <= 1) return;

    r = r % n;
    if (r < 0) r += n;
    if (r == 0) return;

    // Nuevo primer nodo: índice n - r
    Node* newFirst = getNode(n - r);
    Node* newLast = newFirst->prev;

    Node* oldFirst = dummy.next;
    Node* oldLast = dummy.prev;

    // Conectar el antiguo final con el antiguo inicio
    oldLast->next = oldFirst;
    oldFirst->prev = oldLast;

    // Colocar nuevo primer y nuevo último respecto al centinela
    dummy.next = newFirst;
    newFirst->prev = &dummy;

    dummy.prev = newLast;
    newLast->next = &dummy;
}
```

#### Costo

El costo está dominado por encontrar `newFirst`:

```text
getNode(n-r)
```

Por lo tanto:

```text
O(1 + min{n-r, r})
```

Los cambios de enlaces son `O(1)`.

---

### e) Dos invariantes estructurales para detectar errores de punteros

#### Invariante 1: enlaces bidireccionales consistentes

Para cada nodo `x` alcanzable:

```text
x->next->prev == x
x->prev->next == x
```

Esto detecta errores donde se actualizó `next` pero no `prev`, o viceversa.

#### Invariante 2: recorrido completo coincide con `n`

Al recorrer hacia adelante desde `dummy.next` hasta volver a `dummy`, se deben visitar exactamente `n` nodos reales.

Al recorrer hacia atrás desde `dummy.prev` hasta volver a `dummy`, también se deben visitar exactamente `n` nodos reales.

Además, ambos recorridos deben terminar en el centinela, no en `nullptr`.

Esto detecta:

- ciclos incorrectos;
- nodos desconectados;
- tamaño inconsistente;
- enlaces rotos;
- pérdida de nodos.

---

## Pregunta 6 — Balanceo de paréntesis, corchetes y llaves

Se desea probar una implementación:

```cpp
bool isBalanced(string s)
```

que acepta:

```text
(), [], {}
```

Debe devolver `true` si toda apertura se cierra en orden correcto.

---

### a) 12 casos de prueba con salida esperada

| Caso | Entrada | Esperado | Grupo |
|---:|---|---:|---|
| 1 | `""` | `true` | cadena vacía |
| 2 | `"()"` | `true` | par simple |
| 3 | `"[]{}()"` | `true` | pares consecutivos |
| 4 | `"({[]})"` | `true` | anidamiento correcto |
| 5 | `"{[()]}"` | `true` | anidamiento correcto |
| 6 | `"(([]){})"` | `true` | anidamiento mixto correcto |
| 7 | `"(]"` | `false` | tipo incorrecto |
| 8 | `"([)]"` | `false` | cruce incorrecto |
| 9 | `")("` | `false` | cierre sin apertura previa |
| 10 | `"]"` | `false` | cierre sin apertura |
| 11 | `"((("` | `false` | aperturas sin cierre |
| 12 | `"({[]}"` | `false` | falta cierre exterior |

---

### b) Qué error detecta cada grupo

- **Cadena vacía:** verifica que no se exija al menos un carácter. Una cadena vacía está balanceada.
- **Casos correctos simples:** verifican emparejamiento básico.
- **Casos correctos anidados:** verifican disciplina LIFO: lo último abierto debe cerrarse primero.
- **Tipo incorrecto:** detecta implementaciones que solo cuentan cantidades, pero no tipos.
- **Cruce incorrecto:** detecta implementaciones que no respetan el orden de cierre.
- **Cierre sin apertura:** detecta si el algoritmo intenta desapilar cuando la pila está vacía.
- **Apertura sin cierre:** detecta si al final quedaron aperturas pendientes en la pila.

---

### c) ADT adecuado

El ADT adecuado es una **pila** (`Stack`).

Justificación:

Cuando aparece un símbolo de apertura, todavía no sabemos cuándo se cerrará. Pero si aparece un cierre, debe corresponder al símbolo de apertura más reciente que aún no ha sido cerrado.

Eso es exactamente la política:

```text
LIFO: Last In, First Out
```

Algoritmo:

```cpp
bool isBalanced(string s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false;

            char top = st.top();
            st.pop();

            if (c == ')' && top != '(') return false;
            if (c == ']' && top != '[') return false;
            if (c == '}' && top != '{') return false;
        }
    }

    return st.empty();
}
```

Invariante:

```text
Después de procesar un prefijo de la cadena,
la pila contiene exactamente las aperturas no cerradas de ese prefijo,
en orden desde la más antigua hasta la más reciente.
```

---

### d) Complejidad temporal y espacial

Sea:

```text
n = longitud de s
```

Cada carácter se procesa una sola vez.

Cada apertura se apila una vez y cada cierre desapila a lo sumo una vez.

Por lo tanto:

```text
Tiempo: O(n)
```

En el peor caso, todos los caracteres son aperturas:

```text
"(((((((("
```

La pila puede almacenar `n` elementos.

```text
Espacio: O(n)
```

---

## Pregunta 7 — Mínimo de ventana deslizante usando deque

Se recibe un flujo de enteros y se desea responder, para cada posición, el mínimo de los últimos `k` elementos procesados.

Secuencia para traza:

```text
[5, 2, 4, 1, 3, 0, 6]
```

con:

```text
k = 3
```

---

### a) Entrada, salida y precondiciones

#### Entrada

- Un flujo o arreglo de enteros:

```text
A[0..n-1]
```

- Un entero `k`.

#### Precondiciones

```text
k >= 1
```

Si se desea producir solo ventanas completas:

```text
k <= n
```

Si se acepta responder desde el primer elemento, entonces para las primeras posiciones se toma la ventana parcial:

```text
A[max(0, i-k+1)..i]
```

#### Salida

Para cada posición `i`, se devuelve:

```text
min(A[max(0, i-k+1)..i])
```

Si se exigen solo ventanas completas, se empieza a emitir desde:

```text
i = k - 1
```

---

### b) Representación con cola/deque auxiliar

Usamos un `Deque` de candidatos a mínimo. Cada elemento del deque es:

```text
(índice, valor)
```

Algoritmo para cada nuevo elemento `A[i] = x`:

```cpp
while (!dq.empty() && dq.back().value >= x) {
    dq.pop_back();
}

dq.push_back({i, x});

while (!dq.empty() && dq.front().index <= i - k) {
    dq.pop_front();
}

minActual = dq.front().value;
```

La idea es mantener solo candidatos útiles. Si llega un valor `x` menor o igual que valores al final del deque, esos valores ya no podrán ser mínimos mientras `x` esté en la ventana, porque:

- son mayores o iguales que `x`;
- son más antiguos que `x`;
- saldrán de la ventana antes o al mismo tiempo que `x`.

---

### c) Invariantes de la estructura auxiliar

Después de procesar la posición `i`, el deque cumple:

1. **Índices crecientes**

```text
Los índices en el deque están en orden creciente de adelante hacia atrás.
```

2. **Valores crecientes**

Si se eliminan valores `>= x` al insertar, entonces:

```text
Los valores en el deque son estrictamente crecientes de adelante hacia atrás.
```

3. **Todos los índices están vivos**

```text
Para todo par (idx, val) en el deque:
idx > i - k
```

Es decir, todos pertenecen a la ventana actual.

4. **El frente es el mínimo**

```text
dq.front().value es el mínimo de la ventana actual.
```

5. **No hay candidatos dominados**

Si un elemento antiguo tiene valor mayor o igual que uno nuevo, se elimina porque nunca volverá a ser mínimo mientras el nuevo esté disponible.

---

### d) Traza para `[5, 2, 4, 1, 3, 0, 6]`, `k = 3`

Representamos el deque como:

```text
[(índice, valor), ...]
```

#### Respuesta por cada posición usando ventana parcial al inicio

| i | x | Operación principal | Deque final | Mínimo |
|---:|---:|---|---|---:|
| 0 | 5 | insertar 5 | `[(0,5)]` | 5 |
| 1 | 2 | quitar 5 por ser mayor que 2; insertar 2 | `[(1,2)]` | 2 |
| 2 | 4 | insertar 4 | `[(1,2),(2,4)]` | 2 |
| 3 | 1 | quitar 4 y 2; insertar 1 | `[(3,1)]` | 1 |
| 4 | 3 | insertar 3 | `[(3,1),(4,3)]` | 1 |
| 5 | 0 | quitar 3 y 1; insertar 0 | `[(5,0)]` | 0 |
| 6 | 6 | insertar 6 | `[(5,0),(6,6)]` | 0 |

Salida por cada posición:

```text
[5, 2, 2, 1, 1, 0, 0]
```

#### Si solo se reportan ventanas completas de tamaño 3

Ventanas:

```text
[5, 2, 4] -> 2
[2, 4, 1] -> 1
[4, 1, 3] -> 1
[1, 3, 0] -> 0
[3, 0, 6] -> 0
```

Salida:

```text
[2, 1, 1, 0, 0]
```

---

### e) Complejidad total y costo amortizado por elemento

Cada elemento:

- entra al deque una vez;
- puede salir por el frente una vez cuando vence;
- puede salir por atrás una vez si es dominado por un valor más pequeño.

Aunque una sola inserción puede eliminar varios elementos del final, cada elemento eliminado ya no vuelve a entrar.

Por lo tanto, en toda la secuencia:

```text
n inserciones
O(n) eliminaciones totales
```

Complejidad total:

```text
Tiempo: O(n)
Espacio: O(k)
```

Costo amortizado por elemento:

```text
O(1)
```

El peor caso de una operación individual puede ser `O(k)` si elimina muchos candidatos, pero amortizadamente cada elemento paga por su propia inserción y eliminación.

---

### f) Comparación con recalcular el mínimo recorriendo la ventana

Método ingenuo:

Para cada posición, recorrer los últimos `k` elementos y calcular el mínimo desde cero.

Costo por posición:

```text
O(k)
```

Costo total:

```text
O(nk)
```

Espacio extra:

```text
O(1)
```

Método con deque:

```text
Tiempo total: O(n)
Espacio: O(k)
```

La diferencia es importante cuando `k` es grande. El deque evita repetir trabajo manteniendo candidatos vivos al mínimo.

---

# Resumen de conceptos usados

| Concepto | Dónde aparece |
|---|---|
| ADT vs implementación | `CursorBuffer`, `DengVector`, `ArrayQueue`, `DLList` |
| Invariante estructural | arreglos dinámicos, listas dobles, deque monotónica |
| Complejidad por operación | todas las preguntas |
| Peor caso vs amortizado | `DengVector`, `ArrayQueue`, deque monotónica |
| Memoria contigua | arreglos dinámicos, `ArrayQueue` |
| Memoria enlazada | `DLList`, `CursorBuffer` con lista |
| `resize` y capacidad | `DengVector`, `ArrayQueue`, `DualArrayDeque` |
| Índices modulares | `ArrayQueue` circular |
| Nodo, punteros y relinkeo | `DLList`, `rotate`, `addBefore` |
| Parsing con stack | `isBalanced` |
| Ventana deslizante | mínimo de últimos `k` elementos |
| Deque monotónica | pregunta 7 |
| Correctitud observable | casos de prueba en pregunta 6 |
| Casos borde | todas las implementaciones |
