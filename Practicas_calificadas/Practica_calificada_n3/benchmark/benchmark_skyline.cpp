#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Skyline.h"

using namespace std;
using namespace std::chrono;

vector<vector<int>> generate(int n) {

    vector<vector<int>> b;
    b.reserve(n);

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distX(0, 100000);
    uniform_int_distribution<int> distH(1, 1000);

    for (int i = 0; i < n; i++) {

        int l = distX(gen);
        int r = l + (distX(gen) % 100 + 1);
        int h = distH(gen);

        b.push_back({l, r, h});
    }

    return b;
}

void run(int n) {

    Skyline s;
    auto data = generate(n);

    auto start = high_resolution_clock::now();
    auto res = s.getSkyline(data);
    auto end = high_resolution_clock::now();

    auto time = duration_cast<milliseconds>(end - start).count();

    cout << n << " "
         << res.size() << " "
         << time << "ms"
         << endl;
}

int main() {

    vector<int> tests = {
        100,
        500,
        1000,
        2000,
        5000,
        10000
    };

    cout << "n skyline_points time\n";

    for (int n : tests) {
        run(n);
    }

    return 0;
}