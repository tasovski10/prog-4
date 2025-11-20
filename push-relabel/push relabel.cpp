#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int n;
vector<vector<int>> cap, flow;
vector<int> height, excess;

void push(int u, int v) {
    int d = min(excess[u], cap[u][v] - flow[u][v]);
    if (d > 0 && height[u] == height[v] + 1) {
        flow[u][v] += d;
        flow[v][u] -= d;
        excess[u] -= d;
        excess[v] += d;
    }
}

void relabel(int u) {
    int minH = INF;
    for (int v = 0; v < n; v++)
        if (cap[u][v] - flow[u][v] > 0)
            minH = min(minH, height[v]);
    if (minH < INF)
        height[u] = minH + 1;
}

int maxFlow(int s, int t) {
    height.assign(n, 0);
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);

    height[s] = n;
    for (int v = 0; v < n; v++) {
        flow[s][v] = cap[s][v];
        flow[v][s] = -cap[s][v];
        excess[v] = cap[s][v];
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int u = 0; u < n; u++) {
            if (u == s || u == t) continue;
            while (excess[u] > 0) {
                bool pushed = false;
                for (int v = 0; v < n; v++) {
                    int oldExcess = excess[u];
                    push(u, v);
                    if (excess[u] != oldExcess) {
                        pushed = true;
                        changed = true;
                        break;
                    }
                }
                if (!pushed) relabel(u);
            }
        }
    }

    int total = 0;
    for (int i = 0; i < n; i++)
        total += flow[i][t];
    return total;
}

int main() {
    int m, s, t;
    cin >> n >> m;
    cap.assign(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        cap[u][v] = c;
    }

    cin >> s >> t;

    cout << maxFlow(s, t) << "\n";
}
