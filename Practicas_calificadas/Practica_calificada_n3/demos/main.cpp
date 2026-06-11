#include <iostream>
#include <vector>
#include "../include/skyline.hpp"

using namespace std;

int main() {

    Skyline solver;

    vector<Skyline::Building> buildings = {
        {2,9,10},
        {3,7,15},
        {5,12,12},
        {15,20,10},
        {19,24,8}
    };

    vector<vector<int>> result = solver.getSkyline(buildings);

    cout << "Skyline result:" << endl;

    for (const auto &p : result) {
        cout << "[" << p[0] << ", " << p[1] << "]" << endl;
    }

    return 0;
}