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
		if (dato.at(dato.size() - 1) == '\n') dato.erase(dato.size() - 1);
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

	int cantidad_columnas() {
		return datos->size();
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

	int getI_Fila(size_t ind, size_t in) {
		return filas->at(ind)->getI(in);
	}

	float getF_Fila(size_t ind, size_t f) {
		return filas->at(ind)->getF(f);
	}

	char getC_Fila(size_t ind, size_t c) {
		return filas->at(ind)->getC(c);
	}

	string getS_Fila(size_t ind, size_t s) {
		return filas->at(ind)->getS(s);
	}

	void tipos(string linea, char separador) {
		stringstream temp(linea);
		string dato;
		string nombre;
		size_t in = 1, f = 1, c = 1, s = 1;
		while (getline(temp, dato, separador)) {
			switch (identificarTD(dato))
			{
			case 'I':
				cout << "Digite el nombre de la " << in << "° columna numeros enteros: ";
				in++;
				break;
			case 'F':
				cout << "Digite el nombre de la " << f << "° columna de numeros reales: ";
				f++;
				break;
			case 'C':
				cout << "Digite el nombre de la " << c << "° columna de caracteres: ";
				c++;
				break;
			case 'S':
				cout << "Digite el nombre de la " << s << "° columna de cadenas de caracteres: ";
				s++;
				break;
			}
			getline(cin, nombre);
			datos->push_back(new pair<char, string>(identificarTD(dato), nombre));
			indexar->agregar(identificarTD(dato));
		}
	}

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
			if (numFilas == 0) tipos(linea, separador);
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
		pair<size_t, char>* r = new pair<size_t, char>(0, 'N');
		return r;
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
		if (ord->second == 'S') cadenas(ord->first);
		else quicksort(ord->second, ord->first);
	}

	void swap(vector<Fila*>*& filas, int ini, int fin) {
		Fila* aux = filas->at(ini);
		filas->at(ini) = filas->at(fin);
		filas->at(fin) = aux;
	}

	void ordenando(vector<Fila*>* filas, int izq, int der, char tipo, size_t ind) {
		int i = izq, j = der, tmp;
		int p;
		switch (tipo)
		{
		case 'I':
			p = filas->at((izq + der) / 2)->getI(ind);
			while (i <= j) {
				while (filas->at(i)->getI(ind) < p) i++;
				while (filas->at(j)->getI(ind) > p) j--;
				if (i <= j) {
					swap(filas, i, j);
					i++, j--;
				}
			}
			break;
		case 'F':
			p = filas->at((izq + der) / 2)->getF(ind);
			while (i <= j) {
				while (filas->at(i)->getF(ind) < p) i++;
				while (filas->at(j)->getF(ind) > p) j--;
				if (i <= j) {
					swap(filas, i, j);
					i++, j--;
				}
			}
			break;
		case 'C':
			p = filas->at((izq + der) / 2)->getC(ind);
			while (i <= j) {
				while (filas->at(i)->getC(ind) < p) i++;
				while (filas->at(j)->getC(ind) > p) j--;
				if (i <= j) {
					swap(filas, i, j);
					i++, j--;
				}
			}
			break;
		}
		if (izq < j)
			ordenando(filas, izq, j, tipo, ind);
		if (i < der)
			ordenando(filas, i, der, tipo, ind);
	}

	void quicksort(char tipo, size_t ind) {
		ordenando(filas, 0, filas->size() - 1, tipo, ind);
	}

	void quicksort(vector<Fila*>* filas, int izq, int der, int ind) {
		int i = izq, j = der, tmp;
		char p;
		p = filas->at((izq + der) / 2)->getS(ind).at(0);
		while (i <= j) {
			while (filas->at(i)->getS(ind).at(0) < p) i++;
			while (filas->at(j)->getS(ind).at(0) > p) j--;
			if (i <= j) {
				swap(filas, i, j);
				i++, j--;
			}
		}
		if (izq < j)
			quicksort(filas, izq, j, ind);
		if (i < der)
			quicksort(filas, i, der, ind);
	}


	void cadenas(size_t ind) {
		quicksort(filas, 0, filas->size() - 1, ind);
	}

};
#endif // !__DATAFRAME_HPP__