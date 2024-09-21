#pragma once
#include <iostream>
#include <sstream>
#include"Menu.h"
using namespace std;

template<typename T>
class InfoCustomer {
protected:
    Menu* menu;
    string ID, Name, Lastname;
    T DNI, Age, Phone;
public:
    InfoCustomer(string ID = "", string Name = "", string Lastname = "", T DNI = 0, T Age = 0, T Phone = 0) {
        this->ID = ID;
        this->Name = Name;
        this->Lastname = Lastname;
        this->DNI = DNI;
        this->Age = Age;
        this->Phone = Phone;
        menu = new Menu();
    }

    ~InfoCustomer() {}

    // Getters y Setters
    void SetName(string Name) { this->Name = Name; }
    void SetLastName(string Lastname) { this->Lastname = Lastname; }
    void SetDNI(T DNI) { this->DNI = DNI; }
    void SetAge(T Age) { this->Age = Age; }
    void SetPhone(T Phone) { this->Phone = Phone; }
    void SetID(string ID) { this->ID = ID; }

    string GetName() { return Name; }
    string GetLastName() { return Lastname; }
    T GetDNI() { return DNI; }
    T GetPhone() { return Phone; }
    T GetAge() { return Age; }
    string GetID() { return ID; }

    void ToString() {
        menu->Fondo();
        menu->Logo();
        Console::BackgroundColor = ConsoleColor(7);
        Console::ForegroundColor = ConsoleColor(0);
        Console::SetCursorPosition(42, 12);
        cout << "            Datos Personales";
        Console::SetCursorPosition(42, 14);
        cout << "ID: " << ID;
        Console::SetCursorPosition(42, 16);
        cout << "Nombre: " << Name;
        Console::SetCursorPosition(42, 18);
        cout << "Apellidos: " << Lastname;
        Console::SetCursorPosition(42, 20);
        cout << "DNI: " << DNI;
        Console::SetCursorPosition(42, 22);
        cout << "Edad: " << Age;
        Console::SetCursorPosition(42, 24);
        cout << "Telefono: " << Phone;
    }
};
