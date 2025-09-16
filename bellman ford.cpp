#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, m, start;
    cin >> n >> m >> start;

    vector<vector<pair<int,int>>> G(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }

    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    for (int k = 0; k < n - 1; k++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;
            for (auto edge : G[u]) {
                int v = edge.first, w = edge.second;
                if (dist[u] + w < dist[v]) dist[v] = dist[u] + w;
            }
        }
    }

    for (int u = 0; u < n; u++) {
        if (dist[u] == INT_MAX) continue;
        for (auto edge : G[u]) {
            int v = edge.first, w = edge.second;
            if (dist[u] + w < dist[v]) {
                cout << "negativen ciklus" << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX) cout << "beskonecno";
        else cout << dist[i] << " ";
    }
}
