#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm> // for min, max

using namespace std;

class Graph {
public:
    map<int, vector<pair<int, int>>> adjList;

    void add_edge(int u, int v, int w) {
        adjList[u].push_back(make_pair(v, w));
        adjList[v].push_back(make_pair(u, w));
    }

    bool dfs(int current, int targetWeight, int currentSum, set<pair<int, int>>& edgeVisited) {
        if (currentSum == targetWeight && !edgeVisited.empty()) return true;
        if (currentSum > targetWeight) return false;

        const vector<pair<int, int>>& neighbors = adjList[current];
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int neighbor = neighbors[i].first;
            int weight = neighbors[i].second;

            pair<int, int> edge = make_pair(min(current, neighbor), max(current, neighbor));
            if (edgeVisited.count(edge) == 0) {
                edgeVisited.insert(edge);
                if (dfs(neighbor, targetWeight, currentSum + weight, edgeVisited)) {
                    return true;
                }
                edgeVisited.erase(edge);
            }
        }
        return false;
    }

    bool weightFinder(int targetWeight) {
        map<int, vector<pair<int, int>>>::iterator it;
        for (it = adjList.begin(); it != adjList.end(); ++it) {
            int node = it->first;
            set<pair<int, int>> edgeVisited;
            if (dfs(node, targetWeight, 0, edgeVisited))
                return true;
        }
        return false;
    }

    void clear() {
        adjList.clear();
    }
};

int main() {
    int T;
    cin >> T;

    while (T--) {
        Graph g;
        int u, v, w;

        while (cin >> u >> v >> w, !(u == 0 && v == 0 && w == 0)) {
            g.add_edge(u, v, w);
        }

        int x;
        cin >> x;

        cout << (g.weightFinder(x) ? "YES\n" : "NO\n");
        g.clear();
    }

    return 0;
}
