#ifndef __DATAFRAME_HPP__
#define __DATAFRAME_HPP__
#include "Fila.hpp"
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

class DataFrame {
private:
	vector<Fila*>* filas;
	vector<char>* datos;
	vector<Arbol*>* arboles;
	size_t numFilas;
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
		else if (dato.size() == 0 || dato.size() == 1) return 'B';
		else return 'I';
	}

public:
	DataFrame() {
		filas = new vector<Fila*>;
		datos = new vector<char>;
		numFilas = 0;
	}

	void agregar_fila(Fila* nuevo) {
		filas->push_back(nuevo);
	}

	void tipos(string linea) {
		stringstream temp(linea);
		string dato;
		while (getline(temp, dato, ',')) {
			datos->push_back(identificarTD(dato));
		}
	}

	void cargarMatriz(string nombre) {
		ifstream archivo;
		archivo.open(nombre + ".txt");
		string linea;
		while (getline(archivo, linea)) {
			if (numFilas == 0) tipos(linea);
			stringstream temp(linea);
			string dato;
			agregar_fila(new Fila());
			for (size_t i = 0; i < datos->size(); i++) {
				switch (datos->at(i))
				{
				case 'I':
					getline(temp, dato, ',');
					filas->at(numFilas)->insertar(stoi(dato));
					break;
				case 'C':
					getline(temp, dato, ',');
					filas->at(numFilas)->insertar(dato.at(0));
					break;
				case 'F':
					getline(temp, dato, ',');
					filas->at(numFilas)->insertar(stof(dato));
					break;
				case 'S':
					getline(temp, dato, ',');
					filas->at(numFilas)->insertar(dato);
					break;
				case 'B':
					getline(temp, dato, ',');
					filas->at(numFilas)->insertar(dato.at(0));
					break;
				}
			}
			numFilas++;
		}
		archivo.close();
	}

	void guardarMatriz(string nombre) { //Exportar
		ofstream archivo;
		archivo.open(nombre + ".txt");
		for (size_t i = 0; i < filas->size(); i++) {
			size_t in = 0, c = 0, f = 0, s = 0, b = 0;
			for (size_t j = 0; j < datos->size(); j++) {
				switch (datos->at(j))
				{
				case 'I':
					archivo << filas->at(i)->getI(in);
					in++;
					break;
				case 'C':
					archivo << filas->at(i)->getC(c);
					c++;
					break;
				case 'F':
					archivo << filas->at(i)->getF(f);
					f++;
					break;
				case 'S':
					archivo << filas->at(i)->getS(s);
					s++;
					break;
				case 'B':
					archivo << filas->at(i)->getB(b);
					b++;
					break;
				}
				if (j < datos->size() - 1) archivo << ",";
			}
			archivo << endl;
		}
		archivo.close();
	}

	void mostrar() {
		for (size_t i = 0; i < filas->size(); i++) {
			size_t in = 0, c = 0, f = 0, s = 0, b = 0;
			for (size_t j = 0; j < datos->size(); j++) {
				switch (datos->at(j))
				{
				case 'I':
					cout << filas->at(i)->getI(in) << "    ";
					in++;
					break;
				case 'C':
					cout << filas->at(i)->getC(c) << "    ";
					c++;
					break;
				case 'F':
					cout << filas->at(i)->getF(f) << "    ";
					f++;
					break;
				case 'S':
					cout << filas->at(i)->getS(s) << "    ";
					s++;
					break;
				case 'B':
					cout << filas->at(i)->getB(b) << "    ";
					b++;
					break;
				}
			}
			cout << endl;
		}
	}

	void indexado() {

	}
};
#endif // !__DATAFRAME_HPP__