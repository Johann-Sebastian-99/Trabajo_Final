#ifndef __DATAFRAME_HPP__
#define __DATAFRAME_HPP__
#include "Fila.hpp"
#include "Indexacion.hpp"
#include <fstream>
#include <string.h>
#include <sstream>
#include <iomanip>
#include "Ordenamiento.hpp"
using namespace std;

class DataFrame {
private:
	vector<Fila*>* filas;
	vector<pair<char, string>*>* datos;
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
		datos = new vector<pair<char, string>*>;
		indexar = new Indexacion();
		numFilas = 0;
	}

	DataFrame(vector<Fila*>* filas, vector<pair<char, string>*>* datos) {
		this->filas = filas;
		this->datos = datos;
	}

	int cantidad_filas() {
		return numFilas;
	}

	void agregar_fila(Fila* nuevo) {
		filas->push_back(nuevo);
	}

	void valores_fila() {
		string dato;
		filas->push_back(new Fila());
		for (size_t i = 0; i < datos->size(); i++) {
			size_t in = 0, c = 0, f = 0, s = 0;
			switch (datos->at(i)->first)
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

	void definir_columnas(vector<pair<char, string>*>* columnas) {
		datos = columnas;
		for (size_t i = 0; i < datos->size(); i++) {
			indexar->agregar(datos->at(i)->first);
		}
	}

	vector<pair<char, string>*>* getColumnas() {
		return datos;
	}

	/*void tipos(string linea) {
		stringstream temp(linea);
		string dato;
		while (getline(temp, dato, ',')) {
			datos->push_back(identificarTD(dato));
			indexar->agregar(identificarTD(dato));
		}
	}*/

	void cargarMatriz(string nombre, char separador) {
		ifstream archivo;
		archivo.open(nombre);
		if (archivo.fail()) {
			cout << "No se pudo encontrar el archivo . . . ";
			system("pause>0");
			return;
		}
		string linea;
		while (getline(archivo, linea)) {
			stringstream temp(linea);
			string dato;
			agregar_fila(new Fila());
			size_t in = 0, c = 0, f = 0, s = 0;
			for (size_t i = 0; i < datos->size(); i++) {
				switch (datos->at(i)->first)
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

	void guardarMatriz(string nombre, char separador) { //Exportar
		ofstream archivo;
		archivo.open(nombre + ".txt");
		for (size_t i = 0; i < filas->size(); i++) {
			size_t in = 0, c = 0, f = 0, s = 0;
			for (size_t j = 0; j < datos->size(); j++) {
				switch (datos->at(j)->first)
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
				if (j < datos->size() - 1) archivo << separador;
			}
			archivo << endl;
		}
		archivo.close();
	}

	pair<size_t, char>* buscar_columna(string columna) {
		size_t in = 0, f = 0, c = 0, s = 0;
		for (size_t i = 0; i < datos->size(); i++) {
			switch (datos->at(i)->first)
			{
			case 'I':
				if (datos->at(i)->second == columna)
					return new pair<size_t, char>(in, datos->at(i)->first);
				in++;
				break;
			case 'F':
				if (datos->at(i)->second == columna)
					return new pair<size_t, char>(f, datos->at(i)->first);
				f++;
				break;
			case 'C':
				if (datos->at(i)->second == columna)
					return new pair<size_t, char>(c, datos->at(i)->first);
				c++;
				break;
			case 'S':
				if (datos->at(i)->second == columna)
					return new pair<size_t, char>(s, datos->at(i)->first);
				s++;
				break;
			}
		}
	}

	template<typename T>
	vector<Fila*>* funcion_filtrar(string columna, T valor) {
		pair<size_t, char>* valores = buscar_columna(columna);
		return indexar->buscar(valores->first, valor);
	}

	void mostrar() {
		for (int i = 0; i < datos->size(); i++) {
			cout << datos->at(i)->second << "	";
		}
		cout << endl;
		for (size_t i = 0; i < filas->size(); i++) {
			size_t in = 0, c = 0, f = 0, s = 0, b = 0;
			for (size_t j = 0; j < datos->size(); j++) {
				switch (datos->at(j)->first)
				{
				case 'I':
					cout << filas->at(i)->getI(in) << setw(10);
					in++;
					break;
				case 'C':
					cout << filas->at(i)->getC(c) << setw(10);
					c++;
					break;
				case 'F':
					cout << filas->at(i)->getF(f) << setw(10);
					f++;
					break;
				case 'S':
					cout << filas->at(i)->getS(s) << setw(10);
					s++;
					break;
				}
			}
			cout << endl;
		}
	}

	void ordenar_columna(string columna) {
		pair<size_t, char>* ord = buscar_columna(columna);
		Ordenamiento* o = new Ordenamiento(filas, ord->first);
		if (ord->second == 'S') o->cadenas();
		else o->quicksort(ord->second);
		filas = o->ordenado();
		delete[] o;
		o = nullptr;
	}

};
#endif // !__DATAFRAME_HPP__