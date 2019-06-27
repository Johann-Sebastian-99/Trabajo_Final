#ifndef __LISTA_HPP__
#define __LISTA_HPP__
#include "NodoHT.hpp"
#include <string>
using namespace std;

class Lista {
public:
	NodoHT* ini;
	NodoHT* fin;

	Lista(){
		ini = nullptr;
		fin = nullptr;
	}

	void agregar(Fila* elemento, string valor) {
		if (ini == nullptr) {
			ini = new NodoHT(elemento, valor);
			fin = ini;
		}
		else if (ini == fin) {
			NodoHT* nuevo = new NodoHT(elemento, valor);
			fin->setS(nuevo);
			fin = nuevo;
		}
	}

	vector<Fila*>* buscar(string valor) {
		vector<Fila*>* filas = new vector<Fila*>;
		NodoHT* aux;
		for (aux = ini; aux->getS() != nullptr; aux = aux->getS()) {
			if (valor == aux->getV()) {
				filas->push_back(aux->getElemento());
			}
		}
		return filas;
	}
};

#endif // !__LISTA_HPP__