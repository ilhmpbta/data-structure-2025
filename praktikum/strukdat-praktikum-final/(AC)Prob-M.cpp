#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    int N;
    cin >> N;
    map<string, int> chanek;

    for (int i = 0; i < N; ++i) {
        string command, fruit_name;
        int quantity;
        cin >> command >> fruit_name >> quantity;

        if (command == "ADD") {
            chanek[fruit_name] += quantity;
        } 
        else if (command == "SELL") {
            if (chanek.find(fruit_name) == chanek.end()) {
                cout << "item not found" << endl;
            } 
            else if (chanek[fruit_name] < quantity) {
                cout << "not enough stock" << endl;
            } 
            else {
                chanek[fruit_name] -= quantity;
                cout << "SUCCESS" << endl;
            }
        }
    }

    return 0;
}
