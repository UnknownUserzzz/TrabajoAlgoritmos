#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ClientDatabase.h"
#include "BusList.h"
#include"Menu.h"
#define ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75
class Controller {
private:
    ClientDatabase<int>* database;
    Menu* menu;
    int option;
    int _option;
    char tecla;
public:
    Controller() {
        database = new ClientDatabase<int>();
        menu = new Menu();
        option = 1;
        _option = 1;
    }
    void MainMenu() {
        bool refresh = true;
        menu->Fondo();  // Llama a Fondo solo una vez
        menu->Logo();   // Llama a Logo solo una vez

        do {
            if (refresh) {  // Solo redibuja las opciones si es necesario
                Console::BackgroundColor = ConsoleColor(7);
                Console::ForegroundColor = ConsoleColor(0);
                Console::CursorVisible = false;

                // Actualiza las opciones del menú
                Console::SetCursorPosition(50, 17);  // Ajusta la posición en lugar de mover constantemente
                cout << (option == 1 ? "   > REGISTRARSE <   " : "     REGISTRARSE     ");
                Console::SetCursorPosition(50, 19);
                cout << (option == 2 ? "  > INICIAR SESION < " : "    INICIAR SESION   ");
                Console::SetCursorPosition(50, 21);
                cout << (option == 3 ? "     > SALIR <       " : "       SALIR        ");
            }

            tecla = _getch();  // Solo cambiar la opción si es necesario
            switch (tecla) {
            case ARRIBA:
                option--;
                if (option < 1) option = 3;
                refresh = true;  // Cambiar el valor para refrescar solo si cambia la opción
                break;
            case ABAJO:
                option++;
                if (option > 3) option = 1;
                refresh = true;
                break;
            default:
                refresh = false;  // No refrescar si no hubo cambio
                break;
            }
        } while (tecla != 13);

        // Manejo de selección
        switch (option) {
        case 1:
            RegisterClient();
            MainMenu();
            break;
        case 2:
            LoginClient();
            MainMenu();
            break;
        case 3:
            exit(0);
        }
    }

    void ClientMenu(Client<int>* client) {
        bool refresh = true;
        menu->Fondo();
        menu->Logo();

        do {
            if (refresh) {
                Console::BackgroundColor = ConsoleColor(7);
                Console::ForegroundColor = ConsoleColor(0);

                // Redibuja solo las opciones del menú de cliente
                Console::SetCursorPosition(42, 12);
                cout << (_option == 1 ? "> Mostrar datos del usuario <" : "  Mostrar datos del usuario  ");
                Console::SetCursorPosition(42, 14);
                cout << (_option == 2 ? "> Comprar Boletos <" : "  Comprar Boletos  ");
                Console::SetCursorPosition(42, 16);
                cout << (_option == 3 ? "> Mostrar boletos comprados <" : "  Mostrar boletos comprados  ");
                Console::SetCursorPosition(42, 18);
                cout << (_option == 4 ? "> Mostrar saldo <" : "  Mostrar saldo  ");
                Console::SetCursorPosition(42, 20);
                cout << (_option == 5 ? "> Recargar saldo <" : "  Recargar saldo  ");
                Console::SetCursorPosition(42, 22);
                cout << (_option == 6 ? "> Salir <" : "  Salir  ");
            }

            tecla = _getch();
            switch (tecla) {
            case ARRIBA:
                _option--;
                if (_option < 1) _option = 6;
                refresh = true;
                break;
            case ABAJO:
                _option++;
                if (_option > 6) _option = 1;
                refresh = true;
                break;
            default:
                refresh = false;
                break;
            }
        } while (tecla != 13);

        // Ejecutar la opción seleccionada
        switch (_option) {
        case 1:
            client->ToString();
            _getch();
            ClientMenu(client);
            break;
        case 2:
            BuyTicket(client);
            _getch();
            ClientMenu(client);
            break;
        case 3:
            ShowBoughtTickets(client);
            _getch();
            ClientMenu(client);
            break;
        case 4:
            ShowBalance(client);
            _getch();
            ClientMenu(client);
            break;
        case 5:
            RechargeBalance(client);
            _getch();
            ClientMenu(client);
            break;
        case 6:
            return;
        }
    }


    void RegisterClient() {
        string name, lastname, user, password;
        int dni, age, phone;
        menu->Fondo();
        menu->Logo();
        Console::BackgroundColor = ConsoleColor(7);
        Console::ForegroundColor = ConsoleColor(0);
        Console::SetCursorPosition(42, 12);
        cout << "Ingrese nombre: ";
        cin >> name;
        Console::SetCursorPosition(42, 14);
        cout << "Ingrese apellido: ";
        cin >> lastname;
        Console::SetCursorPosition(42, 16);
        cout << "Ingrese DNI: ";     
        cin >> dni;
        Console::SetCursorPosition(42, 18);
        cout << "Ingrese edad: ";
      
        cin >> age;
        Console::SetCursorPosition(42, 20);
        cout << "Ingrese telefono: ";
        cin >> phone;
        Console::SetCursorPosition(42,22);
        cout << "Ingrese usuario: ";
        cin >> user;
        Console::SetCursorPosition(42,24);
        cout << "Ingrese password: ";

        cin >> password;

        // Registra al cliente con todos los datos inicializados correctamente
        database->registerClient(name, lastname, dni, age, phone, user, password);
    }


    void LoginClient() {
        menu->Fondo();
        menu->Logo();
        string user, password;
        Console::BackgroundColor = ConsoleColor(7);
        Console::ForegroundColor = ConsoleColor(0);
        Console::SetCursorPosition(42, 12);
        cout << "Ingrese usuario: ";
        cin >> user;
        Console::SetCursorPosition(42, 14);
        cout << "Ingrese password: ";
        cin >> password;

        Client<int>* client = database->findClient(user, password);
        if (client) {
            ClientMenu(client);
        }
        else {
            Console::SetCursorPosition(42, 16);
            cout << "Usuario no encontrado";
            _getch();
        }
    }

   


    void BuyTicket(Client<int>* client) {
        string startRoute, endRoute;
        menu->Fondo();
        menu->Logo();
        Console::BackgroundColor = ConsoleColor(7);
        Console::ForegroundColor = ConsoleColor(0);

        cout << "Ingrese la ruta inicial: ";
        cin >> startRoute;
        cout << "Ingrese la ruta final: ";
        cin >> endRoute;

        BusList<Bus> buses;
        GenerateRandomBuses(buses, startRoute, endRoute);

        buses.displayBuses();

        int busNumber;
        cout << "Ingrese el número de bus para comprar el boleto: ";
        cin >> busNumber;

        Bus* bus = buses.searchBus(busNumber);
        if (bus) {
            if (client->GetBalance() >= bus->GetPrice()) {
                client->SetBalance(client->GetBalance() - bus->GetPrice());
                client->AddBusData(bus->GetBusNumber(), bus->GetCompany(), bus->GetPrice(), bus->GetSchedule());
                client->AddBusRoute(bus->GetBusNumber(), startRoute, endRoute);
                database->saveClientsToFile();
                cout << "Boleto comprado con éxito.\n";
            }
            else {
                cout << "Saldo insuficiente.\n";
            }
        }
        else {
            cout << "Bus no encontrado.\n";
        }
    }

    void GenerateRandomBuses(BusList<Bus>& buses, string startRoute, string endRoute) {
        srand(time(0));
        int numBuses = rand() % 3 + 4;  // Genera entre 4 y 6 buses
        for (int i = 0; i < numBuses; i++) {
            int busNumber = rand() % 100 + 1;
            string company = GenerateRandomCompany();
            int price = rand() % 31 + 30;  // Precio entre 30 y 60
            string schedule = to_string(rand() % 24) + ":00";
            Bus bus(busNumber, company, price, schedule);
            bus.SetStartRoute(startRoute);
            bus.SetEndRoute(endRoute);
            buses.addBus(bus);
        }
    }

    string GenerateRandomCompany() {
        ifstream file("Empresas.txt");
        vector<string> companies;
        string company;
        while (getline(file, company)) {
            companies.push_back(company);
        }
        file.close();
        return companies[rand() % companies.size()];
    }

    void ShowBoughtTickets(Client<int>* client) {
        if (client->busdata.empty()) {
            cout << "No ha comprado boletos.\n";
        }
        else {
            for (Bus* bus : client->busdata) {
                cout << bus->ToStringData();
            }
        }
    }

    void ShowBalance(Client<int>* client) {
        menu->Fondo();  // Llama a Fondo solo una vez
        menu->Logo();   // Llama a Logo solo una vez
        Console::BackgroundColor = ConsoleColor(7);
        Console::ForegroundColor = ConsoleColor(0);
        Console::SetCursorPosition(42, 12);
        cout << "Su saldo actual es: " << client->GetBalance() << " soles.\n";
    }
    void RechargeBalance(Client<int>* client) {
        int option = 1;
        char tecla;
        bool refresh = true;

        // Mostrar fondo y logo una sola vez
        menu->Fondo();
        menu->Logo();

        do {
            if (refresh) {  // Redibuja las opciones del menú si es necesario
                Console::BackgroundColor = ConsoleColor(7);
                Console::ForegroundColor = ConsoleColor(0);

                // Opciones del menú de recarga de saldo
                Console::SetCursorPosition(42, 12);
                cout << (option == 1 ? "> Usar tarjeta existente <" : "  Usar tarjeta existente  ");
                Console::SetCursorPosition(42, 14);
                cout << (option == 2 ? "> Agregar nueva tarjeta <" : "  Agregar nueva tarjeta  ");
                Console::SetCursorPosition(42, 16);
                cout << (option == 3 ? "> Volver <" : "  Volver  ");
            }

            tecla = _getch();  // Captura la tecla presionada
            switch (tecla) {
            case ARRIBA:
                option--;
                if (option < 1) option = 3;
                refresh = true;
                break;
            case ABAJO:
                option++;
                if (option > 3) option = 1;
                refresh = true;
                break;
            default:
                refresh = false;
                break;
            }
        } while (tecla != 13);  // Se sale del bucle cuando se presiona Enter

        // Limpia la pantalla antes de pedir los datos para la opción seleccionada
        for (int i = 12; i <= 16; i++) {  // Borra las opciones anteriores
            Console::SetCursorPosition(42, i);
            cout << string(40, ' ');  // Limpia la línea
        }

        // Recolocar el cursor y manejar las opciones seleccionadas
        Console::SetCursorPosition(42, 12);

        if (option == 1) {
            // Usar tarjeta existente
            if (client->creditData.empty()) {
                Console::SetCursorPosition(42, 12);
                cout << "No tiene tarjetas registradas.\n";
            }
            else {
                int cvv;
                Console::SetCursorPosition(42, 12);
                cout << "Ingrese el CVV de su tarjeta: ";
                cin >> cvv;

                bool cardFound = false;
                for (CreditCard* card : client->creditData) {
                    if (card->GetCVV() == cvv) {
                        Console::SetCursorPosition(42, 14);
                        card->ToString();
                        int amount;
                        Console::SetCursorPosition(42, 20);
                        cout << "Seleccione monto de recarga (40, 60, 80 soles): ";
                        cin >> amount;

                        if (amount == 40 || amount == 60 || amount == 80) {
                            client->SetBalance(client->GetBalance() + amount);
                            database->saveClientsToFile();
                            Console::SetCursorPosition(42, 22);
                            cout << "Recarga exitosa.\n";
                        }
                        else {
                            Console::SetCursorPosition(42, 22);
                            cout << "Monto no válido.\n";
                        }
                        cardFound = true;
                        break;
                    }
                }
                if (!cardFound) {
                    Console::SetCursorPosition(42, 18);
                    cout << "Tarjeta no encontrada.\n";
                }
            }
        }
        else if (option == 2) {
            // Agregar nueva tarjeta
            string type;
            long long number;
            int date, cvv;
            Console::SetCursorPosition(42, 12);
            cout << "Ingrese tipo de tarjeta (VISA/MASTERCARD): ";
            cin >> type;
            Console::SetCursorPosition(42, 14);
            cout << "Ingrese número de tarjeta: ";
            cin >> number;
            Console::SetCursorPosition(42, 16);
            cout << "Ingrese fecha de vencimiento (mm/aa): ";
            cin >> date;
            Console::SetCursorPosition(42, 18);
            cout << "Ingrese CVV: ";
            cin >> cvv;

            if (number > 0 && cvv > 0) {
                try {
                    client->AddCreditCard(type, number, date, cvv);
                    int amount;
                    Console::SetCursorPosition(42, 20);
                    cout << "Seleccione monto de recarga (40, 60, 80 soles): ";
                    cin >> amount;

                    if (amount == 40 || amount == 60 || amount == 80) {
                        client->SetBalance(client->GetBalance() + amount);
                        database->saveClientsToFile();  // Guardar cambios
                        Console::SetCursorPosition(42, 22);
                        cout << "Recarga exitosa.\n";
                    }
                    else {
                        Console::SetCursorPosition(42, 22);
                        cout << "Monto no válido.\n";
                    }
                }
                catch (exception& e) {
                    Console::SetCursorPosition(42, 22);
                    cout << "Error al agregar tarjeta o recargar: " << e.what() << endl;
                }
            }
            else {
                Console::SetCursorPosition(42, 22);
                cout << "Datos de la tarjeta no válidos.\n";
            }
        }
        else if (option == 3) {
            // Volver al menú anterior
            ClientMenu(client);
        }
    }




};

