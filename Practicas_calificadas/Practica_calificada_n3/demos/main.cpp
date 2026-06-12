#include <iostream>
#include <vector>
#include "Skyline.h"

using namespace std;

int main() {

    Skyline solver;

    vector<vector<int>> buildings = {
        {2, 9, 10},
        {3, 7, 15},
        {5, 12, 12},
        {15, 20, 10},
        {19, 24, 8}
    };

    vector<vector<int>> result = solver.getSkyline(buildings);

    for (auto &p : result) {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }

    cout << endl;

    return 0;
}