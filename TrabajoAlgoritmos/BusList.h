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
		Node<T>* temp = head;
		Node<T>* sig;
		while (temp != nullptr) {
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
	T* displayBuses() {
		if (head == nullptr) {  // Verifica si la lista está vacía

			return nullptr;
		}

		Node<T>* temp = head;
		bool escogio = false;
		int tecla;

		while (!escogio) {
			if (temp == nullptr) {
				temp = head; // Reiniciar desde el inicio si llegamos al final
			}

			// Asumiendo que ToString() imprime la información del bus
			temp->data.ToString();

			tecla = _getch(); // Lee la tecla presionada por el usuario

			// Si el usuario presiona 'Esc' (tecla 27), sale del bucle
			if (tecla == 27) {
				escogio = true;
			}
			else {
				// De otra manera, se mueve al siguiente nodo
				temp = temp->next;
			}
		}

		// Retorna la información del bus seleccionado
		return &temp->data;
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


	void sort() {
		if (!head || !head->next) return; // No necesita ordenación si está vacío o tiene un solo nodo

		bool swapped;
		Node<T>* ptr1;
		Node<T>* lptr = nullptr;

		do {
			swapped = false;
			ptr1 = head;

			while (ptr1->next != lptr) {
				// Comparar dos nodos de tipo T
				if (!(ptr1->data < ptr1->next->data)) {
					std::swap(ptr1->data, ptr1->next->data); // Intercambiar los datos si están en el orden incorrecto
					swapped = true;
				}
				ptr1 = ptr1->next;
			}
			lptr = ptr1; // El último nodo ya está en su posición correcta
		} while (swapped);
	}

};