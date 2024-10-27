#pragma once
#include <iostream>

// ANSI color codes
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

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

    // Muestra la información del asiento con colores
    void displaySeat() const {
        if (occupied) {
            std::cout << ANSI_COLOR_RED << "[X]" << ANSI_COLOR_RESET; // Asiento ocupado en rojo
        }
        else {
            std::cout << ANSI_COLOR_GREEN << "[" << seatNumber << "]" << ANSI_COLOR_RESET; // Asiento disponible en verde
        }
    }
};
