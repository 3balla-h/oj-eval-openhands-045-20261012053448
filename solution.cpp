#include <cstdio>
#include <iostream>

using namespace std;

const int MAX_REQUESTS = 500005;

class ElevatorSystem {
private:
    int current_floor;
    bool direction_up;  // true for up, false for down
    int requests[MAX_REQUESTS];
    int request_count;
    
    // Binary search to find insertion position
    int find_position(int floor) {
        int left = 0, right = request_count;
        while (left < right) {
            int mid = (left + right) / 2;
            if (requests[mid] < floor) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
    
    // Find first request >= current_floor
    int find_lower_bound(int floor) {
        int left = 0, right = request_count;
        while (left < right) {
            int mid = (left + right) / 2;
            if (requests[mid] < floor) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
    
public:
    ElevatorSystem() : current_floor(0), direction_up(true), request_count(0) {}
    
    void add_request(int floor) {
        int pos = find_position(floor);
        // Insert at position pos
        for (int i = request_count; i > pos; i--) {
            requests[i] = requests[i-1];
        }
        requests[pos] = floor;
        request_count++;
    }
    
    void cancel_request(int floor) {
        int pos = find_position(floor);
        // Find the exact position
        while (pos < request_count && requests[pos] != floor) {
            pos++;
        }
        if (pos < request_count && requests[pos] == floor) {
            // Remove at position pos
            for (int i = pos; i < request_count - 1; i++) {
                requests[i] = requests[i+1];
            }
            request_count--;
        }
    }
    
    void action() {
        if (request_count == 0) {
            return;  // No requests, stay still
        }
        
        // Find the best request based on current direction
        int target_floor = -1;
        
        if (direction_up) {
            // Look for requests at or above current floor
            int pos = find_lower_bound(current_floor);
            if (pos < request_count) {
                target_floor = requests[pos];
            }
        } else {
            // Look for requests below current floor
            int pos = find_lower_bound(current_floor);
            if (pos > 0) {
                target_floor = requests[pos-1];
            }
        }
        
        if (target_floor == -1) {
            // No request in current direction, reverse direction
            direction_up = !direction_up;
            
            // Try again with new direction
            if (direction_up) {
                int pos = find_lower_bound(current_floor);
                if (pos < request_count) {
                    target_floor = requests[pos];
                }
            } else {
                int pos = find_lower_bound(current_floor);
                if (pos > 0) {
                    target_floor = requests[pos-1];
                }
            }
        }
        
        if (target_floor != -1) {
            // Move to target floor and complete request
            current_floor = target_floor;
            cancel_request(target_floor);
        }
    }
    
    int locate() const {
        return current_floor;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    
    ElevatorSystem elevator;
    
    for (int i = 0; i < n; i++) {
        char command[20];
        scanf("%s", command);
        
        if (command[0] == 'a' && command[1] == 'c') {
            elevator.action();
        } else if (command[0] == 'a' && command[1] == 'd') {
            int floor;
            scanf("%d", &floor);
            elevator.add_request(floor);
        } else if (command[0] == 'c') {
            int floor;
            scanf("%d", &floor);
            elevator.cancel_request(floor);
        } else if (command[0] == 'l') {
            printf("%d\n", elevator.locate());
        }
    }
    
    return 0;
}