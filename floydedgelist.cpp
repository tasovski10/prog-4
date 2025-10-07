#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int besk = INT_MAX;

struct Edge {
    int u, v, w;
};

int getw(const vector<Edge>& edges, int u, int v) {
    for (auto& e : edges)
        if (e.u == u && e.v == v) return e.w;
    return besk;
}

void setw(vector<Edge>& edges, int u, int v, int w) {
    for (auto& e : edges)
        if (e.u == u && e.v == v) {
            e.w = w;
            return;
        }
    edges.push_back({u, v, w});
}


void floyd(vector<Edge>& edges, int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int ik = getw(edges, i, k);
                int kj = getw(edges, k, j);
                int ij = getw(edges, i, j);
                if (ik != besk && kj != besk && ik + kj < ij)
                    setw(edges, i, j, ik + kj);
            }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }


    for (int i = 0; i < n; i++) setw(edges, i, i, 0);

    floyd(edges, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int d = getw(edges, i, j);
            if (d == besk) cout << "beskonecno\t";
            else cout << d << "\t";
        }
        cout << "\n";
    }
}