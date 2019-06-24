#ifndef __ARBOLAVL_HPP__
#define __ARBOLAVL_HPP__
#include "DataFrame.hpp"
#include "Nodo_Arbol.hpp"

template<typename T>
class Arbol {
public:
	Arbol() { inicio = nullptr; }
	void insertar(T valor, Fila* nuevo) {
		_insertar(inicio, valor, nuevo);
	}

	vector<Fila*>* buscar(int valor) {
		return _buscar(inicio, valor);
	}

private:
	Nodo<T>* inicio;

	int calcular_altura(Nodo<T>*& raiz) {
		int izq = 0, der = 0;
		if (raiz->getI()) izq = raiz->getI()->getA() + 1;
		if (raiz->getD()) der = raiz->getD()->getA() + 1;
		if (izq >= der) return izq;
		else return der;
	}

	void _insertar(Nodo<T>*& raiz, T valor, Fila* nuevo) {
		if (raiz == nullptr) {
			raiz = new Nodo<T>(valor);
			raiz->setE(nuevo);
			return;
		}
		else if (valor == raiz->getV()) {
			raiz->setE(nuevo);
			return;
		}
		else {
			int izq = 0, der = 0;
			if (raiz->getV() < valor) {
				_insertar(raiz->getI(), valor, nuevo);
			}
			else {
				_insertar(raiz->getD(), valor, nuevo);
			}
			balanceo(raiz);
			raiz->setA(calcular_altura(raiz));
		}
	}

	int factor_equilibrio(Nodo<T>* izq, Nodo<T>* der) {
		if (!izq && !der) return 0;
		if (!izq && der) return der->getA() + 1;
		if (izq && !der) return (izq->getA() + 1)*(-1);
		return (der->getA() + 1) - (izq->getA() + 1);
	}

	void balanceo(Nodo<T>*& raiz) {
		Nodo<T>* izq = raiz->getI();
		Nodo<T>* der = raiz->getD();
		if (factor_equilibrio(izq, der) > 1) {
			if (factor_equilibrio(der->getI(), der->getD()) < 0) 
				raiz->getD() = rotacion_der(der);
			raiz = rotacion_izq(raiz);
		}
		if (factor_equilibrio(izq, der) < -1) {
			if (factor_equilibrio(izq->getI(), izq->getD()) > 0) 
				raiz->getI() = rotacion_izq(izq);
			raiz = rotacion_der(raiz);
		}
	}

	Nodo<T>*& rotacion_izq(Nodo<T>* raiz) {
		Nodo<T>* aux = raiz->getD();
		raiz->setD(aux->getI());
		aux->setI(raiz);
		aux->setA(calcular_altura(aux));
		raiz->setA(calcular_altura(raiz));
		return aux;
	}

	Nodo<T>*& rotacion_der(Nodo<T>* raiz) {
		Nodo<T>* aux = raiz->getI();
		raiz->setI(aux->getD());
		aux->setD(raiz);
		aux->setA(calcular_altura(aux));
		raiz->setA(calcular_altura(raiz));
		return aux;
	}

	vector<Fila*>* _buscar(Nodo<T>* raiz, int valor) {
		if (raiz == nullptr) return nullptr;
		else if (valor == raiz->getV()) return raiz->getE();
		else if (raiz->getV() < valor) return _buscar(raiz->getI(), valor);
		else return _buscar(raiz->getD(), valor);
	}
};

#endif // !__ARBOL_1_HPP__