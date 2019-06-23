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

	vector<char>* CreacionDataframe() {
		vector<char>* columnas = new vector<char>;
		string cant;
		string dato;
		cout << "Elija la cantidad de columnas que desea agregar: ";
		getline(cin, cant);
		for (size_t i = 0; i < stoi(cant); i++) {
			do {
				cout << "Elija el tipo de dato " << i + 1 << "(I: Entero, F: Real, C: Caracter, S: Cadena de caracteres): ";
				getline(cin, dato);
			} while ((identificarTD(dato) != 'C'));
			columnas->push_back(dato.at(0));
		}
		return columnas;
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

	void Filtrado() {
		cout << "Elija la columna(numero de columna): " << endl;
		
		cout << "Escriba el dato que desea filtrar: " << endl;
	}

	void Seleccion() {
		cout << "Elija la columna(numero de columna): " << endl;
	}

	void Ordenar() {
		cout << "Cual columna desea ordenar?" << endl;
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