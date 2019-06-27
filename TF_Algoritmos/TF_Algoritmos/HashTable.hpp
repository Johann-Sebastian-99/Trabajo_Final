#ifndef __HASHTABLE_HPP__
#define __HASHTABLE_HPP__
#define TAMAÑO 100
#include "Lista.hpp"
#include <list>
#include <vector>
#include <array>
using namespace std;

class HashTable {
	Lista* listas;
	array<Lista*, TAMAÑO> tabla;

public:
	HashTable() {
		for (size_t i = 0; i < TAMAÑO; i++) {
			tabla[i] = nullptr;
		}
	}

	int funcionHash(string valor) {
		int suma = 0;
		int p;
		for (size_t i = 0; i < valor.size(); i++) {
			p = valor.at(i);
			suma = suma + p;
		}
		return suma % TAMAÑO;
	}

	void insertar(Fila* nuevo, string valor) {
		int hash = funcionHash(valor);
		if (tabla[hash] == nullptr) {
			tabla[hash] = new Lista();
		}
		tabla[hash]->agregar(nuevo, valor);
	}

	vector<Fila*>* buscar(string nombre) {
		int hash = funcionHash(nombre);
		return tabla[hash]->buscar(nombre);
	}

};



#endif // !__HASHTABLE_HPP__