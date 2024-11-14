#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include "Bus.h"
using namespace std;

// Clase para manejar la colección de objetos Bus usando Merge Sort
template<typename T>
class Ordenador {
    typedef function<int(T, T)> Comp; // Función para la comparación de elementos
    vector<T> elementos; // Vector para almacenar los elementos
    void (*procesar)(T); // Puntero a función para procesar elementos
    Comp Comparar;

    // Función auxiliar de Merge Sort
    void mergeSort(int inicio, int fin) {
        if (inicio >= fin) return;

        int medio = inicio + (fin - inicio) / 2;
        mergeSort(inicio, medio);
        mergeSort(medio + 1, fin);
        merge(inicio, medio, fin);
    }

    void merge(int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;
        vector<T> izquierda(n1), derecha(n2);

        for (int i = 0; i < n1; i++) izquierda[i] = elementos[inicio + i];
        for (int i = 0; i < n2; i++) derecha[i] = elementos[medio + 1 + i];

        int i = 0, j = 0, k = inicio;
        while (i < n1 && j < n2) {
            if (Comparar(izquierda[i], derecha[j]) <= 0) {
                elementos[k++] = izquierda[i++];
            }
            else {
                elementos[k++] = derecha[j++];
            }
        }
        while (i < n1) elementos[k++] = izquierda[i++];
        while (j < n2) elementos[k++] = derecha[j++];
    }

public:
    // Constructor
    Ordenador(void(*otroPuntero)(T)) {
        this->procesar = otroPuntero;
        this->Comparar = [](T a, T b) -> int {
            return a.GetPrice() - b.GetPrice(); // Comparación basada en el precio
            };
    }

    Ordenador() {
        this->Comparar = [](T a, T b) -> int {
            return a.GetPrice() - b.GetPrice(); // Comparación basada en el precio
            };
    }

    // Método para insertar un elemento y mantener la lista ordenada
    void insertar(T e) {
        elementos.push_back(e);
        mergeSort(0, elementos.size() - 1); // Ordenar tras cada inserción
    }

    // Método para buscar un elemento en la lista
    bool buscar(T e) {
        for (const auto& elem : elementos) {
            if (Comparar(elem, e) == 0) return true;
        }
        return false;
    }

    // Método para mostrar los buses y permitir seleccionar uno
    T* displayBuses() {
        // Mostrar los buses en orden
        int index = 1;
        for (auto& bus : elementos) {
            cout << index++ << ". ";
            bus.ToString(); // Mostrar información del bus
            cout << endl;
        }

        // Permitir selección del usuario
        int choice;
        cout << "Seleccione el número del bus que desea (0 para cancelar): ";
        cin >> choice;

        if (choice <= 0 || choice > elementos.size()) {
            return nullptr; // No se seleccionó un bus válido
        }

        return &elementos[choice - 1]; // Devuelve el bus seleccionado
    }

    // Método para procesar elementos en orden
    void enOrden() {
        for (auto& elem : elementos) {
            procesar(elem);
        }
    }
    // Método para obtener una referencia al vector de elementos ordenados
    const vector<T>& getBuses() const {
        return elementos;
    }

};
