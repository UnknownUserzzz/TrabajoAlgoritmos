#pragma once
#include "Node.h"
#include "Bus.h"
#include "BubbleSort.h"
template <typename T>
class BusList {
private:
    Node<T>* head;
    bool escogio;
    char tecla;
public:
    BusList() {
        head = nullptr;
        escogio = false;
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
    // M�todo para agregar un nuevo autob�s al final de la lista
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

    // M�todo para mostrar todos los autobuses en la lista
    T* displayBuses() {
        Node<T>* temp = head;
        while (!escogio) {
            if (temp == nullptr) { temp = head; }
            temp->data.ToString();
            temp = temp->next;
            tecla=_getch();
            if (tecla == 27) { escogio = true; }
        }
        return &temp->data;
    }

    // M�todo para buscar un autob�s por n�mero
    T* searchBus(int busNumber) const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data.GetBusNumber() == busNumber) {
                return &temp->data;
            }
            temp = temp->next;
        }
        return nullptr;  // No se encontr� el autob�s
    }

    // M�todo para eliminar un autob�s por n�mero
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


    void sort() {
        if (!head || !head->next) return; // No necesita ordenaci�n si est� vac�o o tiene un solo nodo

        bool swapped;
        Node<T>* ptr1;
        Node<T>* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                // Comparar dos nodos de tipo T
                if (!(ptr1->data < ptr1->next->data)) {
                    std::swap(ptr1->data, ptr1->next->data); // Intercambiar los datos si est�n en el orden incorrecto
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1; // El �ltimo nodo ya est� en su posici�n correcta
        } while (swapped);
    }

};