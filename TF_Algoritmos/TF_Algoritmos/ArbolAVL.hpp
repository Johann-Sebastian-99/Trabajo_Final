#ifndef __ARBOLAVL_HPP__
#define __ARBOLAVL_HPP__
#include "DataFrame.hpp"
#include "Nodo_Arbol.hpp"

class Arbol {
private:
	Nodo* inicio;

	int calcular_altura(Nodo*& raiz) {
		int izq = 0, der = 0;
		if (raiz->getI()) izq = raiz->getI()->getA() + 1;
		if (raiz->getD()) der = raiz->getD()->getA() + 1;
		if (izq >= der) return izq;
		else return der;
	}

	void _insertar(Nodo*& raiz, int valor, Fila* nuevo, size_t ind) {
		if (raiz == nullptr) {
			raiz = new Nodo(valor);
			return;
		}
		else if (raiz->getV() == valor) {
			raiz->setE(nuevo);
			return;
		}
		else {
			int izq = 0, der = 0;
			if (raiz->getV() < valor) {
				_insertar(raiz->getI(), valor, nuevo, ind);
			}
			else {
				_insertar(raiz->getD(), valor, nuevo, ind);
			}
		}
		balanceo(raiz);
		raiz->setA(calcular_altura(raiz));
	}

	int factor_equilibrio(Nodo* izq, Nodo* der) {
		if (!izq && !der) return 0;
		if (!izq && der) return der->getA() + 1;
		if (izq && !der) return (izq->getA() + 1)*(-1);
		return (der->getA() + 1) - (izq->getA() + 1);
	}

	void balanceo(Nodo*& raiz) {
		Nodo* izq = raiz->getI();
		Nodo* der = raiz->getD();
		if (factor_equilibrio(izq, der) > 1) {
			if (factor_equilibrio(der->getI(), der->getD()) < 0) {
				raiz->getD() = rotacion_der(der);
				raiz = rotacion_izq(raiz);
			}
			else {
				raiz = rotacion_izq(raiz);
			}
		}
		if (factor_equilibrio(izq, der) < -1) {
			if (factor_equilibrio(izq->getI(), izq->getD()) > 0) {
				raiz->getI() = rotacion_izq(izq);
				raiz = rotacion_der(raiz);
			}
			else {
				raiz = rotacion_der(raiz);
			}
		}
	}

	Nodo*& rotacion_izq(Nodo* raiz) {
		Nodo* aux = raiz->getD();
		raiz->setD(aux->getI());
		aux->setI(raiz);
		aux->setA(calcular_altura(aux));
		raiz->setA(calcular_altura(raiz));
		return aux;
	}

	Nodo*& rotacion_der(Nodo* raiz) {
		Nodo* aux = raiz->getI();
		raiz->setI(aux->getD());
		aux->setD(raiz);
		aux->setA(calcular_altura(aux));
		raiz->setA(calcular_altura(raiz));
		return aux;
	}

	vector<Fila*>* _buscar(Nodo* raiz, int valor) {
		if (raiz == nullptr) return nullptr;
		else if (valor == raiz->getV()) return raiz->getE();
		else if (raiz->getV() < valor) return _buscar(raiz->getI(), valor);
		else return _buscar(raiz->getD(), valor);
	}

public:
	Arbol() { inicio = nullptr; }
	void insertar(int valor, Fila* nuevo, size_t ind) {
		_insertar(inicio, valor, nuevo, ind);
	}

	vector<Fila*>* buscar(int valor) {
		_buscar(inicio, valor);
	}
};

#endif // !__ARBOL_1_HPP__