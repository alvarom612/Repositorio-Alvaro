## Actividad 1- CC232

### Integrantes
- MONTOYA DULANTO, Alvaro Raul
- ROMAN ZELA, Victor Ducante

#### Bloque 1

1. **Expliquen con sus palabras la diferencia entre problema, algoritmo, ADT e implementación.**
- Un problema describe qué se quiere resolver, es decir, la relación deseada entre entradas y salidas.  
- Un algoritmo es el método paso a paso para resolver ese problema.  
- Un ADT (Tipo Abstracto de Datos) define qué operaciones ofrece una estructura y qué significado tienen, sin comprometerse con una representación concreta.  
- Una implementación es la realización concreta de un algoritmo o de un ADT en código, usando una representación específica en memoria.

2. **En `bubble_sort.cpp`, expliquen qué observable conecta correctitud y costo.**
- El observable importante no es solo que el arreglo quede ordenado al final, sino también cuántas comparaciones, intercambios o pasadas se realizan durante el proceso.  
- La correctitud se observa en el resultado: la salida queda ordenada.  
- El costo se conecta con observables como el número de comparaciones entre elementos adyacentes y el número de recorridos del arreglo, porque esas operaciones reflejan el trabajo real del algoritmo.  

3. **En `power.cpp`, expliquen por qué `power` mejora la idea de una versión ingenua.**
Una versión ingenua de potencia multiplica la base por sí misma `n` veces, así que hace trabajo lineal en el exponente, por lo que la mejora típica en `power.cpp` es reutilizar resultados parciales, por ejemplo calculando primero una potencia más pequeña y luego combinándola. Si usa exponenciación por cuadrados, reduce el número de multiplicaciones a orden logarítmico en el exponente.  Es importante tener en cuenta que no hace falta repetir todas las multiplicaciones una por una si se puede “dividir el problema” y reaprovechar subresultados.

4. **En `fibonacci.cpp`, expliquen por qué una función puede ser correcta y aun así ser una mala elección práctica.**
Una función puede ser correcta porque devuelve el valor matemáticamente esperado, pero puede ser una mala elección si su costo crece demasiado rápido. Un ejemplo clásico es Fibonacci recursivo ingenuo: produce el resultado correcto, pero repite muchísimas llamadas sobre los mismos subproblemas.  
Entonces, aunque la correctitud esté bien, la implementación puede ser impráctica por tiempo excesivo, consumo de pila o mala escalabilidad.

5. **En `count_ones.cpp`, expliquen por qué el tamaño de entrada no siempre coincide con el valor numérico.**
Cuando la entrada es un número entero, el “tamaño” relevante para costo no suele ser su valor numérico, sino la longitud de su representación, por ejemplo la cantidad de bits.  
El número 1024 es mucho más grande que 10, pero el costo de muchos algoritmos sobre enteros depende del número de bits necesarios para representarlos, no del valor en sí.  Por lo tanto, decir “la entrada es `n`” puede ser engañoso: a veces el costo real depende de `log n` si el tamaño se mide en bits.

6. **En `demo_adt_secuencia.cpp`, expliquen por qué la misma interfaz puede convivir con representaciones distintas.**
Un ADT separa la interfaz de la representación.  Por ejemplo, una secuencia puede ofrecer operaciones como acceder, insertar o eliminar, pero por debajo puede estar implementada con arreglo dinámico, lista enlazada u otra estructura.  Además, la interfaz puede mantenerse igual mientras cambian costo, uso de memoria y detalles internos.  
Esa es precisamente la ventaja de abstraer: el usuario del ADT trabaja con operaciones, no con la forma exacta en que los datos viven en memoria.

#### Bloque 2

**Construyan una tabla con cuatro columnas:**

* archivo,
* salida u observable importante,
* idea algorítmica,
* argumento de costo.

| archivo | salida u observable importante | idea algorítmica | argumento de costo |
|---|---|---|---|
| `demo_bubblesort.cpp` | Arreglo antes/después y, si aparece, número de comparaciones, swaps o pasadas **[ajustar con la salida exacta del demo]** | Comparar elementos adyacentes e ir “empujando” los mayores hacia el final en cada pasada | En general hace recorridos anidados sobre el arreglo; por eso el costo típico es `O(n^2)` en comparaciones |
| `demo_power.cpp` | Mismo resultado para una potencia, pero con menos multiplicaciones o menos llamadas **[ajustar con la salida exacta]** | Reducir el problema usando potencias parciales, idealmente por cuadrados | La versión ingenua es `O(n)` en el exponente; la mejorada puede bajar a `O(log n)` |
| `demo_fibonacci.cpp` | Valores correctos para `fib(n)` y crecimiento fuerte del número de llamadas/tiempo **[ajustar con la salida exacta]** | Definición recursiva de Fibonacci | La recursión ingenua repite subproblemas y lleva a crecimiento exponencial |
| `demo_countones.cpp` | Ejemplos donde dos números cercanos en valor no implican el mismo trabajo y donde importa la representación binaria **[ajustar con la salida exacta]** | Recorrer bits del número o eliminar bits encendidos según la técnica usada | El costo se relaciona con la cantidad de bits procesados, o con la cantidad de unos si se usa una técnica como `n &= (n-1)` |

1. **En `demo_bubblesort.cpp`, ¿qué salida sirve para defender costo y no solo resultado?**
La salida que mejor defiende costo es la que muestra comparaciones, swaps, pasadas o trazas del recorrido, no solo el arreglo ordenado.  Además, ver el arreglo final prueba funcionalidad básica; ver cuántas operaciones hizo el algoritmo permite argumentar cuánto trabajo realizó.

2. **En `demo_power.cpp`, ¿qué comparación concreta muestra una mejora algorítmica?**
La comparación concreta es que ambas versiones calculan la misma potencia, pero la mejorada requiere menos multiplicaciones o menos llamadas recursivas que la ingenua.  Esa igualdad de resultado con menor trabajo es la evidencia central de la mejora algorítmica.

3. **En `demo_fibonacci.cpp`, ¿qué crecimiento se vuelve defendible?**
Se vuelve defendible el crecimiento **exponencial** de la versión recursiva ingenua, porque el árbol de llamadas crece muy rápido al aumentar `n`; incluso si para valores pequeños parece aceptable, al crecer `n` el costo explota.

4. **En `demo_countones.cpp`, ¿qué ejemplo ayuda más a distinguir valor numérico de tamaño en bits?**
Un buen ejemplo es comparar números como `7` (`111`) y `8` (`1000`), o `1024` y `1025`.  El punto no es solo cuál es más grande, sino cómo cambia la representación binaria y cuántos bits hay que inspeccionar. También sirve recordar que todos los números entre `2^{k-1}` y `2^k - 1` tienen tamaño en bits parecido, aunque sus valores numéricos difieran mucho.

#### Bloque 3

1. **¿Qué funciones o ideas están verificando las pruebas públicas?**
Las pruebas públicas probablemente están verificando la correctitud funcional básica de las funciones centrales como: Ordenar correctamente, calcular potencias esperadas, devolver valores correctos de Fibonacci y contar bits encendidos de forma correcta.  Además, suelen verificar casos borde, consistencia de resultados y cumplimiento de la interfaz esperada.

2. **¿Qué sí demuestra una prueba pública?**
Una prueba pública sí demuestra que, para los casos probados, el programa produce la salida esperada.  También ayuda a detectar errores evidentes de implementación, regresiones y malentendidos de especificación.

3. **¿Qué no demuestra una prueba pública?**
No demuestra correctitud para **todas** las entradas posibles.  Tampoco demuestra por sí sola la complejidad asintótica, la optimalidad del algoritmo, la ausencia total de errores de memoria ni el comportamiento bajo todos los entornos de ejecución; por lo tanto, pasar tests no equivale a “probar matemáticamente” el algoritmo.

4. **Elijan una pregunta de `preguntas_semana1.md` y respóndanla bien.**
   **Pregunta elegida:**  
   **¿Por qué no basta con mostrar que un programa “funciona” en algunos ejemplos?**
   No basta porque algunos ejemplos solo muestran evidencia parcial.  Es importante aclarar que un programa puede acertar en casos pequeños o convenientes y aun así fallar en casos borde, entradas grandes o situaciones no previstas.  
   Para defender mejor una solución hay que separar tres cosas:  
   - La especificación: qué debería cumplir;  
   - La correctitud: por qué la salida satisface esa especificación;  
   - La evidencia experimental: qué casos observamos al ejecutarlo.  

   Los ejemplos ayudan, pero no reemplazan una justificación conceptual de por qué el algoritmo funciona en general.

5. **Usen la rúbrica para autoevaluarse en: comprensión conceptual, sustentación de correctitud, análisis de eficiencia.** 
- Comprensión conceptual: alta en la distinción entre problema, algoritmo, ADT e implementación; media si todavía confundimos interfaz con representación.  
- Sustentación de correctitud: media/alta si podemos explicar por qué cada función entrega el resultado esperado y no solo mostrar ejemplos.  
- Análisis de eficiencia: media/alta si distinguimos entre costo teórico, observable de ejecución y dependencia del tamaño de entrada.

#### Bloque 4

1. **¿Qué diferencia observable deja `demo_const_refs.cpp` entre lectura, modificación y copia?**
La diferencia observable es que una referencia constante permite leer sin copiar y sin modificar; una referencia no constante permite modificar el objeto original; y pasar por valor crea una copia independiente, lo que puede costar más tiempo y memoria.  Además, en el proceso de ejecución, esto se refleja en cambios visibles sobre el objeto original o en ausencia de esos cambios.

2. **En `bench_vector_growth.cpp`: ¿qué cambia con `reserve`?**
Con `reserve` se reduce la cantidad de realocaciones del vector al crecer, lo que evita copias o movimientos repetidos de elementos y hace más predecible el costo de inserción.  La idea no cambia la funcionalidad, pero sí mejora el comportamiento de memoria y rendimiento.

3. **En `bench_vector_ops.cpp`: ¿por qué `push_back`, `insert(begin())` e `insert(middle)` no cuestan lo mismo?**
Porque insertan en posiciones con distinto trabajo asociado.  
- `push_back`: Normalmente agrega al final y suele costar amortizado constante.  
- `insert(begin())`: Debe desplazar todos los elementos existentes.  
- `insert(middle)`: Desplaza aproximadamente la mitad, así que también es lineal, pero con menor trabajo que insertar al inicio.

4. **En `bench_cache_effects.cpp`: intuición sobre localidad de memoria**
La intuición es que acceder a memoria contigua y en orden suele ser más rápido porque aprovecha mejor la caché.  En cambio, accesos dispersos o con poca localidad hacen que el procesador traiga datos menos útiles y se pierda rendimiento.  Es una evidencia de que la representación en memoria también afecta el costo real.

#### Bloque 5

1. **Según `Ejercicios0.md`, ¿cuál es el orden correcto antes de optimizar?**
El orden correcto es:  
- Primero entender el problema y lograr una solución correcta.  
- Luego medir o perfilar.
- Después identificar el cuello de botella real.
- Finalmente solo entonces optimizar.  
Cabe resaltar que optimizar antes de validar correctitud y sin medir suele llevar a cambios innecesarios o engañosos.

2. **¿Qué quiere mostrar `stl_optimizacion_demostracion.cpp` con `reserve`, `nth_element`, `partial_sort` y `lower_bound`?**
Quiere mostrar que elegir bien la herramienta estándar cambia el costo real sin cambiar necesariamente el objetivo del programa.  
- `reserve` evita realocaciones innecesarias.  
- `nth_element` encuentra una posición de orden sin ordenar todo el arreglo.  
- `partial_sort` ordena solo una parte relevante cuando no hace falta ordenar todo.  
- `lower_bound` aprovecha que los datos estén ordenados para buscar en tiempo logarítmico.

3. **¿Qué tipo de evidencia puede producir `resolver_ejercicios0_v4.2.sh`?**
Puede producir evidencia experimental como tiempos de ejecución, salidas comparativas, resultados de compilación o ejecución repetida de casos de prueba.  Esa evidencia sirve para comparar implementaciones en práctica, no para reemplazar una demostración conceptual de correctitud.

4. **¿Qué limitaciones de entorno menciona `INSTRUCCIONES_Ejercicios0_v4.2.md`?**
Aunque hay que confirmar el texto exacto del archivo, las limitaciones típicas de este tipo de instrucciones son:  Dependencia del compilador y sus flags,  diferencias entre máquinas,  carga del sistema,  variabilidad de tiempos,  y posible falta de reproducibilidad exacta entre entornos.  Por eso los benchmarks deben leerse con cautela.

5. **¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?**
Porque medir desempeño no prueba que el programa sea correcto, ya que un programa puede ser rápido y estar mal.  Además, la discusión de correctitud responde si la salida satisface la especificación; la evidencia experimental responde cómo se comporta en ciertos entornos y casos observados; por lo que podemos afirmar que son complementarias y no son intercambiables.

#### Bloque 6

**¿Qué cambia cuando pasamos de defender correctitud básica en Semana1 a comparar implementaciones con evidencia experimental?**
Cuando pasamos de defender correctitud básica en Semana1 a comparar implementaciones con evidencia experimental, cambia el tipo de afirmación que estamos sosteniendo y también la clase de evidencia que necesitamos.
Primero aparece una afirmación de especificación: por ejemplo, “la función debe ordenar una secuencia no decrecientemente y conservar los mismos elementos de entrada”, o “la función debe devolver `a^n`”.  
Luego viene una afirmación de correctitud: “para toda entrada válida, el algoritmo produce una salida que cumple esa especificación”. Esa defensa se hace con invariantes, razonamiento por casos, estructura recursiva o argumentos similares.
Después agregamos una afirmación de costo: no basta decir que el programa funciona; ahora queremos defender cuánto trabajo hace, por ejemplo `O(n^2)` para Bubble Sort, `O(log n)` para potencia rápida o crecimiento exponencial para Fibonacci recursivo ingenuo. Esa afirmación ya no depende solo del resultado final, sino del número de operaciones relevantes.
También importa una afirmación de representación o memoria: dos implementaciones con la misma interfaz pueden comportarse distinto por cómo almacenan datos, copian objetos, realocan memoria o aprovechan la caché. Por eso la representación concreta sí afecta el costo observado.
Finalmente, hace falta una advertencia metodológica: la evidencia experimental no es una demostración matemática. Los tiempos dependen del hardware, compilador, optimizaciones, tamaño y distribución de entradas, calentamiento de caché y carga del sistema. Un benchmark bien hecho fortalece una hipótesis de rendimiento, pero no reemplaza ni la especificación ni la correctitud.

#### Autoevaluación breve
- **¿Qué podemos defender con seguridad?:** la diferencia entre problema, algoritmo, ADT e implementación; la idea general de correctitud; y por qué costo y representación no son lo mismo.
- **¿Qué todavía confundimos?:** cuándo una observación experimental basta como evidencia y cuándo hace falta una justificación conceptual más fuerte; también la diferencia exacta entre tamaño de entrada y valor numérico.
- **¿Qué evidencia usaríamos en una sustentación?:** trazas pequeñas, casos borde, resultados de pruebas públicas, conteo de operaciones relevantes, comparación entre implementaciones y una explicación explícita de la representación en memoria.