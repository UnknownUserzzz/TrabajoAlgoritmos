#pragma once
#include "InfoCustomer.h"
#include "Credit.h"
#include "Bus.h"
#include <vector>
#include <sstream>
using namespace std;

template<typename T>
class Client {
private:
    T balance;
    string password;
    string user;

public:
    InfoCustomer<T>* data;
    vector<CreditCard*> creditData;
    vector<Bus*> busdata;

public:
    Client(string name, string lastname, T DNI, T age, T phone, string user, string password) {
        data = new InfoCustomer<T>(user, name, lastname, DNI, age, phone); 
        this->user = user;
        this->password = password;
        balance = 0;
    }
    ~Client() {
    }

    void ToString() {
        
      data->ToString();
        
    }

    // Getters y setters
    string GetUser() { return user; }
    string GetPassword() { return password; }
    T GetBalance() { return balance; }

    void SetBalance(T balance) { this->balance = balance; }
    void SetUser(string user) { this->user = user; }
    void SetPassword(string password) { this->password = password; }


    void AddCreditCard(string Type, long long Number, int Date, int CVV) {
            creditData.push_back(new CreditCard(Type, Number, Date, CVV));
    }

    void AddBusData(int busNumber, string Company, int prize, string schedule) {
        busdata.push_back(new Bus(busNumber, Company, prize, schedule));
    }

    void AddBusRoute(int busNumber, string StartRoute, string EndRoute) {
        if(busdata.size()>0){
        for (int i = 0;i<busdata.size();i++) {
            if (busdata[i]->GetBusNumber() == busNumber) {
                busdata[i]->SetStartRoute(StartRoute);
                busdata[i]->SetEndRoute(EndRoute);
                break;
            }
        }
        }
    }
};
