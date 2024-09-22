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

    
    void loadClientsFromFile() {
        ifstream file("clientes.txt");
        if (file.is_open()) {
            string name, lastname, user, password, type;
            T dni, age, phone, balance;
            long long number;
            int date, cvv;
            int busNumber, prize;
            string company, schedule, startRoute, endRoute;

          
            while (file >> user >> password >> name >> lastname >> dni >> age >> phone >> balance) {
                Client<T> client(name, lastname, dni, age, phone, user, password);
                client.SetBalance(balance);

                
                string endcard;
                while (file >> type) {
                    if (type == "ENDCARD") {
                        break;
                    }
                    file >> number >> date >> cvv;
                    client.AddCreditCard(type, number, date, cvv);
                }

                
                // Cargar boletos (buses)
                string busLine;
                while (getline(file, busLine)) {
                    if (busLine == "ENDBUS") {
                        break;  // Fin de la sección de buses para este cliente
                    }

                    stringstream ss(busLine);
                    string startRoute, endRoute, schedule, company;
                    int busNumber = -1, prize = -1;

                   
                    // Leer las rutas, busNumber, prize y schedule utilizando getline para evitar problemas con espacios
                    if (!(ss >> startRoute >> endRoute >> busNumber >> prize)) {
                        continue;
                    }

                    // Leer el horario
                    if (!(ss >> schedule)) {
                        cerr << "Error al leer el horario, formato incorrecto en la línea: " << busLine << endl;
                        continue;
                    }

                    // Leer el resto de la línea para obtener el nombre completo de la compañía
                    getline(ss, company);
                    if (company.empty()) {
                        cerr << "Error: El nombre de la compañía está vacío en la línea: " << busLine << endl;
                        continue;
                    }

                    // Eliminar el posible espacio inicial que deja getline
                    company = company.substr(1);

                    // Verificar si todos los campos están presentes y válidos
                    if (!startRoute.empty() && !endRoute.empty() && !company.empty() && busNumber >= 0 && prize >= 0) {
                        client.AddBusData(busNumber, company, prize, schedule);
                        client.AddBusRoute(busNumber, startRoute, endRoute);
                   

                    }
                    else {
                        cerr << "Error: Campos vacíos o inválidos en el boleto leído. Línea: " << busLine << endl;
                    }
                }
                clients.push_back(client);  
            }

            file.close();
        }
        else {
            cout << "";
        }
    }

public:
    ClientDatabase() {
        loadClientsFromFile();
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

    
  void saveClientsToFile() {
    ofstream file("clientes.txt");
    if (file.is_open()) {
        for (auto& client : clients) {
            // Guardar datos del cliente
            file << client.GetUser() << " "
                 << client.GetPassword() << " "
                 << client.data->GetName() << " "
                 << client.data->GetLastName() << " "
                 << client.data->GetDNI() << " "
                 << client.data->GetAge() << " "
                 << client.data->GetPhone() << " "
                 << client.GetBalance() << endl;

            // Guardar tarjetas de crédito
            for (auto& card : client.creditData) {
                file << card->GetType() << " "
                     << card->GetNumber() << " "
                     << card->GetDate() << " "
                     << card->GetCVV() << endl;
            }
            file << "ENDCARD" << endl;

            // Guardar boletos (buses)
            for (auto& bus : client.busdata) {
                file << bus->GetStartRoute() << " "
                     << bus->GetEndRoute() << " "
                     << bus->GetBusNumber() << " "
                     << bus->GetPrice() << " "
                     << bus->GetSchedule() << " "
                     << bus->GetCompany() << endl; // Asegúrate de guardar todos los datos correctamente
            }
            file << "ENDBUS" << endl;  // Delimitador para los buses
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo para guardar los datos." << endl;
    }
}

};
