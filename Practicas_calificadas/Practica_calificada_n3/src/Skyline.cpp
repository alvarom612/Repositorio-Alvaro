#include "../include/skyline.hpp"

/*
 * Genera eventos desde los edificios:
 * - inicio: altura positiva
 * - fin: altura negativa (marca eliminación)
 */
vector<Skyline::Event> Skyline::generateEvents(const vector<Building>& buildings) {
    vector<Event> events;
    events.reserve(buildings.size() * 2);

    for (const auto& b : buildings) {
        events.emplace_back(b.left, b.height, true);   // inicio
        events.emplace_back(b.right, b.height, false); // fin
    }

    return events;
}

/*
 * Orden de eventos:
 * 1. x ascendente
 * 2. si mismo x:
 *    - eventos de inicio antes que fin
 *    - si ambos inicio: mayor altura primero
 *    - si ambos fin: menor altura primero
 */
void Skyline::sortEvents(vector<Event>& events) {
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (a.x != b.x)
            return a.x < b.x;

        if (a.isStart != b.isStart)
            return a.isStart > b.isStart; // start primero

        if (a.isStart)
            return a.height > b.height;   // más alto primero

        return a.height < b.height;       // fin: menor primero
    });
}

/*
 * Limpieza lazy deletion:
 * elimina del heap alturas ya marcadas como removidas
 */
void Skyline::cleanHeap() {
    while (!maxHeap.empty()) {
        int h = maxHeap.top();

        if (removed[h] > 0) {
            removed[h]--;
            maxHeap.pop();
        } else {
            break;
        }
    }
}

/*
 * Algoritmo principal Skyline
 */
vector<vector<int>> Skyline::getSkyline(const vector<Building>& buildings) {

    vector<vector<int>> result;

    if (buildings.empty())
        return result;

    vector<Event> events = generateEvents(buildings);
    sortEvents(events);

    maxHeap = priority_queue<int>();
    removed.clear();

    int prevHeight = 0;

    for (const auto& e : events) {

        if (e.isStart) {
            // agregar altura
            maxHeap.push(e.height);
        } else {
            // marcar para eliminación (lazy)
            removed[e.height]++;
        }

        cleanHeap();

        int currentHeight = maxHeap.empty() ? 0 : maxHeap.top();

        // si cambia el skyline, registrar punto clave
        if (currentHeight != prevHeight) {
            result.push_back({e.x, currentHeight});
            prevHeight = currentHeight;
        }
    }

    return result;
}