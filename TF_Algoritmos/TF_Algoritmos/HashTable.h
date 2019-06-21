#ifndef __HASHTABLE_HPP__
#define __HASHTABLE_HPP__
#define TAMAÑO 100
#include "Lista.hpp"
#include <vector>
#include <array>
using namespace std;

class HashTable {
	Lista* listas;
	array<Lista*, TAMAÑO> tabla;

public:
	HashTable() {
		listas = new Lista();
	}

	int funcionHash(string valor) {
		int suma = 0;
		for (size_t i = 0; i < valor.size(); i++) {
			suma += valor.at(i);
		}
		return suma % TAMAÑO;
	}

	void insertar(Fila* nuevo, int ind) {
		int hash = funcionHash(nuevo->getS(ind));
		if (tabla[hash] == NULL) {
			tabla[hash] = new Lista();
		}
		tabla[hash]->agregar(nuevo, ind);
	}

	vector<Fila*>* buscar(string nombre) {
		int hash = funcionHash(nombre);
		return tabla[hash]->buscar(nombre);
	}

};



#endif // !__HASHTABLE_HPP__