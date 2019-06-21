#ifndef __LISTA_HPP__
#define __LISTA_HPP__
#include "NodoHT.hpp"
#include <string>
using namespace std;

class Lista {
	NodoHT* inicio;
	NodoHT* fin;

public:
	Lista(){
		inicio = fin = nullptr;
	}

	void agregar(Fila* elemento, int ind) {
		NodoHT* nuevo = new NodoHT(elemento, ind);
		if (inicio == nullptr) inicio = nuevo;
		else if (inicio == fin) {
			fin->setS(nuevo);
		}
		fin = nuevo;
	}

	vector<Fila*>* buscar(string valor) {
		vector<Fila*>* filas = new vector<Fila*>;
		NodoHT* aux;
		for (aux = inicio; aux->getS(); aux = aux->getS()) {
			if (valor == aux->getV()) {
				filas->push_back(aux->getElemento());
			}
		}
		return filas;
	}
};

#endif // !__LISTA_HPP__