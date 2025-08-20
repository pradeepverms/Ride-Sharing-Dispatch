#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Structure for Driver
struct Driver {
    string name;
    int distance; // distance from rider in meters
    double rating; // driver rating (1.0 to 5.0)

    Driver(string n, int d, double r) : name(n), distance(d), rating(r) {}
};

// Comparator for priority queue: prioritize by nearest distance, then higher rating
struct DriverCompare {
    bool operator()(const Driver& a, const Driver& b) {
        if (a.distance == b.distance)
            return a.rating < b.rating; // higher rating first if distances are same
        return a.distance > b.distance; // nearer distance first
    }
};

// Structure for Rider
struct Rider {
    string name;
    string location;

    Rider(string n, string l) : name(n), location(l) {}
};

// Structure for Ride History Entry
struct Ride {
    string riderName;
    string driverName;

    Ride(string r, string d) : riderName(r), driverName(d) {}
};

class RideSharingSimulator {
private:
    queue<Rider> riderQueue;
    priority_queue<Driver, vector<Driver>, DriverCompare> driverQueue;
    list<Ride> rideHistory;

public:
    // Add a rider request
    void addRider(const string& name, const string& location) {
        riderQueue.push(Rider(name, location));
        cout << "Rider " << name << " added to queue.\n";
    }

    // Add a driver availability
    void addDriver(const string& name, int distance, double rating) {
        driverQueue.push(Driver(name, distance, rating));
        cout << "Driver " << name << " added to available drivers.\n";
    }

    // Match driver to rider
    void dispatch() {
        if (riderQueue.empty()) {
            cout << "No riders in queue.\n";
            return;
        }
        if (driverQueue.empty()) {
            cout << "No drivers available to dispatch.\n";
            return;
        }
        Rider rider = riderQueue.front();
        riderQueue.pop();

        Driver driver = driverQueue.top();
        driverQueue.pop();

        // Log ride history
        rideHistory.push_back(Ride(rider.name, driver.name));

        cout << "Driver " << driver.name << " dispatched to Rider " << rider.name << ".\n";
    }

    // Show ride history
    void showRideHistory() {
        if (rideHistory.empty()) {
            cout << "No rides yet.\n";
            return;
        }
        cout << "Ride History:\n";
        for (const auto& ride : rideHistory) {
            cout << "Rider: " << ride.riderName << " - Driver: " << ride.driverName << "\n";
        }
    }
};

int main() {
    RideSharingSimulator simulator;

    simulator.addDriver("Pradip", 500, 4.8);
    simulator.addDriver("Sandip", 300, 4.5);
    simulator.addDriver("deepak", 300, 4.7);

    simulator.addRider("John", "Downtown");
    simulator.addRider("Manu", "Airport");

    simulator.dispatch();
    simulator.dispatch();

    simulator.showRideHistory();

    return 0;
}