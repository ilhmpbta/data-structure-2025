#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
#include <map>
#include <set>
using namespace std;

struct graph{
    long vertexCount, edgeCount;
    vector<vector<long>> adjList;
    vector<bool> visited;
    vector<long> parent;
    vector<long> cyclePath;
    long startCycle = -1, endCycle = -1;
    
    void init(long v){
        vertexCount = v;
        edgeCount = 0;
        visited.assign(vertexCount, false);
        parent.assign(vertexCount, -1);
        for(int i=0; i<vertexCount; i++) adjList.push_back({});
    }

    void add_edge(long vertex1, long vertex2){
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
        edgeCount++;
    }

    bool dfs_cycle(long node, long par) {
        visited[node] = true;
        parent[node] = par;

        for (auto neighbor : adjList[node]) {
            if (neighbor == par) continue;
            if (visited[neighbor]) {
                startCycle = neighbor;
                endCycle = node;
                return true;
            }
            if (dfs_cycle(neighbor, node)) return true;
        }
        return false;
    }

    void cycle_path() {
        cyclePath.clear();
        long curr = endCycle;
        cyclePath.push_back(startCycle);

        while (curr != startCycle) {
            cyclePath.push_back(curr);
            curr = parent[curr];
        }
        cyclePath.push_back(startCycle); 
        sort(cyclePath.begin(), cyclePath.end());
        cyclePath.erase(unique(cyclePath.begin(), cyclePath.end()), cyclePath.end());
    }

    bool check_cycle() {
        visited.assign(vertexCount, false);
        parent.assign(vertexCount, -1);
        startCycle = -1;
        endCycle = -1;

        for (long i = 0; i < vertexCount; i++) {
            if (!visited[i]) {
                if (dfs_cycle(i, -1)) {
                    cycle_path();
                    return true;
                }
            }
        }
        return false;
    }
};

int main(){
    int N; cin >> N;
    while (N--) {
        long u, v; cin >> u >> v;
        graph g;
        g.init(u);

        while (v--) {
            long v1, v2; cin >> v1 >> v2;
            g.add_edge(v1, v2);
        }

        if (g.check_cycle()) {
            cout << "VOCALOID CYCLE PROGRAM (VCP) : CYCLE DETECTED";
            for (auto x : g.cyclePath) cout << " " << x;
            cout << "\n";
        } else cout << "VOCALOID CYCLE PROGRAM (VCP) : NO CYCLE DETECTED\n";
    }  return 0;
}
