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
    int totalSeats; // N�mero total de asientos en el bus

public:
    Bus(int number, const std::string& comp, int pr, const std::string& sched, int seatCount = 20)
        : busNumber(number), Company(comp), price(pr), schedule(sched), totalSeats(seatCount) {
        // Inicializa los asientos
        for (int i = 1; i <= totalSeats; ++i) {
            seats.emplace_back(Seat(i));
        }
    }
    //Para comparar y ordenar los autobuses
    bool operator<(const Bus& other) const {
        return this->price < other.price; // Se puede cambiar el atributo price por busNumber para comparar el numero de bus
    }

    // Getters y Setters
    int GetBusNumber() { return busNumber; }
    string GetCompany() { return Company; }
    int GetPrice() { return price; }
    string GetSchedule() { return schedule; }
    string GetStartRoute() { return StartRoute; }
    string GetEndRoute() { return EndRoute; }

    void SetBusNumber(int busNumber) { this->busNumber = busNumber; }
    void SetCompany(string Company) { this->Company = Company; }
    void SetPrice(int price) { this->price = price; }
    void SetSchedule(string schedule) { this->schedule = schedule; }
    void SetStartRoute(string StartRoute) { this->StartRoute = StartRoute; }
    void SetEndRoute(string EndRoute) { this->EndRoute = EndRoute; }

    // Mostrar informaci�n del autob�s
    void ToString() {
        menu->Fondo();
        menu->Logo();
        Console::ForegroundColor = ConsoleColor::White;
        Console::SetCursorPosition(42, 12);
        cout << "Empresa: " << Company;
        Console::SetCursorPosition(42, 14);
        cout << "Numero de bus: " << busNumber;
        Console::SetCursorPosition(42, 16);
        cout << "Precio: " << price;
        Console::SetCursorPosition(42, 18);
        cout << "Horario: " << schedule;
        Console::SetCursorPosition(42, 24);
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "PRESIONA ENTER PARA SEGUIR BUSCANDO....";
        Console::SetCursorPosition(42, 26);
        cout << "PRESIONA ESC PARA ELEGIR EL BOLETO DE BUS...";
    }

    void ToStringData() {
        menu->Fondo();
        menu->Logo();
        Console::ForegroundColor = ConsoleColor::White;
        Console::SetCursorPosition(42, 12);
        cout << "Ruta: " << StartRoute << " - " << EndRoute;
        Console::SetCursorPosition(42, 14);
        cout << "Empresa: " << Company;
        Console::SetCursorPosition(42, 16);
        cout << "Numero de bus: " << busNumber;
        Console::SetCursorPosition(42, 18);
        cout << "Precio: " << price;
        Console::SetCursorPosition(42, 20);
        cout << "Horario: " << schedule;
       
    }
    // Muestra los asientos
    void displaySeats() const {
        for (const auto& seat : seats) {
            seat.displaySeat();
            std::cout << " "; // Espacio entre asientos
        }
        std::cout << "\n";
    }

    // Selecciona un asiento
    bool selectSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats) return false;
        if (seats[seatNumber - 1].isOccupied()) return false;
        seats[seatNumber - 1].setOccupied(true);
        return true;
    }
};
