#include "Skyline.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>>
Skyline::getSkyline(vector<vector<int>>& buildings) {

    vector<pair<int,int>> events;

    for (auto &b : buildings) {
        events.push_back({b[0], -b[2]});
        events.push_back({b[1],  b[2]});
    }

    sort(events.begin(), events.end());

    multiset<int> heights;
    heights.insert(0);

    vector<vector<int>> result;

    int prevMax = 0;

    for (auto &e : events) {

        int x = e.first;
        int h = e.second;

        if (h < 0) {
            heights.insert(-h);
        } else {
            auto it = heights.find(h);
            if (it != heights.end()) {
                heights.erase(it);
            }
        }

        _ASSERT(!heights.empty());
        int currentMax = *heights.rbegin();

        if (currentMax != prevMax) {
            result.push_back({x, currentMax});
            prevMax = currentMax;
            cout << "Event: " << x << ", Height: " << currentMax << endl;
        } else {
            _ASSERT(false); // This should not be reached
        }
    }

    return result;
}