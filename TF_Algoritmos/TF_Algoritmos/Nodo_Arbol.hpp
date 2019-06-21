#ifndef __NODO_ARBOL_HPP__
#define __NODO_ARBOL_HPP__
#include "Dataframe.hpp"

class Nodo {
private:
	int valor;
	Nodo* izq;
	Nodo* der;
	vector<Fila*>* filas;
	int altura;

public:
	Nodo(int valor) {
		this->valor = valor;
		izq = nullptr;
		der = nullptr;
		altura = 0;
		filas = new vector<Fila*>;
	}

	int getV() { return valor; }
	Nodo*& getI() { return izq; }
	Nodo*& getD() { return der; }
	int getA() { return altura; }

	void setV(int valor) { this->valor = valor; }
	void setI(Nodo* izq) { this->izq = izq; }
	void setD(Nodo* der) { this->der = der; }
	void setA(int altura) { this->altura = altura; }

	void setE(Fila* nueva) {
		filas->push_back(nueva);
	}
	vector<Fila*>* getE() {
		return filas;
	}
};


#endif // !__NODO_1_HPP__