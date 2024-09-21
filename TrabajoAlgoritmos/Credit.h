#pragma once
#include <iostream>
#include <sstream>
#include"Menu.h"
using namespace std;

class CreditCard {
protected:
    string Type;
    long long Number;
    int Date, CVV;
    Menu* menu;
public:
    CreditCard(string Type = "", long long Number = 0, int Date = 0, int CVV = 0) {
        this->Type = Type;
        this->Number = Number;
        this->Date = Date;
        this->CVV = CVV;
        menu = new Menu();
    }

    ~CreditCard() {}

    // Getters y Setters
    void SetType(string Type) { this->Type = Type; }
    void SetNumber(long long Number) { this->Number = Number; }
    void SetCVV(int CVV) { this->CVV = CVV; }
    void SetDate(int Date) { this->Date = Date; }

    string GetType() { return Type; }
    long long GetNumber() { return Number; }
    int GetCVV() { return CVV; }
    int GetDate() { return Date; }

    void ToString() {
        menu->Fondo();
        menu->Logo();
        Console::BackgroundColor = ConsoleColor(7);
        Console::ForegroundColor = ConsoleColor(0);
        Console::SetCursorPosition(42, 14);
        cout << "            Datos de la tarjeta";
        Console::SetCursorPosition(42, 15);
        cout << "Tipo: " << Type;
        Console::SetCursorPosition(42, 16);
        cout << "Numero: " << Number;
        Console::SetCursorPosition(42, 17);
        cout << "Fecha de Vencimiento: " << Date;
        Console::SetCursorPosition(42, 18);
        cout << "CVV: " << CVV;

        ;
    }
};
