#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class SeatType {
    virtual float getPrice() = 0;
}

class Seat {
    string seatNumber;
    bool isBooked;
    SeatType seatType;
};

class Movie {
    string id;
    string title;
    string director;
    int duration; // in minutes
    float rating; // out of 10
    vector<string> posterUrls;
public:
    string getId() {
        return id;
    }

};

class Show {
    string movieId;
    string starttime;
    Auditorium audi;
    float standardPrice;
    vector<Seat> bookedSeats;
};

class Auditorium {
    vector<Seat> seats;
    unordered_map<string, Show> dateShowMap;
};

class Theatre {
    string id;
    string name;
    string location;
    vector<Auditorium> auditoriums;
};

class City {
    string name;
    vector<Theatre> theatres;
};

class ShowPlanner {

};

int main() {

} 