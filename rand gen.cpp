#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int n = 50 + rand() % 51;
    int start = 0;

    vector<vector<int>> edges;

    for (int i = 1; i < n; i++) {
        int u = rand() % i;
        int v = i;
        int w = (rand() % 21) - 10;
        if (w == 0) w = 1;
        edges.push_back({u, v, w});
    }

    int extra = n * 3;
    for (int i = 0; i < extra; i++) {
        int u = rand() % n;
        int v = rand() % n;
        if (u == v) continue;
        int w = (rand() % 21) - 10;
        if (w == 0) w = 1;
        edges.push_back({u, v, w});
    }

    cout << n << " " << edges.size() << " " << start << "\n";
    for (auto e : edges) {
        cout << e[0] << " " << e[1] << " " << e[2] << "\n";
    }
}
