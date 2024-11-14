#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include"Menu.h"
#include "Seat.hpp"

using namespace std;
class Bus {
private:
    int busNumber;
    string Company;
    int price;
    string schedule;
    string StartRoute;
    string EndRoute;
    Menu* menu;
    vector<Seat> seats; // Lista de asientos en el bus
    int totalSeats; // Número total de asientos en el bus

public:
    Bus()
        : busNumber(0), Company("Unknown"), price(0), schedule("Unknown"), totalSeats(20) {
        // Inicializa los asientos
        for (int i = 1; i <= totalSeats; ++i) {
            seats.emplace_back(Seat(i));
        }
    }
    Bus(int number, const std::string& comp, int pr, const std::string& sched, int seatCount = 20)
        : busNumber(number), Company(comp), price(pr), schedule(sched), totalSeats(seatCount) {
        // Inicializa los asientos
        srand(static_cast<unsigned>(time(0))); // Semilla para números aleatorios
        for (int i = 1; i <= totalSeats; ++i) {
            seats.emplace_back(Seat(i));
        }

        // Ocupa algunos asientos aleatoriamente
        int numOccupied = rand() % (totalSeats / 2); // Ocupa hasta la mitad de los asientos
        for (int i = 0; i < numOccupied; ++i) {
            int randomSeat = rand() % totalSeats;
            seats[randomSeat].setOccupied(true);
        }
    }
    //Para comparar y ordenar los autobuses
    bool operator<(const Bus& other) const {
        return this->price < other.price; // Se puede cambiar el atributo price por busNumber para comparar el numero de bus
    }


    // Getters y setters
    int GetBusNumber() const { return busNumber; }
    std::string GetCompany() const { return Company; }
    int GetPrice() const { return price; }
    std::string GetSchedule() const { return schedule; }
    std::string GetStartRoute() const { return StartRoute; }
    std::string GetEndRoute() const { return EndRoute; }
    void SetStartRoute(const std::string& route) { StartRoute = route; }
    void SetEndRoute(const std::string& route) { EndRoute = route; }

    string ToString() const {
        std::ostringstream oss;
        oss << "Empresa: " << Company << "\n";
        oss << "Numero de bus: " << busNumber << "\n";
        oss << "Precio: " << price << "\n";
        oss << "Horario: " << schedule << "\n";
        return oss.str();
    }

    string ToStringData() const {
        std::ostringstream oss;
        oss << "Ruta: " << StartRoute << " - " << EndRoute << "\n";
        oss << "Empresa: " << Company << "\n";
        oss << "Numero de bus: " << busNumber << "\n";
        oss << "Precio: " << price << "\n";
        oss << "Horario: " << schedule << "\n";
        return oss.str();
    }

    void displaySeats(int startX = 42, int startY = 14, int seatsPerRow = 10) const {
        int currentX = startX;
        int currentY = startY;

        Console::ForegroundColor = ConsoleColor::White;

        for (int i = 0; i < seats.size(); ++i) {
            Console::SetCursorPosition(currentX, currentY);

            if (seats[i].isOccupied()) {
                Console::ForegroundColor = ConsoleColor::Red;  // Color para asiento ocupado
                cout << "[X]";  // Símbolo para asiento ocupado
            }
            else {
                Console::ForegroundColor = ConsoleColor::Green;  // Color para asiento disponible
                cout << "[" << seats[i].getSeatNumber() << "]";  // Muestra el número del asiento si está disponible
            }

            currentX += 4;  // Mueve el cursor horizontalmente para el siguiente asiento

            // Salta a la siguiente fila después de seatsPerRow asientos
            if ((i + 1) % seatsPerRow == 0) {
                currentX = startX;
                currentY += 2;  // Baja el cursor para la siguiente fila de asientos
            }
        }

        Console::ForegroundColor = ConsoleColor::White;  // Restaurar el color original
    }

    // Selecciona un asiento
    bool selectSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats) return false;
        if (seats[seatNumber - 1].isOccupied()) return false;
        seats[seatNumber - 1].setOccupied(true);
        return true;
    }

    // Encuentra el primer asiento disponible
    int findFirstAvailableSeat() const {
        for (const auto& seat : seats) {
            if (!seat.isOccupied()) {
                return seat.getSeatNumber();
            }
        }
        return -1; // No hay asientos disponibles
    }
};
