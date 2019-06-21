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

	void agregar(string valor, Fila* elemento) {
		NodoHT* aux = inicio;
		for (aux = inicio; aux != fin; aux = aux->getS()) {
			if (aux->)
		}
	}

};

#endif // !__LISTA_HPP__