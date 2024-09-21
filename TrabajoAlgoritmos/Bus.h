#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class Bus {
private:
    int busNumber;
    string Company;
    int price;
    string schedule;
    string StartRoute;
    string EndRoute;

public:
    Bus(int busNumber=0, string Company="", int price =0, string schedule="") {
        this->busNumber = busNumber;
        this->Company = Company;
        this->price = price;
        this->schedule = schedule;
        StartRoute = "";
        EndRoute = "";
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
    string ToString() {
        ostringstream print;
        print << "\nEmpresa: " << Company << endl;
        print << "Numero de bus: " << busNumber << endl;
        print << "Precio: " << price << endl;
        print << "Horario: " << schedule << endl;
        return print.str();
    }

    string ToStringData() {
        ostringstream print;
        print << "\nRuta: " << StartRoute << " - " << EndRoute << endl;
        print << "Empresa: " << Company << endl;
        print << "Numero de bus: " << busNumber << endl;
        print << "Precio: " << price << endl;
        print << "Horario: " << schedule << endl;
        return print.str();
    }
};
