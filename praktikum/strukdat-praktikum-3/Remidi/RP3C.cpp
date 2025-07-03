#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

struct graph{
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
   
    void init(long v){
        vertexCount = v;
        edgeCount = 0;
 
 
        adjList.resize(vertexCount);
    }
 
    void add_edge(long u, long v, long w){
        adjList[u].push_back(make_pair(v, w));
        adjList[v].push_back(make_pair(u, w));
        edgeCount++;
    }
 
    void dijkstra(vector<long> &result, vector<long> &predecessor, long start){
        vector<bool> visited(vertexCount, false);
        priority_queue <pair<long, long>,
                        vector <pair<long, long>>,
                        greater <pair<long, long>> > pq;
        result = vector<long>(vertexCount, LONG_MAX);
        predecessor = vector<long>(vertexCount, -1); // predecessor is a vector to store the predecessor (pendahulu) of each node
       
        pq.push(make_pair(0, start));
        result[start] = 0;
 
 
        while(!pq.empty()){
            auto temp = pq.top();
            pq.pop();
 
 
            long u = temp.second;
            if (visited[u]) continue;
            visited[u] = true;
 
 
            for(auto vertex:adjList[u]){
                long nextVertex = vertex.first;
                long w = vertex.second;
 
 
                if(!visited[nextVertex] && result[u] + w < result[nextVertex]){
                    result[nextVertex] = result[u] + w;
                    pq.push(make_pair(result[nextVertex], nextVertex));
                    predecessor[nextVertex] = u; // store the predecessor of nextVertex
                }
            }
        }
    }
 
    vector<long> trace_path(long start, long end, const vector<long>& predecessor) {
        vector<long> path;
        // loop from end to start using predecessor 
        for (long at = end; at != -1; at = predecessor[at]) {
            path.push_back(at);
        }
        // reverse the path to get it from start to end
        reverse(path.begin(), path.end());
        if (path.front() == start) {
            // if the path starts with the start node, return the path
            return path;
        }
        return {}; // return an empty path if there is no path from start to end
    }
};
 
 
int main(){
    graph g;
    long A, B;
    cin >> A >> B;
    g.init(A);
    for (auto i = 0; i < B; i++){
        long u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    long N;
    cin >> N;
    while (N--){
        long S;
        cin >> S;
        if (g.adjList[S].empty() || S < 0 || S >= g.vertexCount) {
            cout << "Invalid starting point" << endl;
        }

        else {
            vector<long> dijkstra_result;
            vector<long> predecessor;
            sort(g.adjList[S].begin(), g.adjList[S].end());
            g.dijkstra(dijkstra_result, predecessor, S);
            for (int i = 0; i < g.vertexCount; i++) {
                vector<long> path = g.trace_path(S, i, predecessor);
                if (path.empty() || S == i) continue;
                else {
                    cout << "---From " << S << " to " << i << "---" << endl;
                    for (auto that: path) {
                        cout << that;
                        if (that != path.back()) cout << " - ";
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}
