#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
using namespace std;

struct graph{
    long vertexCount, edgeCount;
    vector<vector<pair<long, long>>> adjList;
   
    void init(long v){
        vertexCount = v;
        edgeCount = 0;
 
 
        adjList.resize(vertexCount);
    }
 
    void add_edge(long vertex1, long vertex2, long weight){
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        edgeCount++;
    }
 
    void dijkstra(vector<long> &result, vector<long> &predecessor, long start){
        vector<bool> visited(vertexCount, false);
        priority_queue <pair<long, long>,
                        vector <pair<long, long>>,
                        greater <pair<long, long>> > pq;
        result = vector<long>(vertexCount, LONG_MAX);
        predecessor = vector<long>(vertexCount, -1);
       
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
                long weight = vertex.second;
 
 
                if(!visited[nextVertex] && result[u] + weight < result[nextVertex]){
                    result[nextVertex] = result[u] + weight;
                    pq.push(make_pair(result[nextVertex], nextVertex));
                    predecessor[nextVertex] = u;
                }
            }
        }
    }
 
    vector<long> trace_path(long start, long end, const vector<long>& predecessor) {
        vector<long> path;
        for (long at = end; at != -1; at = predecessor[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        if (path.front() == start) {
            return path;
        }
        return {};
    }
};
 
 
int main(){
    int n,m,s,t;
    cin >> n >> m >> s >> t;
    graph g; g.init(n+1);

    while (m--) {
        int u,v,w;
        cin >> u >> v >> w;
        g.add_edge(u,v,w);
    }

    vector<long> dijkstra_result, predecessor, path;
    g.dijkstra(dijkstra_result, predecessor, s);
    path = g.trace_path(s, t, predecessor);

    int cost = dijkstra_result[t];
    if (path.size() > (n/2)) cost = (cost + 1)/2;

    cout << cost << endl;

    return 0;
}