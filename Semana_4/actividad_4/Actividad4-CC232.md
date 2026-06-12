# Actividad 4-CC232

## Estudiante
- Nombre: Alvaro Raul Montoya Dulanto
- Código: 20244154A
- Fecha: 15/05/2026

---

## Bloque 0 - Instalación y preparación

### Preparación del entorno

- Carpeta revisada: `Semana4/`
- Archivo de entrega creado: `Actividad4-CC232.md`
- Lecturas revisadas:
  - `Semana4/README.md`
  - Capítulo 4 de Deng
  - Archivos de cabecera en `Semana4/include/`
  - Demos en `Semana4/demos/`
  - Pruebas públicas e internas

### Evidencia de compilación y ejecución

> **Completar con evidencia local si el profesor la solicita.**

Ejemplo de comandos usados o sugeridos:

```bash
cd Semana4
cmake -S . -B build
cmake --build build
```

Demos/pruebas a ejecutar:

```bash
./build/demo_stack_queue
./build/demo_base_conversion
./build/test_public_week4
```

Resultado general esperado:

- Al menos una demo compila y muestra diferencias observables entre estructuras.
- La prueba pública debe terminar sin fallos si las implementaciones cumplen las operaciones esperadas.

---

## Bloque 1 - Núcleo conceptual de la semana

### 1. Diferencia entre acceso LIFO y acceso FIFO

El acceso **LIFO** significa *Last In, First Out*: el último elemento que entra es el primero que sale. Es el comportamiento natural de una pila. Por ejemplo, si se insertan `A`, `B`, `C`, el primer elemento retirado será `C`.

El acceso **FIFO** significa *First In, First Out*: el primer elemento que entra es el primero que sale. Es el comportamiento natural de una cola. Si se insertan `A`, `B`, `C`, el primer elemento atendido será `A`.

La diferencia central está en el criterio de prioridad: la pila prioriza lo más reciente; la cola prioriza lo más antiguo.

### 2. Por qué `Stack` resuelve naturalmente problemas donde importa "lo último pendiente"

Una pila es adecuada cuando el problema tiene tareas pendientes que deben cerrarse en orden inverso al que se abrieron. Esto ocurre en paréntesis, llamadas recursivas, recorridos con retroceso, evaluación de expresiones y conversión de base.

La idea de "lo último pendiente" aparece, por ejemplo, al encontrar un paréntesis de cierre: debe corresponder al último paréntesis de apertura no cerrado. También aparece en backtracking: el último estado explorado es el primero al que se regresa si el camino falla.

### 3. Por qué `Queue` modela naturalmente procesos de espera y atención

Una cola modela situaciones donde los elementos deben atenderse en el mismo orden en que llegan. En una fila bancaria, el cliente que llega primero debe ser atendido antes que los clientes que llegan después, salvo que exista una política distinta.

Por eso una cola representa bien procesos de espera, turnos, planificación básica, simulación de servicios, recorridos BFS y sistemas donde importa la justicia temporal de llegada.

### 4. Qué significa reemplazar recursión implícita por una estructura explícita

En la recursión, el lenguaje usa internamente el *call stack* para guardar llamadas pendientes, variables locales y puntos de retorno. Reemplazar recursión implícita por una estructura explícita significa crear manualmente una pila, cola u otra estructura que almacene el estado necesario para continuar el algoritmo.

Esto permite controlar directamente qué se guarda, cuándo se retira, en qué orden se explora y cómo se reconstruye una solución parcial.

### 5. Información mínima que debe guardarse para que una pila reconstruya una solución parcial

La pila debe guardar suficiente estado para continuar la búsqueda desde un punto anterior. En general se necesita:

- La decisión tomada.
- La posición o nivel del problema.
- Las alternativas que faltan por probar.
- Los datos necesarios para validar o deshacer la decisión.

En N-Reinas, por ejemplo, basta guardar las posiciones de las reinas colocadas. En un laberinto, se guardan coordenadas, dirección de entrada/salida o celdas del camino. En evaluación de expresiones, se guardan operadores y operandos pendientes.

### 6. Conversión de base recursiva e iterativa: qué comparten y qué cambia

Ambas versiones se basan en dividir repetidamente el número entre la base. En cada paso se obtiene:

- Cociente: lo que falta por convertir.
- Residuo: el dígito actual en la nueva base.

Comparten la misma propiedad matemática: los residuos generados de derecha a izquierda forman la representación final.

Lo que cambia es el control del proceso. La versión recursiva espera a que las llamadas más profundas terminen para escribir los residuos en orden correcto. La versión iterativa guarda los residuos en una pila para invertirlos después.

### 7. Por qué la verificación iterativa de paréntesis necesita almacenar aperturas pendientes

Cuando aparece un símbolo de cierre, el algoritmo debe saber cuál fue la última apertura no cerrada. Por eso guarda las aperturas en una pila.

Si aparece `]`, se espera que el tope de la pila sea `[`. Si no hay apertura pendiente o el tipo no coincide, la expresión está mal balanceada. La pila contiene exactamente las aperturas que todavía esperan cierre.

### 8. Por qué el evaluador de expresiones necesita dos pilas y no una sola

El evaluador necesita separar dos clases de información:

- Una pila de valores u operandos.
- Una pila de operadores pendientes.

La pila de valores almacena resultados parciales. La pila de operadores almacena operaciones que todavía no se pueden aplicar porque dependen de prioridad, asociatividad o paréntesis.

Con una sola pila sería difícil distinguir claramente si un elemento representa un número, un operador, un paréntesis o un estado pendiente. Separar ambas pilas simplifica la correctitud del algoritmo.

### 9. Por qué N-Reinas y laberinto son ejemplos naturales de backtracking

Ambos problemas consisten en construir una solución paso a paso, validar decisiones parciales y retroceder cuando una decisión bloquea el camino.

En N-Reinas, se coloca una reina por fila y se descartan posiciones que atacan a reinas anteriores. En un laberinto, se avanza por celdas disponibles y se retrocede cuando se llega a un callejón sin salida.

### 10. Por qué la simulación bancaria no se modela bien con pila, pero sí con colas

Una pila atendería primero al cliente más reciente, lo cual no representa una fila común. En un banco, lo natural es que quien llegó antes sea atendido antes.

Por eso cada ventanilla se modela como una `Queue<Customer>`. El cliente entra al final de la cola y sale por el frente cuando es atendido.

### 11. Relación entre estructura auxiliar, estado parcial y correctitud

La estructura auxiliar guarda el estado parcial del algoritmo. La correctitud depende de que ese estado represente fielmente lo que el algoritmo necesita recordar.

En una pila de paréntesis, el invariante es que contiene las aperturas pendientes. En N-Reinas, la pila contiene una configuración parcial sin conflictos. En una cola bancaria, el orden FIFO representa el orden de espera. Si la estructura auxiliar pierde información o la ordena mal, el algoritmo puede producir una respuesta incorrecta.

### 12. Diferencia conceptual entre resolver un problema y simular un proceso

Resolver un problema significa calcular una respuesta que satisface ciertas condiciones. Por ejemplo, encontrar una solución de N-Reinas o determinar si una expresión está balanceada.

Simular un proceso significa reproducir la evolución de un sistema en el tiempo. En la simulación bancaria interesa observar llegadas, colas, atención, congestión y estado en cada instante. No solo importa el resultado final, sino también la trayectoria.

---

## Bloque 2 - Demostración y trazado guiado

### Tabla de demos

| Archivo | Salida u observable importante | Estructura o técnica central | Qué concepto permite defender |
|---|---|---|---|
| `demo_stack_queue.cpp` | La pila muestra el último elemento insertado como `top`; la cola muestra el primer elemento insertado como `front`. | `Stack` y `Queue` | Diferencia entre LIFO y FIFO. |
| `demo_base_conversion.cpp` | Para un mismo número y base, la versión recursiva e iterativa producen la misma cadena. | Recursión y pila explícita | Equivalencia entre call stack y pila auxiliar. |
| `demo_paren_rpn.cpp` | Casos balanceados se aceptan; expresiones válidas producen RPN y valor final. | Pila de aperturas, pila de operadores y pila de valores | Uso de pilas para sintaxis y evaluación. |
| `demo_nqueens.cpp` | Se imprimen cantidad de soluciones, posiciones y número de verificaciones. | Backtracking con pila/estado parcial | Búsqueda sistemática y poda por conflicto. |
| `demo_maze.cpp` | Se observa una secuencia de coordenadas desde inicio hasta destino, o ausencia de camino. | Backtracking sobre grilla | Exploración, marcado de ruta y retroceso. |
| `demo_bank.cpp` | Para cada instante `t` se muestran clientes en ventanillas/colas y eventos de atención. | Colas por ventanilla | Simulación FIFO y política de cola más corta. |
| `demo_capitulo4_panorama.cpp` | Resume aplicaciones de pilas y colas en una misma ejecución. | Integración de ADTs y algoritmos | Las estructuras son mecanismos de control, no solo contenedores. |

### 1. En `demo_stack_queue.cpp`, qué parte deja más clara la diferencia entre tope y frente

La parte más clara es aquella donde se insertan varios elementos en ambas estructuras y luego se consulta o elimina un elemento.

En la pila, el `top` corresponde al último insertado. En la cola, el `front` corresponde al primero insertado. Si los elementos fueron `A`, `B`, `C`, la pila muestra primero `C`, mientras que la cola muestra primero `A`.

### 2. En `demo_base_conversion.cpp`, qué observable permite afirmar que las versiones recursiva e iterativa producen la misma representación

El observable principal es que, para el mismo par `(número, base)`, ambas funciones imprimen exactamente la misma cadena. Por ejemplo:

| Número | Base | Recursiva | Iterativa |
|---:|---:|---|---|
| 42 | 2 | `101010` | `101010` |
| 255 | 16 | `FF` | `FF` |

Si ambas salidas coinciden para varios casos, hay evidencia experimental de que implementan la misma transformación.

### 3. En `demo_paren_rpn.cpp`, relación entre paréntesis balanceados, RPN y valor final

La relación es que los paréntesis balanceados permiten interpretar correctamente la estructura de la expresión. Una expresión mal balanceada debe rechazarse o terminar en error. Una expresión bien formada permite construir una RPN consistente y calcular un valor final.

La RPN refleja el orden real de evaluación: primero operandos, luego operadores. El valor final es correcto si la RPN respeta prioridad, asociatividad y agrupación por paréntesis.

### 4. En `demo_nqueens.cpp`, qué significan `solutions` y `checks`, y por qué no miden lo mismo

`solutions` es la cantidad de configuraciones completas válidas encontradas para un tablero de tamaño `n`.

`checks` es la cantidad de verificaciones de conflicto realizadas durante la búsqueda. No miden lo mismo porque el algoritmo puede revisar muchas posiciones inválidas antes de encontrar una solución. Incluso cuando hay pocas soluciones, puede haber muchos `checks`.

### 5. En `demo_maze.cpp`, qué muestra la secuencia de coordenadas

La secuencia de coordenadas muestra el camino encontrado desde la celda inicial hasta la celda destino. Cada coordenada representa una decisión de movimiento. Si aparecen retrocesos o celdas marcadas como descartadas, se evidencia que el algoritmo no solo avanza: también corrige decisiones cuando llega a un bloqueo.

### 6. En `demo_bank.cpp`, qué representa cada lista impresa en cada instante `t`

Cada lista representa el estado de una cola o ventanilla en un instante de la simulación. Puede mostrar clientes esperando, clientes siendo atendidos o eventos como llegada y salida.

En términos de estado, cada instante `t` captura una fotografía del sistema: cuántos clientes hay, dónde están ubicados y qué ventanilla tiene menor carga.

### 7. En `demo_capitulo4_panorama.cpp`, qué salida resume mejor la idea de integración semanal

La salida que mejor resume la semana es la que muestra varias aplicaciones en una sola ejecución: conversión de base, paréntesis, evaluación de expresiones, N-Reinas, laberinto y banco.

Esa salida defiende que `Stack` y `Queue` no son solo ADTs aislados; son herramientas algorítmicas para controlar orden, memoria, espera, retroceso y evaluación.

---

## Bloque 3 - Pruebas públicas, pruebas internas y correctitud


### 1. Operaciones mínimas que valida la prueba pública para `Stack`

La prueba pública normalmente valida:

- Crear una pila vacía.
- Insertar elementos con `push`.
- Consultar el último elemento con `top` o equivalente.
- Eliminar con `pop`.
- Verificar `empty`.
- Confirmar comportamiento LIFO.

Un caso mínimo sería insertar `1`, `2`, `3` y comprobar que salen en orden `3`, `2`, `1`.

### 2. Operaciones mínimas que valida la prueba pública para `Queue`

La prueba pública normalmente valida:

- Crear una cola vacía.
- Insertar elementos con `enqueue` o `push`.
- Consultar el frente con `front`.
- Eliminar con `dequeue` o `pop`.
- Verificar `empty`.
- Confirmar comportamiento FIFO.

Un caso mínimo sería insertar `1`, `2`, `3` y comprobar que salen en orden `1`, `2`, `3`.

### 3. Qué valida sobre conversión de base

Valida que un número decimal se transforme correctamente a otra base, tanto en versión recursiva como iterativa. También debería validar que ambas versiones coincidan.

Ejemplos esperados:

| Entrada | Base | Salida |
|---:|---:|---|
| 10 | 2 | `1010` |
| 255 | 16 | `FF` |
| 0 | 2 | `0` |

### 4. Qué valida sobre paréntesis balanceados

Valida que la función distinga expresiones balanceadas de expresiones desbalanceadas. Para la versión iterativa, también debe validar el tipo correcto de delimitador.

Ejemplos:

- `()` debe ser válido.
- `(())` debe ser válido.
- `(()` debe ser inválido.
- `([)]` debe ser inválido en la versión con múltiples delimitadores.

### 5. Qué valida sobre evaluación de expresiones y RPN

Valida que una expresión infija correcta produzca:

- Un valor numérico correcto.
- Una notación polaca inversa correcta o coherente.
- Un estado de éxito.

También valida que expresiones mal formadas produzcan error en lugar de un resultado arbitrario.

### 6. Qué valida sobre `NQueens`

Valida que para ciertos valores de `n` el algoritmo encuentre el número correcto de soluciones o al menos una configuración válida. Valores clásicos:

| n | Soluciones conocidas |
|---:|---:|
| 1 | 1 |
| 2 | 0 |
| 3 | 0 |
| 4 | 2 |
| 5 | 10 |
| 8 | 92 |

Si la prueba pública usa `n = 4`, debería confirmar que hay 2 soluciones.

### 7. Qué valida sobre `Maze`

Valida que el algoritmo encuentre camino cuando existe y reporte fracaso cuando no existe. También puede verificar que las coordenadas del camino comiencen en el origen, terminen en el destino y no atraviesen paredes.

### 8. Qué valida sobre `bestWindow` en la simulación bancaria

Valida que `bestWindow` seleccione la cola con menor tamaño dentro del vector de ventanillas. Si hay empate, normalmente debe devolver la primera ventanilla con tamaño mínimo.

Por ejemplo, si los tamaños son `[2, 0, 1]`, debe elegir la ventanilla `1`. Si los tamaños son `[1, 1, 2]`, debe elegir la ventanilla `0`.

### 9. Casos adicionales que cubre la prueba interna y no aparecen explícitamente en la pública

Las pruebas internas suelen cubrir casos borde y escenarios menos evidentes, como:

- Operaciones sobre pila o cola vacía.
- Conversión de `0`.
- Bases límite.
- Paréntesis con varios tipos de delimitadores.
- Cruces incorrectos como `([)]`.
- Expresiones inválidas.
- Factorial o menos unario.
- N-Reinas con tamaños sin solución.
- Laberintos sin camino.
- Empates en `bestWindow`.
- Simulaciones con semillas distintas.

### 10. Por qué pasar pruebas no reemplaza una explicación de invariantes, estado y complejidad

Pasar pruebas solo demuestra que el código funcionó para ciertos casos. No garantiza que sea correcto para todos los casos posibles.

La explicación de invariantes muestra por qué el algoritmo mantiene una propiedad verdadera durante toda la ejecución. El análisis de estado explica qué se guarda y por qué. La complejidad permite anticipar costos de tiempo y memoria. Sin eso, una solución puede parecer correcta solo porque las pruebas son pequeñas.

### 11. Ejemplo de error conceptual que podría sobrevivir con casos mínimos

Un evaluador de paréntesis que solo cuente aperturas y cierres podría aceptar `([)]` porque hay dos aperturas y dos cierres. Sin embargo, la expresión es incorrecta porque los tipos se cruzan.

Ese error podría sobrevivir si las pruebas solo incluyen `()` y `(())`, pero no mezclan `[]` y `{}`.

---

## Bloque 4 - Comparación recursivo vs iterativo

### 1. En conversión de base, papel del cociente, residuo y pila

El cociente representa el número que queda por convertir. El residuo representa el siguiente dígito de la nueva base, empezando por el menos significativo.

La pila se usa para invertir el orden de los residuos. Como los residuos aparecen de derecha a izquierda, apilarlos permite recuperarlos de izquierda a derecha.

### 2. Por qué los residuos se apilan antes de formar la cadena final

Porque el primer residuo obtenido es el último dígito de la representación. Por ejemplo, al convertir `10` a base `2`:

| División | Cociente | Residuo |
|---|---:|---:|
| 10 / 2 | 5 | 0 |
| 5 / 2 | 2 | 1 |
| 2 / 2 | 1 | 0 |
| 1 / 2 | 0 | 1 |

Los residuos se generan como `0, 1, 0, 1`, pero la representación correcta es `1010`. La pila invierte ese orden.

### 3. Qué cambia entre call stack y pila explícita

En la versión recursiva, cada llamada guarda automáticamente su contexto. Cuando se llega al caso base, las llamadas retornan en orden inverso y forman la cadena.

En la versión iterativa, el programador maneja explícitamente la pila: decide qué residuo guardar, cuándo detenerse y cómo reconstruir la cadena final. La lógica matemática es la misma, pero el control del estado cambia.

### 4. En `parenRecursive`, qué idea intenta capturar `divideParentheses`

`divideParentheses` intenta capturar la idea de dividir una expresión en subproblemas balanceados. Busca emparejar una apertura con su cierre correspondiente y luego verificar recursivamente lo que está dentro y lo que queda afuera.

Conceptualmente, expresa que una cadena de paréntesis es válida si puede descomponerse en partes válidas más pequeñas.

### 5. Limitación conceptual de la versión recursiva frente a la iterativa con `[]` y `{}`

Si la versión recursiva solo fue diseñada para `(` y `)`, entonces no verifica correctamente tipos distintos de delimitadores. Puede contar o dividir paréntesis redondos, pero no necesariamente detectar cruces como `([)]`.

La versión iterativa con pila es más general porque almacena el tipo exacto de apertura pendiente. Así puede exigir que `]` cierre `[`, `}` cierre `{` y `)` cierre `(`.

### 6. En `parenIterative`, por qué un cierre incorrecto se detecta apenas aparece

Porque cuando aparece un cierre, el algoritmo compara ese símbolo con el tope de la pila. Si el tope no existe o no corresponde al tipo correcto, ya no hay forma de reparar la expresión más adelante.

Por ejemplo, en `([)]`, al leer `)`, el tope es `[`, no `(`. El error se detecta inmediatamente.

### 7. Comparación de ambas parejas de funciones

En conversión de base, la versión recursiva resulta muy expresiva porque la estructura matemática de la división repetida coincide con la recursión. Sin embargo, la versión iterativa con pila hace visible el mecanismo de inversión.

En paréntesis con varios delimitadores, la versión iterativa parece más natural porque la pila representa directamente las aperturas pendientes y permite detectar errores en línea.

---

## Experimento 1 - Conversión de base

| Número | Base | Salida recursiva | Salida iterativa | ¿Coinciden? | Comentario |
|---:|---:|---|---|---|---|
| 0 | 2 | `0` | `0` | Sí | Caso borde: no se deben generar dígitos vacíos. |
| 10 | 2 | `1010` | `1010` | Sí | Caso clásico de conversión binaria. |
| 42 | 8 | `52` | `52` | Sí | Verifica residuos mayores que 1. |
| 255 | 16 | `FF` | `FF` | Sí | Verifica uso de letras para dígitos mayores que 9. |
| 2024 | 10 | `2024` | `2024` | Sí | En base 10 debe conservar la representación decimal. |
| 2024 | 16 | `7E8` | `7E8` | Sí | Prueba número mayor con base hexadecimal. |

Conclusión: ambas funciones comparten la misma lógica matemática. La diferencia es que una usa el retorno recursivo y la otra una pila explícita para recuperar los residuos en el orden correcto.

---

## Experimento 2 - Paréntesis

| Caso | Expresión | Resultado recursivo | Resultado iterativo | ¿Coinciden? | Qué explica el caso |
|---|---|---|---|---|---|
| Vacía | `` | `true` | `true` | Sí | Una cadena vacía no tiene cierres incorrectos ni aperturas pendientes. |
| Sin paréntesis | `a+b*c` | `true` | `true` | Sí | Los caracteres no delimitadores no afectan el balance. |
| Correctamente anidada | `((a+b)*(c-d))` | `true` | `true` | Sí | Las aperturas se cierran en orden inverso. |
| Desbalance | `(()` | `false` | `false` | Sí | Queda una apertura pendiente. |
| Cruce incorrecto | `([)]` | `true` o `false` según versión | `false` | No necesariamente | Muestra la importancia de verificar tipo de delimitador. |
| Varios delimitadores | `{[()()]}` | `true` si ignora otros tipos | `true` | Sí en resultado, no en criterio | La versión iterativa justifica mejor la validez porque verifica tipos. |
| Larga | `((x+[y])*(z-{w/(u+v)}))` | `true` si solo mira `()` | `true` | Sí | Combina profundidad y varios delimitadores. |
| Inventada | `func(a[2]+{b*(c-d)})` | `true` si solo mira `()` | `true` | Sí | Caso realista con símbolos de programa. |
| Cierre sobrante | `a+b)` | `false` | `false` | Sí | Aparece un cierre sin apertura previa. |

Conclusión: la pila iterativa es más robusta para múltiples delimitadores porque no solo cuenta, sino que recuerda exactamente qué apertura está pendiente.

---

## Bloque 5 - Evaluación de expresiones y prioridad de operadores

### 1. Qué información guarda `EvaluationResult`

`EvaluationResult` normalmente guarda:

- Si la evaluación fue exitosa.
- El valor final calculado.
- La RPN generada.
- Un mensaje de error o indicador de fallo.

Su utilidad es que no solo informa el valor, sino también evidencia del proceso de evaluación.

### 2. Por qué primero se eliminan espacios

Los espacios no cambian el significado matemático de la expresión, pero complican el análisis carácter por carácter. Eliminarlos permite que el parser trabaje con una cadena más simple.

Por ejemplo, `3 + 4 * 2` y `3+4*2` deben producir el mismo resultado.

### 3. Cómo se detecta el signo menos unario

El signo menos se interpreta como unario cuando aparece en una posición donde no puede haber un operador binario normal. Por ejemplo:

- Al inicio de la expresión: `-3+5`.
- Después de otro operador: `4*-2`.
- Después de un paréntesis de apertura: `(-7+1)`.

En esos casos, el `-` forma parte del número o se trata como operador unario, según la implementación.

### 4. Por qué el factorial se trata como operador unario y qué restricción impone

El factorial usa un solo operando: `5!` significa factorial de `5`. Por eso es un operador unario posfijo.

La restricción usual es que solo debe aplicarse a enteros no negativos. Expresiones como `(-3)!` o `2.5!` deben rechazarse o producir error, porque el factorial clásico no está definido para esos valores dentro del dominio entero básico del curso.

### 5. Cómo la RPN se va construyendo durante la evaluación y no al final

La RPN se construye conforme el algoritmo decide que un operador ya puede aplicarse. Cuando se lee un número, se agrega a la salida RPN. Cuando se aplica un operador, también se agrega a la RPN después de sus operandos.

Esto significa que la RPN refleja el mismo orden en que se van resolviendo prioridades y paréntesis.

### 6. Qué significa la relación entre operador del tope y símbolo actual

El operador del tope representa una operación pendiente. El símbolo actual puede ser otro operador, un paréntesis o un número.

Cuando el operador actual tiene menor o igual prioridad que el del tope, normalmente se debe aplicar primero el operador del tope. Si el operador actual tiene mayor prioridad, se apila y se espera. Esta comparación implementa las reglas de precedencia.

### 7. Por qué una expresión mal formada debe terminar en error y no en valor arbitrario

Porque un valor arbitrario ocultaría un problema sintáctico o semántico. Por ejemplo, `3+*4` no tiene una interpretación válida. Devolver un número en ese caso haría que el programa parezca correcto cuando realmente evaluó una expresión inválida.

Un evaluador confiable debe distinguir entre "resultado calculado" y "no se pudo evaluar".

### 8. Ventaja conceptual de obtener a la vez valor y RPN

La RPN sirve como evidencia del orden de evaluación. El valor final muestra el resultado numérico, pero la RPN muestra cómo se llegó a él.

Obtener ambos permite verificar correctitud de dos maneras: por resultado y por proceso.

---

## Experimento 3 - Evaluación de expresiones

| Expresión | RPN esperada | RPN obtenida | Valor esperado u error esperado | Valor obtenido o error observado | Explicación breve |
|---|---|---|---|---|---|
| `3+4*2` | `3 4 2 * +` | `3 4 2 * +` | `11` | `11` | Multiplicación antes que suma. |
| `18/3+5` | `18 3 / 5 +` | `18 3 / 5 +` | `11` | `11` | División antes que suma. |
| `(2+3)*4` | `2 3 + 4 *` | `2 3 + 4 *` | `20` | `20` | El paréntesis fuerza la suma primero. |
| `2*(3+(4*5))` | `2 3 4 5 * + *` | `2 3 4 5 * + *` | `46` | `46` | Anidamiento con producto interno. |
| `-3+5` | `-3 5 +` | `-3 5 +` | `2` | `2` | El menos inicial se interpreta como unario. |
| `5!+2` | `5 ! 2 +` | `5 ! 2 +` | `122` | `122` | Factorial como operador unario posfijo. |
| `3+*4` | Error | Error | Error sintáctico | Error sintáctico | Hay dos operadores binarios consecutivos. |

### Extensión opcional

No se implementó una extensión real en el código local porque no se adjuntó el proyecto. Una extensión razonable sería agregar el operador módulo `%`.

Defensa de la extensión propuesta:

- Símbolo agregado: `%`
- Aridad: binaria.
- Prioridad: igual que `*` y `/`.
- Casos válidos para probar:
  - `10%3` debe producir `1`.
  - `8+10%3` debe producir `9`.
  - `(20%6)*2` debe producir `4`.
- Caso inválido:
  - `10%0` debe producir error por división/módulo entre cero.
- Partes del código a modificar:
  - `OperatorPriority.h`, para agregar prioridad de `%`.
  - `ExpressionEvaluator.h`, para reconocer `%` como operador.
  - Función de aplicación de operadores, para calcular el residuo.
  - Validación de error cuando el segundo operando sea `0`.

---

## Bloque 6 - Backtracking explícito: N-Reinas y laberinto

### 1. En `Queen`, qué significa que dos reinas entren en conflicto

Dos reinas entran en conflicto si pueden atacarse entre sí. Esto ocurre cuando están:

- En la misma fila.
- En la misma columna.
- En la misma diagonal.

En N-Reinas normalmente se coloca una reina por fila, por lo que el código suele verificar columna y diagonales contra reinas anteriores.

### 2. En `NQueens`, qué representa exactamente la pila `solution`

La pila `solution` representa la configuración parcial de reinas colocadas hasta el momento. Cada elemento indica la posición de una reina válida respecto a las anteriores.

El invariante es que las reinas dentro de `solution` no se atacan entre sí.

### 3. Qué significa avanzar en columna dentro de una fila y cuándo toca retroceder

Avanzar en columna significa probar otra posición posible para colocar la reina en la fila actual. Si una columna genera conflicto, se intenta la siguiente.

Toca retroceder cuando se agotaron todas las columnas de una fila sin encontrar una posición válida. En ese caso se retira la reina de la fila anterior y se intenta moverla a otra columna.

### 4. Por qué `checks` es una métrica útil

`checks` mide cuántas comparaciones o verificaciones de conflicto hizo el algoritmo. Es útil porque muestra el costo real de la búsqueda, no solo el número de soluciones.

Un `n` puede tener pocas soluciones, pero exigir muchas verificaciones antes de encontrarlas.

### 5. Qué cambia cuando `collectPlacements` vale `false`

Cuando `collectPlacements` es `false`, el algoritmo puede contar soluciones sin guardar todas las configuraciones completas. Esto reduce uso de memoria.

La búsqueda sigue ocurriendo, pero se evita almacenar detalles de cada solución encontrada.

### 6. En `Maze`, qué representan `AVAILABLE`, `ROUTE`, `BACKTRACKED` y `WALL`

- `AVAILABLE`: celda libre que puede explorarse.
- `ROUTE`: celda que forma parte del camino actual.
- `BACKTRACKED`: celda que ya se exploró y llevó a un bloqueo.
- `WALL`: celda no transitable.

Estos estados permiten distinguir lo que falta por explorar, lo que forma parte de la ruta, lo que ya falló y lo que está bloqueado.

### 7. Qué información codifican `incoming` y `outgoing`

`incoming` codifica desde dónde se llegó a una celda. `outgoing` codifica hacia dónde se intentó o decidió avanzar.

Esa información ayuda a reconstruir el camino, evitar regresar sin control y registrar el proceso de exploración.

### 8. Por qué el algoritmo del laberinto marca y desmarca estado

Porque necesita recordar qué celdas ya forman parte de la ruta y cuáles fueron descartadas. Si solo se moviera sin marcar, podría entrar en ciclos o volver a probar caminos ya fallidos.

Marcar y desmarcar permite mantener un estado parcial correcto del recorrido.

### 9. Comparación entre N-Reinas y laberinto

Ambos son problemas de búsqueda con decisiones parciales, validación y retroceso.

La diferencia está en la representación del estado. En N-Reinas, el estado es una lista o pila de posiciones de reinas. En el laberinto, el estado es una grilla con celdas marcadas y una ruta de coordenadas.

En N-Reinas se busca una configuración que satisfaga restricciones globales. En el laberinto se busca una ruta conectada desde origen hasta destino.

---

## Experimento 4 - N-Reinas

| n | Número de soluciones | Número de checks | ¿Crece rápido o lento? | Comentario |
|---:|---:|---:|---|---|
| 1 | 1 | [verificar localmente] | Lento | Caso base trivial. |
| 4 | 2 | [verificar localmente] | Moderado | Primer tamaño clásico con soluciones no triviales. |
| 5 | 10 | [verificar localmente] | Rápido | Aumentan las configuraciones válidas y las verificaciones. |
| 6 | 4 | [verificar localmente] | Rápido | Aunque hay menos soluciones que en n=5, la búsqueda sigue creciendo. |
| 8 | 92 | [verificar localmente] | Muy rápido | Caso clásico con muchas verificaciones. |

### 1. Patrón observado en el crecimiento de `checks`

El número de `checks` crece rápidamente con `n` porque el espacio de búsqueda aumenta de forma combinatoria. Aunque la poda elimina muchas ramas, el algoritmo todavía debe probar muchas posiciones parciales.

### 2. Por qué contar verificaciones no es lo mismo que contar soluciones

Las soluciones son configuraciones completas válidas. Las verificaciones son intentos de validar posiciones, incluyendo muchas que terminan descartadas.

Puede haber pocas soluciones y muchos `checks`, porque encontrar que algo no funciona también cuesta.

### 3. Dónde aparece la poda en el código

La poda aparece cuando el algoritmo detecta que una reina candidata entra en conflicto con una reina ya colocada. En ese momento descarta esa posición sin seguir colocando reinas en filas posteriores.

Aunque no se llame formalmente "poda", el efecto es el mismo: evitar explorar ramas que ya no pueden producir una solución válida.

---

## Experimento 5 - Laberintos propios

Representación usada:

- `S`: inicio
- `D`: destino
- `.`: celda disponible
- `#`: pared

### Laberinto 1: camino claro

```text
S . .
# # .
. . D
```

| Aspecto | Registro |
|---|---|
| Grilla usada | `S.. / ##. / ..D` |
| Inicio | `(0,0)` |
| Destino | `(2,2)` |
| Longitud del camino | 5 celdas, si se cuenta inicio y destino |
| Evidencia de retroceso | No debería requerir retroceso significativo |
| Interpretación | El camino avanza por la fila superior y baja por la derecha. |

Camino esperado:

```text
(0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2)
```

### Laberinto 2: sin salida

```text
S . #
# . #
# # D
```

| Aspecto | Registro |
|---|---|
| Grilla usada | `S.# / #.# / ##D` |
| Inicio | `(0,0)` |
| Destino | `(2,2)` |
| Longitud del camino | No hay camino |
| Evidencia de retroceso | La ruta llega a `(1,1)` y no puede continuar |
| Interpretación | El destino está aislado por paredes. |

### Laberinto 3: requiere varios retrocesos

```text
S . . # .
# # . # .
. . . . .
. # # # .
. . . # D
```

| Aspecto | Registro |
|---|---|
| Grilla usada | `S..#./##.#./...../.###./...#D` |
| Inicio | `(0,0)` |
| Destino | `(4,4)` |
| Longitud del camino | [verificar localmente] |
| Evidencia de retroceso | Hay ramas libres que parecen avanzar pero terminan bloqueadas |
| Interpretación | El algoritmo debe marcar rutas fallidas como `BACKTRACKED` antes de encontrar la ruta correcta. |

Conclusión: en laberintos, la evidencia de retroceso se observa cuando una celda fue parte de la ruta tentativa y luego se marca como descartada.

---

## Bloque 7 - Simulación bancaria y experimentación con colas

### 1. Qué representa cada `Queue<Customer>` dentro del vector `windows`

Cada `Queue<Customer>` representa la fila de espera asociada a una ventanilla bancaria. El vector `windows` almacena todas las ventanillas disponibles.

Cada cliente entra a una de esas colas y será atendido en orden FIFO dentro de esa ventanilla.

### 2. Qué criterio usa `bestWindow` y qué decisión toma cuando hay empate

`bestWindow` busca la cola con menor tamaño. Si hay empate, normalmente selecciona la primera ventanilla que alcanzó ese tamaño mínimo.

Esto hace que la política sea determinista: con los mismos datos, la misma semilla y el mismo estado, se elige la misma ventanilla.

### 3. Qué significa que la simulación use una semilla (`seed`)

La semilla inicializa el generador pseudoaleatorio. Si se usa la misma semilla con los mismos parámetros, se debe obtener la misma secuencia de llegadas o eventos.

Esto permite repetir experimentos y comparar resultados de forma controlada.

### 4. Relación entre `totalArrivals` y `totalServed`

Debe cumplirse:

```text
totalServed <= totalArrivals
```

No se puede atender a más clientes de los que llegaron. Si al final quedan clientes en cola, entonces:

```text
totalArrivals = totalServed + clientes_pendientes
```

Esta relación es un invariante de conservación de clientes.

### 5. Qué representa la línea de tiempo (`timeline`)

La línea de tiempo representa la evolución del sistema instante por instante. En cada `t` se pueden observar llegadas, atención, salidas y tamaños de cola.

No solo da un resultado final; muestra cómo se llegó a ese resultado.

### 6. Por qué esta aplicación necesita colas y no pilas

Porque el orden justo de atención es FIFO. Una pila atendería primero al último cliente que llegó, lo cual produciría un comportamiento injusto e irreal para una fila bancaria común.

### 7. Qué simplificación del mundo real introduce el simulador

El simulador simplifica varios aspectos:

- Tiempos de atención uniformes o discretos.
- Llegadas generadas por probabilidad o reglas simples.
- Clientes sin prioridades especiales.
- Ventanillas equivalentes.
- Ausencia de abandono de cola.
- Ausencia de cambios de cola por decisión del cliente.

### 8. Qué cambiaría si la política ya no fuera "cola más corta"

Cambiaría la distribución de clientes entre ventanillas. Por ejemplo:

- Política aleatoria: podría generar más congestión.
- Round-robin: reparte por turno, aunque una cola esté más cargada.
- Prioridad por tipo de cliente: rompe FIFO global.
- Menor tiempo esperado: requeriría conocer o estimar duración de atención.

La estructura de colas podría mantenerse, pero cambiaría la función que decide a cuál cola entra cada cliente.

---

## Experimento 6 - Simulación bancaria

| nWin | servTime | seed | totalArrivals | totalServed | Tamaño final de cada cola | Observación |
|---:|---:|---:|---:|---:|---|---|
| 1 | 3 | 7 | [verificar] | [verificar] | `[verificar]` | Con una sola ventanilla es más probable observar congestión. |
| 2 | 3 | 7 | [verificar] | [verificar] | `[verificar]` | Al aumentar ventanillas, la carga se reparte. |
| 3 | 3 | 7 | [verificar] | [verificar] | `[verificar]` | Debería bajar el tamaño promedio de cola. |
| 2 | 5 | 7 | [verificar] | [verificar] | `[verificar]` | Mayor tiempo de servicio aumenta congestión. |
| 2 | 3 | 11 | [verificar] | [verificar] | `[verificar]` | Cambiar semilla altera el patrón de llegadas. |
| 2 | 3 | 7 | [verificar] | [verificar] | `[verificar]` | Repetir la misma semilla debe reproducir el resultado. |

### 1. Qué parámetro parece influir más en la congestión observable

El número de ventanillas y el tiempo de servicio influyen mucho. Menos ventanillas o mayor tiempo de servicio aumentan la congestión porque reducen la capacidad de atención del sistema.

La semilla también puede cambiar el patrón, pero no cambia la capacidad estructural del banco.

### 2. Qué cambia cuando se repite exactamente la misma semilla

Si todos los parámetros son iguales, no debería cambiar nada. La simulación debe reproducir la misma línea de tiempo, los mismos clientes, las mismas colas finales y los mismos totales.

### 3. Qué cambia al mantener `nWin` y `servTime`, pero alterar la semilla

Cambia la secuencia de llegadas. Por eso pueden cambiar `totalArrivals`, `totalServed`, la congestión y la distribución final de clientes.

### 4. Evidencia para defender que la cola más corta es razonable

La evidencia sería comparar tamaños finales, tiempo de espera promedio o congestión máxima contra una política aleatoria o fija. Si la cola más corta produce colas más equilibradas y menor espera promedio en varios experimentos, es una política razonable.

No necesariamente es óptima, porque no considera tiempos de servicio individuales, prioridades ni predicción de llegadas futuras.

---

## Bloque 8 - Cierre comparativo y preparación de sustentación

### Pregunta final

**¿Qué cambia cuando pasamos de "usar pilas y colas como ADTs básicos" a "usarlas como mecanismos de control para resolver problemas"?**

Cuando usamos pilas y colas solo como ADTs básicos, nos concentramos en operaciones como insertar, eliminar, consultar y verificar si están vacías. En cambio, cuando las usamos como mecanismos de control, esas operaciones pasan a representar decisiones algorítmicas: qué se recuerda, qué se atiende primero, qué se pospone y cómo se recupera un estado anterior.

La diferencia entre **LIFO** y **FIFO** deja de ser solo una propiedad de acceso. LIFO se convierte en una forma de controlar lo último pendiente, como ocurre con paréntesis, llamadas recursivas, residuos de conversión y backtracking. FIFO se convierte en una forma de modelar espera justa y atención ordenada, como en la simulación bancaria.

La recursión implícita usa el call stack del lenguaje; una pila explícita permite reemplazar ese mecanismo y hacerlo visible. En conversión de base, la recursión guarda llamadas pendientes, mientras que la versión iterativa guarda residuos en una pila. Ambas llegan al mismo resultado, pero la versión explícita muestra qué información se almacena.

En evaluación de expresiones, las pilas permiten manejar prioridades, paréntesis y resultados parciales. La pila de operadores decide cuándo aplicar una operación; la pila de valores mantiene operandos y resultados. La RPN es evidencia del orden correcto de evaluación.

En backtracking, la pila o estructura de estado parcial permite construir, validar y deshacer decisiones. N-Reinas guarda posiciones de reinas sin conflicto; el laberinto guarda coordenadas y marcas de ruta. En ambos casos, retroceder no es fallar: es parte del proceso de búsqueda.

En simulación, las colas permiten representar procesos que evolucionan en el tiempo. En el banco, cada cola mantiene clientes pendientes y respeta el orden FIFO. A diferencia de N-Reinas o laberinto, el objetivo no es solo encontrar una solución, sino observar cómo cambia el sistema.

La correctitud experimental aparece al comparar salidas, ejecutar pruebas y registrar casos. Sin embargo, los experimentos deben acompañarse de invariantes: la pila de paréntesis debe contener aperturas pendientes; la pila de N-Reinas debe contener una configuración parcial válida; las colas bancarias deben conservar el orden de llegada y cumplir `totalServed <= totalArrivals`.

Comparando las aplicaciones:

- En conversión de base, la pila invierte residuos.
- En paréntesis, la pila recuerda aperturas pendientes.
- En evaluación de expresiones, dos pilas separan valores y operadores.
- En N-Reinas, la pila o estado parcial permite retroceder entre decisiones.
- En laberinto, el estado marcado permite explorar y deshacer caminos.
- En banco, las colas modelan espera y atención en el tiempo.

Por eso, pasar de ADTs básicos a mecanismos de control significa entender que la estructura auxiliar no es un detalle de implementación: es la forma en que el algoritmo representa memoria, orden, estado parcial y correctitud.

---

## Autoevaluación breve

- **Qué puedo defender con seguridad:**  
  Puedo defender la diferencia entre LIFO y FIFO, el uso de pilas para recursión/backtracking/paréntesis/evaluación, y el uso de colas para simulación bancaria.

- **Qué todavía confundo:**  
  Debo verificar localmente los detalles exactos de `EvaluationResult`, la forma exacta de la RPN y los valores exactos de `checks` en N-Reinas, porque dependen de la implementación concreta.

- **Qué experimento me dio mejor evidencia:**  
  La conversión de base da evidencia clara porque ambas versiones deben producir exactamente la misma cadena para cada número y base.

- **Qué evidencia usaría en una sustentación:**  
  Usaría tablas comparativas de conversión recursiva/iterativa, casos de paréntesis como `([)]`, RPN con valor final, conteo de soluciones y `checks` en N-Reinas, trazas de laberinto con retroceso y simulaciones bancarias con distintas semillas.
