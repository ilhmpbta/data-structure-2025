#include <iostream>
#include <vector>
using namespace std;

int magic(vector<int>& card) { 
    int left = 1;
    int right = card.size() - 2;
    int maxleft = card[left - 1];
    int maxright = card[right + 1];

    int res = 0;
    while (left <= right) {
        if (maxright >= maxleft) { 
            res += max(0, maxleft - card[left]);
            maxleft = max(maxleft, card[left]);
            left += 1;
        } else {
            res += max(0, maxright - card[right]);
            maxright = max(maxright, card[right]);
            right -= 1;
        } 
    }
    return res;
}

int main() {
    vector<int> lyney;
    int N, x;
    cin >> N;

    while (N--) {
        cin >> x;
        lyney.push_back(x);
    }

    cout << magic(lyney) << endl;
    return 0;
}
