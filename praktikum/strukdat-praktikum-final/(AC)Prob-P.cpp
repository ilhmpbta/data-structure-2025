#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int nala_task(vector<char>& tasks, int q) {
    unordered_map<char, int> frequency;
    for (char task : tasks) {
        frequency[task]++;
    }

    priority_queue<int> pq;
    for (auto const& [key, val] : frequency) {
        pq.push(val);
    }

    int total_time = 0;
    while (!pq.empty()) {
        int k = q + 1;
        vector<int> temp;
        for (int i = 0; i < k; ++i) {
            if (!pq.empty()) {
                temp.push_back(pq.top());
                pq.pop();
                total_time++;
            }
        }

        for (int count : temp) if (--count > 0) pq.push(count);  
        if(pq.empty()) break;
        total_time += pq.empty() ? 0 : (q + 1 - temp.size());
    }
    return total_time;
}

int main() {
    vector<char> tasks;
    int p, q;
    cin >> p >> q;

    while(p--) {
        char t; 
        cin >> t;
        tasks.push_back(t);
    }

    cout << nala_task(tasks, q) << endl;
    return 0;
}
