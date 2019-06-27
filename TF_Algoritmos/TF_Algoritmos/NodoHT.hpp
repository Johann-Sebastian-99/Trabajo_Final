#ifndef __NODO_HT_HPP__
#define __NODO_HT_HPP__
#include <vector>
#include <string>
#include "Fila.hpp"
using namespace std;

class NodoHT {
	Fila* elemento;
	string valor;
	NodoHT* sig;

public:
	NodoHT(Fila* elemento, string valor) {
		this->valor = valor;
		this->elemento = elemento;
		sig = nullptr;
	}

	NodoHT* getS() {
		return sig;
	}

	void setS(NodoHT* sig) {
		this->sig = sig;
	}

	string getV() {
		return valor;
	}

	Fila* getElemento() {
		return elemento;
	}
};


#endif // !__NODOHT_HPP__