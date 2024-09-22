#pragma once
#include <iostream>
#include <sstream>
#include"Menu.h"
using namespace std;
//hola
class Bus {
private:
    int busNumber;
    string Company;
    int price;
    string schedule;
    string StartRoute;
    string EndRoute;
    Menu* menu;

public:
    Bus(int busNumber=0, string Company="", int price =0, string schedule="") {
        this->busNumber = busNumber;
        this->Company = Company;
        this->price = price;
        this->schedule = schedule;
        StartRoute = "";
        EndRoute = "";
        menu = new Menu();
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

    // Mostrar información del autobús
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
};
