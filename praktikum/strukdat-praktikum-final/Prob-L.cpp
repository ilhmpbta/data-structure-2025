#include <iostream>
#include <vector>
#include <cstring>
#define MOD 1000000007
using namespace std;

struct graph{
    int n, m;
    vector<vector<int>> adjList;

    void init(int n, int m) {
        this->n = n;
        this->m = m;
        adjList.resize(n);
    }

    void add_edge(int u, int v) {
        adjList[u].push_back(v);
    }
};

int hamiltonian_path(graph& g) {
    vector<vector<int>> dp(1 << g.n, vector<int>(g.n, 0));
    
    dp[1][0] = 1;

    for (int mask = 1; mask < (1 << g.n); ++mask) {
        for (int u = 0; u < g.n; ++u) {
            if ((mask & (1 << u)) == 0)
                continue;

            for (int v : g.adjList[u]) {
                if ((mask & (1 << v)) == 0) {
                    dp[mask | (1 << v)][v] = (dp[mask | (1 << v)][v] + dp[mask][u]) % MOD;
                }
            }
        }
    }

    return dp[(1 << g.n) - 1][g.n - 1];
}

int main() {
    int n, m;
    cin >> n >> m;

    graph g;
    g.init(n, m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u - 1, v - 1); 
    }
    cout << hamiltonian_path(g) << endl;

    return 0;
}
