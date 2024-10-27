#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include "Bus.h"
using namespace std;

// Nodo para almacenar objetos de la clase Bus
template<typename T>
class Nodo {
public:
    T elemento;
    Nodo* izq;
    Nodo* der;
    Nodo(const T& elem) : elemento(elem), izq(nullptr), der(nullptr) {}
	Nodo() : izq(nullptr), der(nullptr) {}
};

// Clase BST para manejar objetos Bus
template<typename T>
class BST {
    typedef function<int(T, T)> Comp; // Función para la comparación de elementos
    Nodo<T>* raiz;
    void (*procesar)(T); // Puntero a función para procesar elementos
    Comp Comparar;

private:
    // Función recursiva para eliminar un elemento del árbol
    bool _eliminar(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) return false;
        int r = Comparar(nodo->elemento, e);
        if (r < 0) return _eliminar(nodo->der, e);
        if (r > 0) return _eliminar(nodo->izq, e);

        if (nodo->der == nullptr && nodo->izq == nullptr) {
            delete nodo;
            nodo = nullptr;
            return true;
        }
        if (nodo->izq == nullptr) {
            Nodo<T>* temp = nodo;
            nodo = nodo->der;
            delete temp;
            return true;
        }
        if (nodo->der == nullptr) {
            Nodo<T>* temp = nodo;
            nodo = nodo->izq;
            delete temp;
            return true;
        }

        Nodo<T>* aux = nodo->der;
        while (aux->izq != nullptr) {
            aux = aux->izq;
        }
        nodo->elemento = aux->elemento;
        return _eliminar(nodo->der, aux->elemento);
    }

    // Función recursiva para buscar un elemento en el árbol
    bool _buscar(Nodo<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        int r = Comparar(nodo->elemento, e);
        if (r == 0) return true;
        if (r < 0) return _buscar(nodo->der, e);
        return _buscar(nodo->izq, e);
    }

    // Función recursiva para insertar un elemento en el árbol
    bool _insertar(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new Nodo<T>(e); // Usar el constructor que inicializa 'elemento'
            return true;
        }
        int r = Comparar(nodo->elemento, e);
        if (r == 0) return false; // Ya existe el elemento
        if (r < 0) return _insertar(nodo->der, e);
        return _insertar(nodo->izq, e);
    }

    // Función recursiva para recorrer el árbol en orden
    void _enOrden(Nodo<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        procesar(nodo->elemento);
        _enOrden(nodo->der);
    }

    // Función auxiliar recursiva para recolectar buses en un vector en orden
    void _recogerBuses(Nodo<T>* nodo, vector<T*>& busList) {
        if (nodo == nullptr) return;
        _recogerBuses(nodo->izq, busList); // Recorrer izquierda
        busList.push_back(&(nodo->elemento)); // Guardar puntero al bus
        _recogerBuses(nodo->der, busList); // Recorrer derecha
    }
    void _collectInOrder(Nodo<T>* nodo, vector<T*>& busList) {
        if (nodo == nullptr) return;
        _collectInOrder(nodo->izq, busList); // Recorrer izquierda
        busList.push_back(&(nodo->elemento)); // Agregar el elemento al vector
        _collectInOrder(nodo->der, busList); // Recorrer derecha
    }

public:
    // Constructor
    BST(void(*otroPuntero)(T)) {
        this->procesar = otroPuntero;
        this->Comparar = [](T a, T b) -> int {
            return a.GetPrice() - b.GetPrice(); // Comparación basada en el precio
            };
        raiz = nullptr;
    }
    BST() {
        this->Comparar = [](T a, T b) -> int {
            return a.GetPrice() - b.GetPrice(); // Comparación basada en el precio
            };
        raiz = nullptr;
    } 

    // Método para mostrar los buses y permitir seleccionar uno
    T* displayBuses() {
        vector<T*> busList; // Contenedor temporal para almacenar punteros a los buses
        _recogerBuses(raiz, busList); // Recolectar los buses en orden en un vector

        // Mostrar los buses recolectados
        int index = 1;
        for (auto& bus : busList) {
            cout << index++ << ". ";
            bus->ToString(); // Mostrar información del bus
            cout << endl;
        }

        // Permitir selección del usuario
        int choice;
        cout << "Seleccione el número del bus que desea (0 para cancelar): ";
        cin >> choice;

        if (choice <= 0 || choice > busList.size()) {
            return nullptr; // No se seleccionó un bus válido
        }

        return busList[choice - 1]; // Devuelve el bus seleccionado
    }

    // Métodos públicos del BST
    bool insertar(T e) {
        return _insertar(raiz, e);
    }

    void enOrden() {
        _enOrden(raiz);
    }

    bool buscar(T e) {
        return _buscar(raiz, e);
    }

    bool eliminar(T e) {
        return _eliminar(raiz, e);
    }
    bool recogerBuses(T e) {
        return _recogerBuses(raiz, e);
    }
    void collectInOrder(vector<T*>& busList) {
        _collectInOrder(raiz, busList);
    }
};
