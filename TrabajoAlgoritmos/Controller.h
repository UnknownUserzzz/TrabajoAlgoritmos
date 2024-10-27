#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ClientDatabase.h"
/*#include "BusList.h"*/
#include"Menu.h"
#include "BST.hpp"
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
		menu->Welcome();

		do {
			if (refresh) {  // Solo redibuja las opciones si es necesario

				Console::ForegroundColor = ConsoleColor::White;
				Console::CursorVisible = false;

				// Actualiza las opciones del menú
				Console::SetCursorPosition(50, 14);  // Ajusta la posición en lugar de mover constantemente
				cout << (option == 1 ? "   > REGISTRARSE <   " : "     REGISTRARSE     ");
				Console::SetCursorPosition(50, 16);
				cout << (option == 2 ? "  > INICIAR SESION < " : "    INICIAR SESION   ");
				Console::SetCursorPosition(50, 18);
				cout << (option == 3 ? "      > SALIR <       " : "        SALIR        ");
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
				Console::ForegroundColor = ConsoleColor::White;

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

		Console::ForegroundColor = ConsoleColor::White;
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
		Console::SetCursorPosition(42, 22);
		cout << "Ingrese usuario: ";
		cin >> user;
		Console::SetCursorPosition(42, 24);
		cout << "Ingrese password: ";

		cin >> password;

		// Registra al cliente con todos los datos inicializados correctamente
		database->registerClient(name, lastname, dni, age, phone, user, password);
	}


	void LoginClient() {
		menu->Fondo();
		menu->Logo();
		string user, password;
		Console::ForegroundColor = ConsoleColor::White;
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

		// Configuración inicial del menú
		menu->Fondo();
		menu->Logo();
		Console::ForegroundColor = ConsoleColor::White;

		// Entrada de la ruta inicial y final
		Console::SetCursorPosition(42, 12);
		cout << "Ingrese la ruta inicial: ";
		cin >> startRoute;
		Console::SetCursorPosition(42, 14);
		cout << "Ingrese la ruta final: ";
		cin >> endRoute;

		// Creación del BST para buses
		BST<Bus> buses([](Bus bus) {}); // No imprimimos nada durante la creación

		// Generar buses aleatorios usando las rutas proporcionadas
		GenerateRandomBuses(buses, startRoute, endRoute);

		// Vector temporal para almacenar punteros a los buses en orden
		vector<Bus*> busList;
		buses.collectInOrder(busList); // Método para recolectar los buses en orden en el vector

		// Iterar sobre los buses uno a uno
		int index = 0;
		bool busSelected = false;
		Bus* selectedBus = nullptr;

		while (index < busList.size() && !busSelected) {
			system("cls"); // Limpiar la pantalla (en Windows)

			// Mostrar la información del bus actual
			cout << "Bus " << (index + 1) << " de " << busList.size() << ":" << endl;
			busList[index]->ToString();
			cout << endl;

			// Mostrar los asientos del bus
			cout << "Asientos disponibles:" << endl;
			busList[index]->displaySeats();
			cout << endl;

			// Esperar la acción del usuario
			cout << "Presione Enter para ver el siguiente bus, ESC para seleccionar este bus, o S para seleccionar un asiento." << endl;
			tecla = _getch();

			// Si se presiona ESC, selecciona el bus actual
			if (tecla == 27) { // Código ASCII para ESC
				selectedBus = busList[index];
				busSelected = true;
			}

			// Avanzar al siguiente bus si se presiona Enter
			if (tecla == 13) { // Código ASCII para Enter
				index++;
			}

			// Selección de asiento si se presiona 'S'
			if (tecla == 'S' || tecla == 's') {
				int seatNumber;
				cout << "Ingrese el número del asiento que desea seleccionar: ";
				cin >> seatNumber;

				if (busList[index]->selectSeat(seatNumber)) {
					cout << "Asiento " << seatNumber << " seleccionado correctamente." << endl;
				}
				else {
					cout << "Asiento no disponible o número inválido." << endl;
				}

				system("pause"); // Esperar a que el usuario presione una tecla
			}
		}

		// Verificar si se seleccionó un bus
		if (selectedBus != nullptr) {
			menu->Fondo();
			menu->Logo();
			Console::ForegroundColor = ConsoleColor::White;

			// Validar si el cliente tiene suficiente saldo para comprar el boleto
			if (client->GetBalance() >= selectedBus->GetPrice()) {
				client->SetBalance(client->GetBalance() - selectedBus->GetPrice());
				client->AddBusData(selectedBus->GetBusNumber(), selectedBus->GetCompany(), selectedBus->GetPrice(), selectedBus->GetSchedule());
				client->AddBusRoute(selectedBus->GetBusNumber(), startRoute, endRoute);
				database->saveClientsToFile();
				Console::SetCursorPosition(42, 22);
				cout << "Boleto comprado con éxito.";
			}
			else {
				Console::SetCursorPosition(42, 22);
				cout << "Saldo insuficiente.";
			}
		}
		else {
			Console::SetCursorPosition(42, 22);
			cout << "No se seleccionó ningún bus.";
		}
	}


	void GenerateRandomBuses(BST<Bus>& buses, string startRoute, string endRoute) {
		srand(time(0));
		int numBuses = rand() % 7 + 10; // Genera entre 10 y 16 buses
		for (int i = 0; i < numBuses; i++) {
			int busNumber = rand() % 100 + 1;
			string company = GenerateRandomCompany();
			int price = rand() % 31 + 30; // Precio entre 30 y 60
			string schedule = to_string(rand() % 24) + ":00";

			// Crear un nuevo bus con los datos generados
			Bus bus(busNumber, company, price, schedule);
			bus.SetStartRoute(startRoute);
			bus.SetEndRoute(endRoute);

			// Insertar el bus en el BST
			buses.insertar(bus);
		}

		// Mostrar los buses ordenados por precio
		buses.enOrden();
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
			menu->Fondo();  // Llama a Fondo solo una vez
			menu->Logo();   // Llama a Logo solo una vez
			Console::ForegroundColor = ConsoleColor::White;
			Console::SetCursorPosition(42, 12);
			cout << "No han comprado boletos";
			_getch();
		}
		else {
			for (Bus* bus : client->busdata) {
				bus->ToStringData();
				_getch();

			}
		}
	}

	void ShowBalance(Client<int>* client) {
		menu->Fondo();  // Llama a Fondo solo una vez
		menu->Logo();   // Llama a Logo solo una vez
		Console::ForegroundColor = ConsoleColor::White;
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
				Console::ForegroundColor = ConsoleColor::White;

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
						cout << "Seleccione monto de recarga (40, 60, 80): ";
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
			cout << "Ingrese numero de tarjeta: ";
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
					cout << "Seleccione monto de recarga (40, 60, 80): ";
					cin >> amount;

					if (amount == 40 || amount == 60 || amount == 80) {
						client->SetBalance(client->GetBalance() + amount);
						database->saveClientsToFile();  // Guardar cambios
						Console::SetCursorPosition(42, 22);
						cout << "Recarga exitosa.\n";
					}
					else {
						Console::SetCursorPosition(42, 22);
						cout << "Monto no valido.\n";
					}
				}
				catch (exception& e) {
					Console::SetCursorPosition(42, 22);
					cout << "Error al agregar tarjeta o recargar: " << e.what() << endl;
				}
			}
			else {
				Console::SetCursorPosition(42, 22);
				cout << "Datos de la tarjeta no validos.\n";
			}
		}
		else if (option == 3) {
			// Volver al menú anterior
			ClientMenu(client);
		}
	}




};

