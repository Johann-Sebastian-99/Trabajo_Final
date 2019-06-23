#ifndef __DATAFRAME_HPP__
#define __DATAFRAME_HPP__
#include "Fila.hpp"
#include "Indexacion.hpp"
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

class DataFrame {
private:
	vector<Fila*>* filas;
	vector<char>* datos;
	size_t numFilas;
	Indexacion* indexar;
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
	DataFrame() {
		filas = new vector<Fila*>;
		datos = new vector<char>;
		indexar = new Indexacion();
		numFilas = 0;
	}

	void agregar_fila(Fila* nuevo) {
		filas->push_back(nuevo);
	}

	void valores_fila() {
		string dato;
		filas->push_back(new Fila());
		for (size_t i = 0; i < datos->size(); i++) {
			size_t in = 0, c = 0, f = 0, s = 0;
			switch (datos->at(i))
			{
			case 'I':
				cout << "Inserte valor de columna " << i + 1 << ": ";
				getline(cin, dato);
				filas->at(numFilas)->insertar(stoi(dato));
				indexar->insertar(in, filas->at(numFilas), stoi(dato));
				in++;
				break;
			case 'C':
				cout << "Inserte valor de columna " << i + 1 << ": ";
				getline(cin, dato);
				filas->at(numFilas)->insertar(dato.at(0));
				indexar->insertar(c, filas->at(numFilas), dato.at(0));
				c++;
				break;
			case 'F':
				cout << "Inserte valor de columna " << i + 1 << ": ";
				getline(cin, dato);
				filas->at(numFilas)->insertar(stof(dato));
				indexar->insertar(f, filas->at(numFilas), stof(dato));
				f++;
				break;
			case 'S':
				cout << "Inserte valor de columna " << i + 1 << ": ";
				getline(cin, dato);
				filas->at(numFilas)->insertar(dato);
				indexar->insertar(s, filas->at(numFilas), dato);
				s++;
				break;
			}
		}
		numFilas++;
	}

	void definir_columnas(vector<char>* columnas) {
		datos = columnas;
		for (size_t i = 0; i < datos->size(); i++) {
			indexar->agregar(datos->at(i));
		}
	}

	void tipos(string linea) {
		stringstream temp(linea);
		string dato;
		while (getline(temp, dato, ',')) {
			datos->push_back(identificarTD(dato));
			indexar->agregar(identificarTD(dato));
		}
	}

	void cargarMatriz(string nombre, char separador) {
		ifstream archivo;
		archivo.open(nombre);
		string linea;
		while (getline(archivo, linea)) {
			if (numFilas == 0) tipos(linea);
			stringstream temp(linea);
			string dato;
			agregar_fila(new Fila());
			for (size_t i = 0; i < datos->size(); i++) {
				size_t in = 0, c = 0, f = 0, s = 0;
				switch (datos->at(i))
				{
				case 'I':
					getline(temp, dato, separador);
					filas->at(numFilas)->insertar(stoi(dato));
					indexar->insertar(in, filas->at(numFilas), stoi(dato));
					in++;
					break;
				case 'C':
					getline(temp, dato, separador);
					filas->at(numFilas)->insertar(dato.at(0));
					indexar->insertar(c, filas->at(numFilas), dato.at(0));
					c++;
					break;
				case 'F':
					getline(temp, dato, separador);
					filas->at(numFilas)->insertar(stof(dato));
					indexar->insertar(f, filas->at(numFilas), stof(dato));
					f++;
					break;
				case 'S':
					getline(temp, dato, separador);
					filas->at(numFilas)->insertar(dato);
					indexar->insertar(s, filas->at(numFilas), dato);
					s++;
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
			for (size_t j = 0; j < datos->size(); j++) {
				size_t in = 0, c = 0, f = 0, s = 0;
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
				}
			}
			cout << endl;
		}
	}
};
#endif // !__DATAFRAME_HPP__