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
 
    void add_edge(long vertex1, long vertex2, long weight){
        adjList[vertex1].push_back(make_pair(vertex2, weight));
        // adjList[vertex2].push_back(make_pair(vertex1, weight)); // jangan lupa dimatikan ygy (directed)
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
                long weight = vertex.second;
 
 
                if(!visited[nextVertex] && result[u] + weight < result[nextVertex]){
                    result[nextVertex] = result[u] + weight;
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
    int V, N;
    cin >> V >> N;
    g.init(V);
    for (int i = 0; i < N; i++) {
        long u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
 
    vector<long> dijkstra_result;
    vector<long> predecessor;
    long start, end;
    cin >> start >> end;
 
    g.dijkstra(dijkstra_result, predecessor, start);
    vector<long> path = g.trace_path(start, end, predecessor);
   
    if (!path.empty()) {
        cout << "Path found with cost " << dijkstra_result[end] << ": ";
        for (auto node : path)  cout << node << " ";
        cout << endl;
    } else cout << "Impossible to find the path" << endl;
    
    return 0;
}
