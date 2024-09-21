#pragma once
#include "Node.h"
#include "Bus.h"
template <typename T>
class BusList {
private:
    Node<T>* head;

public:
    BusList() {
        head = nullptr;
    }
    ~BusList() {
        Node<T>* temp =head;
        Node<T>* sig;
        while (temp!=nullptr) {
            sig = temp->next;
            delete temp;
            temp = sig;
        }
    }
    int size() const {
        int count = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    T* getBus(int index) {
        Node<T>* temp = head;
        for (int i = 0; i < index && temp != nullptr; i++) {
            temp = temp->next;
        }
        return temp != nullptr ? &temp->data : nullptr;
    }
    // Método para agregar un nuevo autobús al final de la lista
    void addBus(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Método para mostrar todos los autobuses en la lista
    void displayBuses() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout<<temp->data.ToString();
            temp = temp->next;
        }
    }

    // Método para buscar un autobús por número
    T* searchBus(int busNumber) const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data.GetBusNumber() == busNumber) {
                return &temp->data;
            }
            temp = temp->next;
        }
        return nullptr;  // No se encontró el autobús
    }

    // Método para eliminar un autobús por número
    void removeBus(int busNumber) {
        if (head == nullptr) return;

        if (head->data.GetBusNumber() == busNumber) {
            Node<T>* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data.GetBusNumber() != busNumber) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {
            Node<T>* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }
};