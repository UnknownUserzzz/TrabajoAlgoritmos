#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ClientDatabase.h"
#include <unordered_set>
#include <set>
/*#include "BusList.h"*/
#include"Menu.h"
#include "Ordenador.h"
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
	vector<Bus> allBuses;
public:
	Controller() {
		database = new ClientDatabase<int>();
		menu = new Menu();
		option = 1;
		_option = 1;
		GenerateRandomBuses(allBuses);

	}
	void MainMenu() {
		bool refresh = true;
		menu->Fondo();  // Llama a Fondo solo una vez
		menu->Logo();   // Llama a Logo solo una vez
		menu->Welcome();

		do {
			if (refresh) {
				Console::ForegroundColor = ConsoleColor::White;
				Console::CursorVisible = false;

				Console::SetCursorPosition(50, 14);
				cout << (option == 1 ? "   > REGISTRARSE <   " : "     REGISTRARSE     ");
				Console::SetCursorPosition(50, 16);
				cout << (option == 2 ? "  > INICIAR SESION < " : "    INICIAR SESION   ");
				Console::SetCursorPosition(50, 18);
				cout << (option == 3 ? "      > SALIR <       " : "        SALIR        ");
			}

			tecla = _getch();
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
		} while (tecla != 13);

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

	// Menú de administrador
	void AdminMenu() {
		int adminOption = 1;
		bool refresh = true;
		menu->Fondo();
		menu->Logo();

		do {
			if (refresh) {
				Console::ForegroundColor = ConsoleColor::White;
				Console::SetCursorPosition(42, 12);
				cout << (adminOption == 1 ? "> Listar Buses <" : "  Listar Buses  ");
				Console::SetCursorPosition(42, 14);
				cout << (adminOption == 2 ? "> Listar Clientes <" : "  Listar Clientes  ");
				Console::SetCursorPosition(42, 16);
				cout << (adminOption == 3 ? "> Salir <" : "  Salir  ");
			}

			tecla = _getch();
			switch (tecla) {
			case ARRIBA:
				adminOption--;
				if (adminOption < 1) adminOption = 3;
				refresh = true;
				break;
			case ABAJO:
				adminOption++;
				if (adminOption > 3) adminOption = 1;
				refresh = true;
				break;
			default:
				refresh = false;
				break;
			}
		} while (tecla != 13);

		switch (adminOption) {
		case 1:
			ListBuses();
			AdminMenu();
			break;
		case 2:
			ListClients();
			AdminMenu();
			break;
		case 3:
			return;
		}
	}

	set<std::pair<std::string, std::string>> GetAvailableRoutes() {
		std::set<std::pair<std::string, std::string>> routes;
		for (const auto& bus : allBuses) { // allBuses contiene todos los buses generados
			routes.emplace(bus.GetStartRoute(), bus.GetEndRoute());
		}
		return routes;
	}

	void ListBuses() {
		menu->Fondo();
		menu->Logo();
		Console::ForegroundColor = ConsoleColor::White;

		std::vector<Bus> busList; // Cambia a std::vector<Bus>
		GenerateRandomBuses(busList); // Llama a GenerateRandomBuses con un vector de buses

		Console::SetCursorPosition(42, 10);
		cout << "Lista de Buses:";

		for (size_t i = 0; i < busList.size(); ++i) {
			Console::SetCursorPosition(42, 12 + static_cast<int>(i) * 2);
			cout << "Nombre del Bus: " << busList[i].GetBusNumber()
				<< ", Precio: " << busList[i].GetPrice();
		}

		_getch();
	}

	// Listar clientes
	void ListClients() {
		menu->Fondo();
		menu->Logo();
		Console::ForegroundColor = ConsoleColor::White;

		// Obtener todos los clientes de la base de datos
		auto clients = database->getAllClients(); // Método getAllClients implementado en ClientDatabase

		Console::SetCursorPosition(42, 10);
		cout << "Lista de Clientes:";

		for (size_t i = 0; i < clients.size(); ++i) {
			Console::SetCursorPosition(42, 12 + static_cast<int>(i) * 2);
			cout << i + 1 << ". " << clients[i]->GetUser(); // Mostramos el nombre del cliente
		}

		int clientIndex;
		Console::SetCursorPosition(42, 14 + static_cast<int>(clients.size()) * 2);
		cout << "Seleccione el número de cliente para ver detalles (0 para salir): ";
		cin >> clientIndex;

		if (clientIndex > 0 && clientIndex <= static_cast<int>(clients.size())) {
			Client<int>* selectedClient = clients[clientIndex - 1];
			ShowClientDetails(selectedClient);
		}
	}
	// Mostrar detalles del cliente
	void ShowClientDetails(Client<int>* client) {
		menu->Fondo();
		menu->Logo();
		Console::ForegroundColor = ConsoleColor::White;
		Console::SetCursorPosition(42, 12);
		client->ToString();
		_getch();
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

		if (user == "admin" && password == "admin") {
			AdminMenu();  // Mostrar menú de administración
		}
		else {
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
	}
	void LimpiarArea(int x1, int y1, int x2, int y2) {
		// Borra un área específica de la pantalla, de (x1, y1) a (x2, y2)
		for (int y = y1; y <= y2; y++) {
			for (int x = x1; x <= x2; x++) {
				Console::SetCursorPosition(x, y);
				cout << " "; // Borra el contenido en la posición actual
			}
		}
	}

	void printWithinBounds(const std::string& text, int startX, int startY, int maxWidth, int maxLines) {
		std::istringstream words(text);
		std::string word;
		int currentX = startX;
		int currentY = startY;
		int lineCount = 0;

		while (words >> word) {
			if (currentX + word.size() >= startX + maxWidth) {  // Cambiar de línea si se excede el ancho
				currentY++;
				lineCount++;
				currentX = startX;
				if (lineCount >= maxLines) break;  // No exceder el número máximo de líneas permitido
			}
			Console::SetCursorPosition(currentX, currentY);
			cout << word << " ";
			currentX += word.size() + 1;  // Espacio entre palabras
		}
	}

	void BuyTicket(Client<int>* client) {
		menu->Fondo();
		menu->Logo();

		auto availableRoutes = GetAvailableRoutes();
		int index = 1;
		Console::SetCursorPosition(42, 10);
		cout << "Rutas disponibles:" << endl;
		for (const auto& route : availableRoutes) {
			Console::SetCursorPosition(42, 10 + index);
			cout << index << ". " << route.first << " -> " << route.second;
			index++;
		}

		int routeChoice;
		Console::SetCursorPosition(42, 10 + index + 2);
		cout << "Seleccione el número de la ruta que desea: ";
		cin >> routeChoice;

		if (routeChoice < 1 || routeChoice > static_cast<int>(availableRoutes.size())) {
			Console::SetCursorPosition(42, 10 + index + 4);
			cout << "Selección no válida.";
			_getch();
			return;
		}

		for (int y = 10; y <= 30; y++) {
			Console::SetCursorPosition(42, y);
			cout << string(60, ' ');
		}

		auto selectedRoute = std::next(availableRoutes.begin(), routeChoice - 1);
		std::string startRoute = selectedRoute->first;
		std::string endRoute = selectedRoute->second;

		std::vector<Bus> busList = SearchBusesByRoute(startRoute, endRoute);

		if (busList.empty()) {
			Console::SetCursorPosition(42, 12);
			cout << "No se encontraron buses para la ruta seleccionada.";
			_getch();
			return;
		}

		int busIndex = 0;
		bool busSelected = false;
		Bus* selectedBus = nullptr;

		while (busIndex < busList.size() && !busSelected) {
			for (int y = 10; y <= 20; y++) {
				Console::SetCursorPosition(42, y);
				cout << string(60, ' ');
			}

			Console::SetCursorPosition(42, 10);
			cout << "Bus " << (busIndex + 1) << " de " << busList.size() << ":" << endl;

			// Usa printWithinBounds para imprimir detalles del bus dentro de los límites
			std::string busDetails = busList[busIndex].ToString();
			printWithinBounds(busDetails, 42, 12, 60, 6);  // Ajusta los parámetros según la interfaz


			Console::SetCursorPosition(42, 26);
			cout << "Presione Enter para ver el siguiente bus, ESC para seleccionar este bus, o S para seleccionar un asiento." << endl;
			tecla = _getch();

			if (tecla == 27) { // Código ASCII para ESC
				selectedBus = &busList[busIndex];
				busSelected = true;
			}

			if (tecla == 13) { // Código ASCII para Enter
				busIndex++;
			}

			if (tecla == 'S' || tecla == 's') {
				int seatNumber;
				busList[busIndex].displaySeats(42, 18);  // Muestra los asientos dentro del margen
				Console::SetCursorPosition(42, 28);
				cout << "Ingrese el número del asiento que desea seleccionar: ";
				cin >> seatNumber;

				if (busList[busIndex].selectSeat(seatNumber)) {
					Console::SetCursorPosition(42, 30);
					cout << "Asiento " << seatNumber << " seleccionado correctamente." << endl;
				}
				else {
					Console::SetCursorPosition(42, 30);
					cout << "Asiento no disponible o número inválido." << endl;
				}

				system("pause");
			}
		}

		if (selectedBus != nullptr) {
			menu->Fondo();
			menu->Logo();
			Console::ForegroundColor = ConsoleColor::White;

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

	void GenerateRandomBuses(std::vector<Bus>& buses) {
		srand(static_cast<unsigned>(time(0)));

		std::vector<std::string> cities = {
			"Lima", "Arequipa", "Cusco", "Trujillo", "Chiclayo",
			"Piura", "Iquitos", "Tacna", "Puno", "Chimbote",
			"Huancayo", "Ayacucho", "Juliaca", "Cajamarca", "Huaraz"
		};

		int numBuses = rand() % 7 + 10; // Genera entre 10 y 16 buses
		std::unordered_set<int> uniqueBusNumbers;

		for (int i = 0; i < numBuses; i++) {
			int busNumber;
			do {
				busNumber = rand() % 100 + 1;
			} while (uniqueBusNumbers.find(busNumber) != uniqueBusNumbers.end());

			uniqueBusNumbers.insert(busNumber);

			std::string company = GenerateRandomCompany();
			int price = rand() % 31 + 30;
			std::string schedule = to_string(rand() % 24) + ":00";
			std::string startRoute = cities[rand() % cities.size()];
			std::string endRoute;

			do {
				endRoute = cities[rand() % cities.size()];
			} while (endRoute == startRoute);

			// Crear el bus con la ruta generada
			Bus bus(busNumber, company, price, schedule);
			bus.SetStartRoute(startRoute);
			bus.SetEndRoute(endRoute);

			// Agregar el bus al vector de buses
			buses.push_back(bus);
		}
	}

	vector<Bus> SearchBusesByRoute(const std::string& startRoute, const std::string& endRoute) {
		std::vector<Bus> matchingBuses;

		for (const auto& bus : allBuses) {
			if (bus.GetStartRoute() == startRoute && bus.GetEndRoute() == endRoute) {
				matchingBuses.push_back(bus);
			}
		}

		return matchingBuses;
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

