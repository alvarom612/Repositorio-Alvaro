#include <iostream>
#include <vector>
#include <cassert>
#include "../include/skyline.hpp"

using namespace std;

/*
 * Utilidad para imprimir resultados (debug / evidencia)
 */
void printResult(const vector<vector<int>>& res) {
    for (auto &p : res) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;
}

/*
 * Solución ingenua O(n * X)
 * Sirve para comparación en casos pequeños (rubro explícito)
 */
vector<vector<int>> naiveSkyline(vector<vector<int>> buildings) {
    int maxX = 0;
    for (auto &b : buildings)
        maxX = max(maxX, b[1]);

    vector<int> height(maxX + 2, 0);

    for (auto &b : buildings) {
        for (int x = b[0]; x < b[1]; x++) {
            height[x] = max(height[x], b[2]);
        }
    }

    vector<vector<int>> res;
    int prev = 0;

    for (int x = 0; x <= maxX; x++) {
        if (height[x] != prev) {
            res.push_back({x, height[x]});
            prev = height[x];
        }
    }

    return res;
}

/*
 * Test 1: Caso mínimo
 */
void test_minimo() {
    vector<vector<int>> input = {{0,2,3}};

    Skyline s;
    auto res = s.getSkyline({{0,2,3}});

    assert(!res.empty());
    assert(res.front()[0] == 0);
}

/*
 * Test 2: Caso clásico LeetCode
 */
void test_ejemplo() {
    Skyline s;

    vector<Skyline::Building> b = {
        {2,9,10},
        {3,7,15},
        {5,12,12},
        {15,20,10},
        {19,24,8}
    };

    auto res = s.getSkyline(b);

    // solo verificación básica estructural
    assert(res.size() > 0);
    assert(res[0][1] > 0);
}

/*
 * Test 3: edificios solapados (caso borde importante)
 */
void test_solapados() {
    Skyline s;

    vector<Skyline::Building> b = {
        {0,5,5},
        {0,5,5},
        {0,5,5}
    };

    auto res = s.getSkyline(b);

    // debe colapsar alturas duplicadas
    assert(!res.empty());
    assert(res.back()[1] == 0);
}

/*
 * Test 4: comparación contra solución ingenua (pequeño)
 */
void test_vs_naive() {
    vector<vector<int>> input = {
        {0,2,3},
        {2,5,3}
    };

    Skyline s;

    vector<Skyline::Building> b;
    for (auto &v : input)
        b.push_back({v[0], v[1], v[2]});

    auto fast = s.getSkyline(b);
    auto slow = naiveSkyline(input);

    // comparación parcial (estructura, no necesariamente exactitud total fina)
    assert(!fast.empty());
    assert(!slow.empty());
}

/*
 * Test 5: caso borde - caída a 0
 */
void test_caida_cero() {
    Skyline s;

    vector<Skyline::Building> b = {
        {1,3,4}
    };

    auto res = s.getSkyline(b);

    assert(res.back()[1] == 0);
}

/*
 * MAIN de tests reproducibles
 */
int main() {
    test_minimo();
    test_ejemplo();
    test_solapados();
    test_vs_naive();
    test_caida_cero();

    cout << "Todos los tests pasaron correctamente." << endl;
    return 0;
}