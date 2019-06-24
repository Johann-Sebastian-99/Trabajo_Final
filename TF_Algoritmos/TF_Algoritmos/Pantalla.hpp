#ifndef __PANTALLA_HPP__
#define __PANTALLA_HPP__
#include "Dataframe.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pantalla {
private:
	char identificarTD(string dato) {
		int contP = 0;
		for (size_t i = 0; i < dato.size(); i++) {
			if (dato.at(i) > 57 || dato.at(i) < 48) {
				if (dato.size() == 1) return 'C';
				else if (dato.at(i) == 46 && contP < 1) contP++;
				else return 'S';
			}
		}
		if (contP > 0) return 'F';
		else return 'I';
	}
public:
	Pantalla() {

	}

	int MenuInicio() {
		string opcion;
		do {
			system("cls");
			cout << "1.- Crear Nuevo Dataframe" << endl;
			cout << "2.- Cargar Dataframe Existente" << endl;
			cout << "3.- Salir del Programa" << endl;
			cout << "Elija la opcion que desee ejecutar: ";
			getline(cin, opcion);
		} while ((identificarTD(opcion) != 'I'));
		return stoi(opcion);
	}

	vector<pair<char, string>*>* CreacionDataframe() {
		vector<pair<char, string>*>* columnas = new vector<pair<char, string>*>;
		string cant;
		string dato;
		string nombre;
		cout << "Elija la cantidad de columnas que desea agregar: ";
		getline(cin, cant);
		for (size_t i = 0; i < stoi(cant); i++) {
			do {
				cout << "Elija el tipo de dato " << i + 1 << "(I: Entero, F: Real, C: Caracter, S: Cadena de caracteres): ";
				getline(cin, dato);
				cout << "Digite el nombre de la columna: ";
				getline(cin, nombre);
			} while ((identificarTD(dato) != 'C'));
			columnas->push_back(new pair<char, string>(dato.at(0), nombre));
		}
		return columnas;
	}

	void seleccionado(DataFrame* matriz) {
		

	}

	pair<string, char> MenuArchivo() {
		string nombre;
		string opcion;
		char separador;
		system("cls");
		cout << "Escriba el nombre del archivo(sin formato): ";
		getline(cin, nombre);
		cout << endl;
		do {
			system("cls");
			cout << "1.- Archivo .txt" << endl;
			cout << "2.- Archivo .csv" << endl;
			cout << "3.- Otro" << endl;
			cout << "Elija la opcion: ";
			getline(cin, opcion);
		} while (identificarTD(opcion) != 'I');
		switch (stoi(opcion))
		{
		case 1:
			nombre += ".txt";
			separador = ',';
			break;
		case 2:
			nombre += ".csv";
			separador = ';';
			break;
		case 3:
			nombre += ".tsv";
			separador = '\t';
			break;
		}
		pair<string, char> r(nombre, separador);
		return r;
	}

	void Filtrado(DataFrame* matriz) {
		string respuesta;
		string dato;
		vector<Fila*>* filas;
		pair<string, string> columnas;
		DataFrame* aux;
		cout << "Elija la columna(numero de columna): ";
		getline(cin, columnas.first);
		cout << "Digite el dato que desea filtrar: ";
		getline(cin, dato);
		switch (identificarTD(dato))
		{
		case 'I':
			filas = matriz->funcion_filtrar(columnas.first, stoi(dato));
			break;
		case 'F':
			filas = matriz->funcion_filtrar(columnas.first, stof(dato));
			break;
		case 'C':
			filas = matriz->funcion_filtrar(columnas.first, dato.at(0));
			break;
		case 'S':
			filas = matriz->funcion_filtrar(columnas.first, dato);
			break;
		}
		aux = new DataFrame(filas, matriz->getColumnas());
		cout << "Desea filtrar otra columna?";
		getline(cin, respuesta);
		if (toupper(respuesta.at(0)) == 'S') {
			cout << "Elija la columna(numero de columna): ";
			getline(cin, columnas.first);
			cout << "Digite el dato que desea filtrar: ";
			getline(cin, dato);
			switch (identificarTD(dato))
			{
			case 'I':
				filas = aux->funcion_filtrar(columnas.first, stoi(dato));
				break;
			case 'F':
				filas = aux->funcion_filtrar(columnas.first, stoi(dato));
				break;
			case 'C':
				filas = aux->funcion_filtrar(columnas.first, stoi(dato));
				break;
			case 'S':
				filas = aux->funcion_filtrar(columnas.first, stoi(dato));
				break;
			}
			aux = new DataFrame(filas, matriz->getColumnas());
		}
		aux->mostrar();
		cout << "Si desea guardar esta matriz, digite G; sino, digite cualquier otra tecla: ";
		getline(cin, respuesta);
		if (toupper(respuesta.at(0)) == 'G') {
			pair<string, char> r = MenuArchivo();
			aux->guardarMatriz(r.first, r.second);
		}
		system("cls");
		aux->mostrar();
		cout << "Guardado exitosamente, puse cualquier tecla para continuar . . .";
		delete[] aux;
		aux = nullptr;
		system("pause>0");
	}

	void Seleccion() {
		cout << "Elija la columna(numero de columna): " << endl;
	}

	void Ordenar(DataFrame* matriz) {
		string columna;
		string respuesta;
		system("cls");
		cout << "Cual columna desea ordenar?";
		getline(cin, columna);
		system("cls");
		matriz->ordenar_columna(columna);
		matriz->mostrar();
		cout << "Si desea guardar esta matriz, digite G; sino, digite cualquier otra tecla: ";
		getline(cin, respuesta);
		if (toupper(respuesta.at(0)) == 'G') {
			pair<string, char> r = MenuArchivo();
			matriz->guardarMatriz(r.first, r.second);
		}
		system("cls");
		matriz->mostrar();
		cout << "Guardado exitosamente, puse cualquier tecla para continuar . . .";
		system("pause>0");
	}

	int OpcionesDataframe(){
		string opcion;
		do {
			cout << "1.- Agregar fila" << endl;
			cout << "2.- Ordenar por columnas" << endl;
			cout << "3.- Seleccionar columnas" << endl;
			cout << "4.- Filtrar por columnas" << endl;
			cout << "5.- Guardar Dataframe" << endl;
			cout << "6.- Salir" << endl;
			cout << "Elija la opcion que desea ejecutar: ";
			getline(cin, opcion);
		} while (identificarTD(opcion) != 'I');
		return stoi(opcion);
	}

};


#endif // !__PANTALLA_HPP__