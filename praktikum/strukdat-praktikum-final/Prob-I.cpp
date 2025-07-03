#include <iostream>
#include <vector>

using namespace std;

struct Room {
    int xmin, ymin, xmax, ymax;  // Boundaries of the room
    vector<pair<int, int>> people;  // List of people in this room
    Room(int xmin, int ymin, int xmax, int ymax) 
        : xmin(xmin), ymin(ymin), xmax(xmax), ymax(ymax) {}
    
    // Function to check if a person is in this room
    bool contains(int x, int y) {
        return x >= xmin && x <= xmax && y >= ymin && y <= ymax;
    }
    
    // Function to split the room into 4 smaller rooms
    void split(vector<Room>& rooms) {
        int xm = (xmin + xmax) / 2;  // Midpoint in the x-axis
        int ym = (ymin + ymax) / 2;  // Midpoint in the y-axis
        rooms.push_back(Room(xmin, ymin, xm, ym));   // Bottom-left
        rooms.push_back(Room(xm+1, ymin, xmax, ym)); // Bottom-right
        rooms.push_back(Room(xmin, ym+1, xm, ymax)); // Top-left
        rooms.push_back(Room(xm+1, ym+1, xmax, ymax));// Top-right
    }
};

// Recursive function to count rooms
int countRooms(vector<Room>& rooms) {
    int leafCount = 0;
    vector<Room> nextRooms;

    for (auto& room : rooms) {
        if (room.people.size() == 1) {
            leafCount++;
        } else if (room.people.size() > 1) {
            room.split(nextRooms);
            for (auto& person : room.people) {
                for (auto& newRoom : nextRooms) {
                    if (newRoom.contains(person.first, person.second)) {
                        newRoom.people.push_back(person);
                    }
                }
            }
        }
    }
    
    if (!nextRooms.empty()) {
        leafCount += countRooms(nextRooms);
    }

    return leafCount;
}

int main() {
    int N;
    cin >> N;

    vector<pair<int, int>> people(N);
    for (int i = 0; i < N; ++i) {
        cin >> people[i].first >> people[i].second;
    }

    vector<Room> rooms;
    rooms.push_back(Room(-100, -100, 100, 100));  // Initial room covering all the space

    // Insert all people into the room (starting with one big room)
    for (auto& person : people) {
        for (auto& room : rooms) {
            if (room.contains(person.first, person.second)) {
                room.people.push_back(person);
                break;
            }
        }
    }

    // Now count how many leaf nodes exist (i.e., rooms)
    cout << countRooms(rooms) << endl;

    return 0;
}
