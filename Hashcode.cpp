#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

struct City {
    int rows;
    int columns;
    
    // Constructor
    City() {
        std::cin >> rows >> columns;
    }
    
};

struct Intersection {
    int row, column;
    Intersection(int row_, int column_) : row(row_), column(column_) {}
    
    Intersection() {}
    
};

int ManhattanDistance(Intersection source, Intersection dest) {
    //hace manhattan distance
    return abs(dest.row - source.row) + abs(dest.column - source.column);
}

int ride_counter = 0;
struct Ride {
    // DFS
    bool is_used;
    
    int id;
    Intersection start, end;
    int time_start;
    // time_finish >= time_start + ManhattanDistance(start, end)
    int time_finish;
    
    Ride() {}
    
    void Read() {
        id = ride_counter++;
        is_used = false;
        std::cin >> start.row >> start.column >> end.row >> end.column >> time_start >> time_finish;
    }
    
    // Time untill optimum pick-up [0..return]
    int OptimumTime() {
        return time_start + ManhattanDistance(start, end);
    }
};

bool comp(const Ride& a, const Ride& b) {
    if (a.time_start < b.time_start) return true;
    else if (a.time_start == b.time_start) {
        if (ManhattanDistance(a.start, a.end) > ManhattanDistance(b.start, b.end)) return false;
        return true;
    }
    else return false;
}

struct Vehicle {
    // BFS
    int id;
    Intersection position;
    int time;
    // DFS
    std::vector<Intersection> positions;
    
    std::vector<int> rides_assigned;
    
    // DFS
    Vehicle() : position(Intersection(0, 0)) {
        time = 0;
        positions.push_back(Intersection(0, 0));
    }
    
    void Print() {
        std::cout << rides_assigned.size();
        for (int i = 0; i < rides_assigned.size(); i++) {
            std::cout << ' ' << rides_assigned[i];
        }
        std::cout << std::endl;
    }
};

std::vector<Vehicle> vehicles;
std::vector<Ride> rides;
// DFS


// BFS
int OptimumTime(const Ride& ride) {
    return ride.time_start + ManhattanDistance(ride.start, ride.end);
}
// BFS
void Algorithm_BFS(const int& bonus_per_ride, const int& n_steps) {
    while(true){
        bool found = false;
        for(int i = 0; i < vehicles.size(); i++){
            for(int j = 0; j < rides.size(); j++){
                // If possible
                if(!rides[j].is_used && vehicles[i].time < (rides[j].time_start
                                                            + ManhattanDistance(vehicles[i].position, rides[j].start)
                                                            + ManhattanDistance(rides[j].start, rides[j].end))
                   ){
                    vehicles[i].time = OptimumTime(rides[j]);
                    vehicles[i].position = rides[j].end;
                    vehicles[i].rides_assigned.push_back(rides[j].id);
                    rides[j].is_used = true;
                    found = true;
                    break;
                }
            }
        }
        if(!found) break;
    }
}


int main() {
    // City
    City barcelona;
    
    // Vehicles
    int n_vehicles;
    std::cin >> n_vehicles;
    vehicles = std::vector<Vehicle>(n_vehicles);
    for (int i = 0; i < n_vehicles; i++) {
        vehicles[i].id = i + 1;
    }
    
    // Rides
    int n_rides;
    std::cin >> n_rides;
    rides = std::vector<Ride>(n_rides);
    
    // Bonus
    int bonus_per_ride;
    std::cin >> bonus_per_ride;
    
    // Steps
    int n_steps;
    std::cin >> n_steps;
    
    // Read
    for (int n_rides = 0; n_rides < rides.size(); n_rides++) {
        rides.at(n_rides).Read();
        // Maybe check invalid
    }
    
    // Algorithm
    Algorithm_BFS(bonus_per_ride, n_steps);
    
    // Print
    for(int n_vehicle = 0; n_vehicle < vehicles.size(); n_vehicle++){
        vehicles.at(n_vehicle).Print();
    }
    
    return 0;
}
