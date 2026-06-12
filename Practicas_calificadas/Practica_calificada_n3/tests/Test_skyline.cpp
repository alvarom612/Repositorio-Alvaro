#include <cassert>
#include <vector>
#include "Skyline.h"

using namespace std;

void test_basic() {
    Skyline s;

    vector<vector<int>> b = {
        {2,9,10},
        {3,7,15},
        {5,12,12},
        {15,20,10},
        {19,24,8}
    };

    auto r = s.getSkyline(b);

    assert(!r.empty());
    assert(r[0][1] == 10 || r[0][1] == 15);
}

void test_single_building() {
    Skyline s;

    vector<vector<int>> b = {{0,2,3}};
    auto r = s.getSkyline(b);

    assert(r.size() == 2);
    assert(r[0][1] == 3);
    assert(r[1][1] == 0);
}

void test_overlap_same_height() {
    Skyline s;

    vector<vector<int>> b = {
        {1,5,5},
        {2,6,5},
        {3,7,5}
    };

    auto r = s.getSkyline(b);

    assert(!r.empty());
    assert(r.back()[1] == 0);
}

void test_same_x_events() {
    Skyline s;

    vector<vector<int>> b = {
        {2,10,10},
        {2,10,7},
        {2,10,12}
    };

    auto r = s.getSkyline(b);

    assert(r[0][1] == 12);
}

void test_disjoint_buildings() {
    Skyline s;

    vector<vector<int>> b = {
        {1,3,3},
        {5,7,4},
        {9,11,2}
    };

    auto r = s.getSkyline(b);

    assert(!r.empty());
    assert(r.size() >= 6);
}

void test_flat_ground() {
    Skyline s;

    vector<vector<int>> b = {};

    auto r = s.getSkyline(b);

    assert(r.empty());
}

int main() {

    test_basic();
    test_single_building();
    test_overlap_same_height();
    test_same_x_events();
    test_disjoint_buildings();
    test_flat_ground();

    return 0;
}