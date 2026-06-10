#ifndef SKYLINE_HPP
#define SKYLINE_HPP

#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
 * Skyline Problem - CC232
 * Estructura basada en Sweep Line + Max Heap + Lazy Deletion
 */

class Skyline {
public:

    // Representa un edificio [left, right, height]
    struct Building {
        int left;
        int right;
        int height;
    };

    // Representa un evento del sweep line
    struct Event {
        int x;
        int height;
        bool isStart;

        Event(int x, int h, bool start)
            : x(x), height(h), isStart(start) {}
    };

    // Constructor vacío
    Skyline() = default;

    // Función principal: calcula skyline
    vector<vector<int>> getSkyline(const vector<Building>& buildings);

private:

    /*
     * Heap de máximos (priority queue)
     * Almacena alturas activas
     */
    priority_queue<int> maxHeap;

    /*
     * Lazy deletion:
     * marca alturas que ya no están activas
     */
    unordered_map<int, int> removed;

    /*
     * Limpia el heap eliminando alturas inválidas
     */
    void cleanHeap();

    /*
     * Genera eventos desde edificios
     */
    vector<Event> generateEvents(const vector<Building>& buildings);

    /*
     * Ordena eventos por regla del skyline
     */
    void sortEvents(vector<Event>& events);

};

#endif // SKYLINE_HPP