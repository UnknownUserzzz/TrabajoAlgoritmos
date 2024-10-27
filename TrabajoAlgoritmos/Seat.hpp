#pragma once
#include <iostream>

class Seat {
private:
    int seatNumber;
    bool occupied;

public:
    // Constructor
    Seat(int number) : seatNumber(number), occupied(false) {}

    // Getters y setters
    int getSeatNumber() const { return seatNumber; }
    bool isOccupied() const { return occupied; }
    void setOccupied(bool status) { occupied = status; }

    // Muestra la información del asiento
    void displaySeat() const {
        if (occupied) {
            std::cout << "[X]"; // Asiento ocupado
        }
        else {
            std::cout << "[" << seatNumber << "]"; // Asiento disponible
        }
    }
};
