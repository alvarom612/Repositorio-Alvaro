# Casos de prueba

## Casos principales

| Entrada | Resultado esperado | Motivo |
|---|---:|---|
| `n = 1` | 1 solución | tablero mínimo válido |
| `n = 2` | 0 soluciones | caso sin solución |
| `n = 3` | 0 soluciones | caso sin solución |
| `n = 4` | 2 soluciones | ejemplo clásico de LeetCode |
| `n = 5` | 10 soluciones | valida que no solo funciona para el ejemplo |

## Casos defensivos

| Entrada | Resultado esperado |
|---|---|
| `n = 0` | lista vacía |
| `n < 0` | lista vacía |

## Validación de tableros

`isValidBoard` rechaza:

- filas con más de una reina,
- columnas repetidas,
- diagonales repetidas,
- caracteres distintos de `Q` y `.`,
- tableros con dimensiones incorrectas.
