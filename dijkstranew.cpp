#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int besk = INT_MAX;

void dijkstra(int n, int s, const vector<vector<pair<int,int>>>& g) {
    vector<int> dist(n, besk);
    vector<bool> vis(n, false);
    dist[s] = 0;

    for (int step = 0; step < n; step++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!vis[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        if (dist[u] == besk) break;
        vis[u] = true;

        for (auto [v, w] : g[u])
            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == besk) {
            cout << -1 << " ";
        } else {
            cout << dist[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});

    }
    int s;
    cin >> s;
    dijkstra(n, s, g);
}