#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class ElevatorSystem {
private:
    int current_floor;
    bool direction_up;  // true for up, false for down
    set<int> pending_requests;
    
public:
    ElevatorSystem() : current_floor(0), direction_up(true) {}
    
    void add_request(int floor) {
        pending_requests.insert(floor);
    }
    
    void cancel_request(int floor) {
        pending_requests.erase(floor);
    }
    
    void action() {
        if (pending_requests.empty()) {
            return;  // No requests, stay still
        }
        
        // Find the best request based on current direction
        int target_floor = -1;
        
        if (direction_up) {
            // Look for requests at or above current floor
            auto it = pending_requests.lower_bound(current_floor);
            if (it != pending_requests.end()) {
                target_floor = *it;
            }
        } else {
            // Look for requests below current floor
            auto it = pending_requests.lower_bound(current_floor);
            if (it != pending_requests.begin()) {
                --it;
                target_floor = *it;
            }
        }
        
        if (target_floor == -1) {
            // No request in current direction, reverse direction
            direction_up = !direction_up;
            
            // Try again with new direction
            if (direction_up) {
                auto it = pending_requests.lower_bound(current_floor);
                if (it != pending_requests.end()) {
                    target_floor = *it;
                }
            } else {
                auto it = pending_requests.lower_bound(current_floor);
                if (it != pending_requests.begin()) {
                    --it;
                    target_floor = *it;
                }
            }
        }
        
        if (target_floor != -1) {
            // Move to target floor and complete request
            current_floor = target_floor;
            pending_requests.erase(target_floor);
        }
    }
    
    int locate() const {
        return current_floor;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    ElevatorSystem elevator;
    
    for (int i = 0; i < n; i++) {
        string command;
        cin >> command;
        
        if (command == "action") {
            elevator.action();
        } else if (command == "add") {
            int floor;
            cin >> floor;
            elevator.add_request(floor);
        } else if (command == "cancel") {
            int floor;
            cin >> floor;
            elevator.cancel_request(floor);
        } else if (command == "locate") {
            cout << elevator.locate() << "\n";
        }
    }
    
    return 0;
}