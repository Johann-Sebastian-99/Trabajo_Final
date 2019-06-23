#ifndef __INDEXACION_HPP__
#define __INDEXACION_HPP__
#include <vector>
#include "ArbolAVL.hpp"
#include "HashTable.hpp"
using namespace std;

class Indexacion {
	vector<Arbol<int>*>* enteros;
	vector<Arbol<float>*>* flotantes;
	vector<Arbol<char>*>* caracteres;
	vector<HashTable*>* cadenas;

public:
	Indexacion() {
		enteros = nullptr;
		flotantes = nullptr;
		caracteres = nullptr;
		cadenas = nullptr;
	}

	void agregar(char tipo) {
		switch (tipo)
		{
		case 'I':
			if (enteros == nullptr) enteros = new vector<Arbol<int>*>;
			enteros->push_back(new Arbol<int>());
			break;
		case 'F':
			if (flotantes == nullptr) flotantes = new vector<Arbol<float>*>;
			flotantes->push_back(new Arbol<float>());
			break;
		case 'C':
			if (caracteres == nullptr) caracteres = new vector<Arbol<char>*>;
			caracteres->push_back(new Arbol<char>());
			break;
		case 'S':
			if (cadenas == nullptr) cadenas = new vector<HashTable*>;
			cadenas->push_back(new HashTable());
			break;
		}
	}

	void insertar(size_t ind, Fila* nuevo, int valor) {
		enteros->at(ind)->insertar(valor, nuevo);
	}
	void insertar(size_t ind, Fila* nuevo, float valor) {
		flotantes->at(ind)->insertar(valor, nuevo);
	}
	void insertar(size_t ind, Fila* nuevo, char valor) {
		caracteres->at(ind)->insertar(valor, nuevo);
	}
	void insertar(size_t ind, Fila* nuevo, string valor) {
		cadenas->at(ind)->insertar(nuevo, ind);
	}

	vector<Fila*>* buscar(size_t ind, int valor) {
		return enteros->at(ind)->buscar(valor);
	}
	vector<Fila*>* buscar(size_t ind, float valor) {
		return flotantes->at(ind)->buscar(valor);
	}
	vector<Fila*>* buscar(size_t ind, char valor) {
		return caracteres->at(ind)->buscar(valor);
	}
	vector<Fila*>* buscar(size_t ind, string valor) {
		return cadenas->at(ind)->buscar(valor);
	}
};

#endif // !__INDEXACION_HPP__