# Bitácora de desarrollo - PC3 CC232


## Domingo 7 de junio de 2026 - Planteamiento del problema

Se realizó la lectura inicial del problema **LeetCode 218 - The Skyline Problem**.

Se identificaron los siguientes puntos clave:

- El problema requiere simular el contorno de edificios.
- Es necesario manejar eventos de inicio y fin de intervalos.
- Una solución ingenua resulta ineficiente para grandes entradas.
- Se detecta la necesidad de una estructura tipo heap o multiset.

Se decidió aplicar un enfoque basado en:

- Sweep Line
- Priority Queue (max heap)
- Lazy deletion

### Decisión inicial de diseño

Se plantea dividir el problema en tres componentes:

- generación de eventos
- ordenamiento de eventos
- mantenimiento de estructura activa


## Lunes 8 de junio de 2026 - Estructura base del proyecto

Se creó la estructura inicial del repositorio.

### Archivos creados:

- `README.md`
- `CMakeLists.txt`

### Actividades realizadas:

- Definición del problema en README
- Descripción del enfoque general
- Configuración de compilación con CMake
- Definición del estándar C++17

Se dejó preparado el entorno para implementar el algoritmo.


## Martes 9 de junio de 2026 - Implementación base

Se implementó la solución principal del problema.

### Archivos creados/modificados:

- `include/skyline.h`
- `src/skyline.cpp`
- `tests/test_skyline.cpp`

### Actividades realizadas:

- Implementación de estructura Building y Event
- Implementación de generación de eventos
- Implementación del algoritmo sweep line
- Integración de max heap
- Implementación de lazy deletion mediante hash map

### Pruebas iniciales:

- Caso mínimo
- Caso clásico del problema
- Caso con edificios solapados

Se verificó que la estructura general produce resultados correctos en ejemplos pequeños.


## Miércoles 10 de junio de 2026 - Validación, bitácora y documentación

Se completó la parte de validación y documentación del proyecto.

### Archivos creados:

- `docs/respuestas_obligatorias.md`
- `docs/preguntas_skyline.md`
- `docs/bitacora.md` (este archivo)

### Actividades realizadas:

- Redacción de respuestas teóricas del problema
- Justificación de complejidad O(n log n)
- Explicación formal del invariante del heap
- Descripción del uso de lazy deletion
- Alineación con semanas 4–6 del curso

### Ajustes técnicos:

- Se revisó el orden de eventos en coordenadas iguales
- Se mejoró la limpieza del heap
- Se verificó consistencia en casos borde

### Validación adicional:

- Comparación conceptual con solución ingenua
- Revisión de duplicados y alturas repetidas


## Jueves 11 de junio de 2026 - Grabación del video

Se realizó la grabación del video de sustentación.

### Actividades realizadas:

- Ejecución desde repositorio limpio
- Demostración de compilación con CMake
- Ejecución de tests automatizados
- Explicación del algoritmo paso a paso
- Modificación en vivo del código (bloque sin cortes)

### Demostración incluida:

- git status
- git log con formato de fechas
- ejecución de tests
- visualización de salida del skyline

### Validación en video:

- se mostró el heap en funcionamiento implícito
- se explicó el invariante del algoritmo
- se justificó el uso de lazy deletion


## Observaciones finales

El desarrollo siguió un proceso incremental:

1. comprensión del problema
2. diseño de estructura
3. implementación del algoritmo
4. validación con pruebas
5. documentación teórica
6. grabación final

Se asegura trazabilidad completa entre código, commits y video.


# Fin de bitácora