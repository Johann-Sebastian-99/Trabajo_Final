#ifndef __NODO_ARBOL_HPP__
#define __NODO_ARBOL_HPP__
#include "Dataframe.hpp"

template<typename T>
class Nodo {
private:
	T valor;
	Nodo* izq;
	Nodo* der;
	vector<Fila*>* filas;
	int altura;

public:
	Nodo(T valor) {
		this->valor = valor;
		izq = nullptr;
		der = nullptr;
		altura = 0;
		filas = new vector<Fila*>;
	}

	T getV() { return valor; }
	Nodo*& getI() { return izq; }
	Nodo*& getD() { return der; }
	int getA() { return altura; }

	void setV(T valor) { this->valor = valor; }
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