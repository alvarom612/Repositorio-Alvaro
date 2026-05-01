# Compilación y ejecución

## Configurar

```bash
cmake -S . -B build
```

## Compilar

```bash
cmake --build build
```

## Ejecutar demo

```bash
./build/nqueens_demo 4
```

## Ejecutar demo con traza

```bash
./build/nqueens_demo 4 --trace
```

## Ejecutar pruebas

```bash
./build/nqueens_tests
ctest --test-dir build --output-on-failure
```

## Ejecutar benchmark

```bash
./build/nqueens_benchmark
```

## Ejecutar actividades

```bash
./build/actividad1_tests
./build/actividad2_tests
./build/actividad3_tests
```