#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

struct graph{
    long vertexCount, edgeCount;
    vector<vector<long>> adjList;
    
    void init(long v){
        vertexCount = v;
        edgeCount = 0;

        for(int i=0; i<vertexCount; i++){
            adjList.push_back({}); // inserts V ammount of empty vector
        }
    }

    void add_edge(long vertex1, long vertex2){
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1);
        edgeCount++;
    }

    void bfs(vector<long> &result, long start, long L){
        vector<bool> visited(vertexCount, false);
        queue<long> q;
        result.clear();
        
        q.push(start);
        visited[start] = true;
        
        long distance = 0;

        while(!q.empty()) {
            long levelSize = q.size(); // number of nodes at current level
            
            if (distance == L) {
                // All remaining nodes in queue are at level L
                while (!q.empty()) {
                    result.push_back(q.front());
                    q.pop();
                }
                return;
            }
            
            // Process one level
            for (long i = 0; i < levelSize; ++i) {
                long temp = q.front(); q.pop();
                for (auto vertex : adjList[temp]) {
                    if (!visited[vertex]) {
                        q.push(vertex);
                        visited[vertex] = true;
                    }
                }
            }
            
            distance++; // go to next level after processing current level
        }
    }
};

int main(){
    graph g;
    int N, M, L, S;
    cin >> N >> M >> L >> S;
    g.init(N);
    for(int i=0; i<M; i++){
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    vector<long> bfs_result;
    g.bfs(bfs_result, S, L);

    if(bfs_result.empty()){
        cout << "Not Found" << endl;
        return 0;
    }

    else {
        for(auto it:bfs_result) cout << it << " ";
    } cout << endl;
    return 0;
}