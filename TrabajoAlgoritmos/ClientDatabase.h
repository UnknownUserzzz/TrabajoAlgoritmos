#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Client.h"

using namespace std;

template<typename T>
class ClientDatabase {
private:
    vector<Client<T>> clients;
    vector<Client<int>*> clientInt;

    // Cargar clientes desde el archivo
    void loadClientsFromFile() {
        ifstream file("clientes.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line == "CLIENT") {
                    string name, lastname, user, password, type;
                    T dni, age, phone, balance;

                    // Leer datos del cliente
                    file >> user >> password >> name >> lastname >> dni >> age >> phone >> balance;
                    file.ignore(); // Ignorar el salto de línea después de los datos del cliente
                    Client<T> client(name, lastname, dni, age, phone, user, password);
                    client.SetBalance(balance);

                    // Leer tarjetas de crédito
                    while (getline(file, line) && line != "ENDCARD") {
                        stringstream ss(line);
                        long long number;
                        int date, cvv;
                        ss >> type >> number >> date >> cvv;
                        client.AddCreditCard(type, number, date, cvv);
                    }

                    // Leer boletos (buses)
                    string busLine; // Declara `busLine` aquí antes de su uso
                    while (getline(file, busLine) && busLine != "ENDBUS") {
                        stringstream ss(busLine);
                        string startRoute, endRoute, schedule, company;
                        int busNumber, prize;

                        ss >> startRoute >> endRoute >> busNumber >> prize >> schedule;
                        getline(ss, company); // Obtener el resto de la línea como el nombre de la compañía

                        // Verificar que `company` no esté vacío antes de usar `substr`
                        if (!company.empty()) {
                            company = company.substr(1); // Eliminar el espacio inicial
                        }
                        else {
                            cerr << "Error: El nombre de la compañía está vacío en la línea: " << busLine << endl;
                            continue;
                        }

                        client.AddBusData(busNumber, company, prize, schedule);
                        client.AddBusRoute(busNumber, startRoute, endRoute);
                    }
                    clients.push_back(client);
                }
            }
            file.close();
        }
        else {
            cout << "No se pudo abrir el archivo para cargar los datos." << endl;
        }
    }
public:
    ClientDatabase() {
        loadClientsFromFile();
    }

    vector<Client<int>*> getAllClients() const {
        return clientInt;
    }

    void registerClient(string name, string lastname, T DNI, T age, T phone, string user, string password) {
        Client<T> newClient(name, lastname, DNI, age, phone, user, password);
        clients.push_back(newClient);
        saveClientsToFile();
    }

    Client<T>* findClient(string user, string password) {
        for (auto& client : clients) {
            if (client.GetUser() == user && client.GetPassword() == password) {
                return &client;
            }
        }
        return nullptr;
    }

    // Guardar clientes en el archivo en un formato más legible
    void saveClientsToFile() {
        ofstream file("clientes.txt");
        if (file.is_open()) {
            for (auto& client : clients) {
                // Guardar datos del cliente con encabezado "CLIENT"
                file << "CLIENT" << endl;
                file << client.GetUser() << " "
                    << client.GetPassword() << " "
                    << client.data->GetName() << " "
                    << client.data->GetLastName() << " "
                    << client.data->GetDNI() << " "
                    << client.data->GetAge() << " "
                    << client.data->GetPhone() << " "
                    << client.GetBalance() << endl;

                // Guardar tarjetas de crédito con encabezado "CREDIT_CARD"
                file << "CREDIT_CARD" << endl;
                for (auto& card : client.creditData) {
                    file << card->GetType() << " "
                        << card->GetNumber() << " "
                        << card->GetDate() << " "
                        << card->GetCVV() << endl;
                }
                file << "ENDCARD" << endl;

                // Guardar boletos (buses) con encabezado "BUS_TICKET"
                file << "BUS_TICKET" << endl;
                for (auto& bus : client.busdata) {
                    file << bus->GetStartRoute() << " "
                        << bus->GetEndRoute() << " "
                        << bus->GetBusNumber() << " "
                        << bus->GetPrice() << " "
                        << bus->GetSchedule() << " "
                        << bus->GetCompany() << endl;
                }
                file << "ENDBUS" << endl;  // Delimitador para los buses
            }
            file.close();
        }
        else {
            cout << "No se pudo abrir el archivo para guardar los datos." << endl;
        }
    }
};
