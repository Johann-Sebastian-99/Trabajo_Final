#ifndef __ORDENAMIENTO_HPP__
#define __ORDENAMIENTO_HPP__
#include "Fila.hpp"
#include "Dataframe.hpp"
#include <vector>
using namespace std;

class Ordenamiento {
	vector<Fila*>* filas;
	size_t ind;

public:
	Ordenamiento(vector<Fila*>* filas, size_t ind) {
		this->filas = filas;
		this->ind = ind;
	}

	void swap(vector<Fila*>*& filas, int ini, int fin) {
		Fila* aux = filas->at(ini);
		filas->at(ini) = filas->at(fin);
		filas->at(fin) = aux;
	}

	void ordenando(vector<Fila*>* filas, int izq, int der, char tipo) {
		int i = izq, j = der, tmp;
		int p;
		switch (tipo)
		{
		case 'I':
			p = filas->at((izq + der) / 2)->getI(ind);
			while (i <= j) {
				while (filas->at(i)->getI(ind) < p) i++;
				while (filas->at(j)->getI(ind) > p) j--;
				if (i <= j) {
					swap(filas, i, j);
					i++, j--;
				}
			}
			break;
		case 'F':
			p = filas->at((izq + der) / 2)->getF(ind);
			while (i <= j) {
				while (filas->at(i)->getF(ind) < p) i++;
				while (filas->at(j)->getF(ind) > p) j--;
				if (i <= j) {
					swap(filas, i, j);
					i++, j--;
				}
			}
			break;
		case 'C':
			p = filas->at((izq + der) / 2)->getC(ind);
			while (i <= j) {
				while (filas->at(i)->getC(ind) < p) i++;
				while (filas->at(j)->getC(ind) > p) j--;
				if (i <= j) {
					swap(filas, i, j);
					i++, j--;
				}
			}
			break;
		}
		if (izq < j)
			ordenando(filas, izq, j, tipo);
		if (i < der)
			ordenando(filas, i, der, tipo);
	}

	void quicksort(char tipo) {
		ordenando(filas, 0, filas->size() - 1, tipo);
	}

	void quicksort(vector<Fila*>* filas, int izq, int der, int l) {
		int i = izq, j = der, tmp;
		char p;
		p = filas->at((izq + der) / 2)->getS(ind).at(l);
		while (i <= j) {
			while (filas->at(i)->getS(ind).at(l) < p) i++;
			while (filas->at(j)->getS(ind).at(l) > p) j--;
			if (i <= j) {
				swap(filas, i, j);
				i++, j--;
			}
		}
		if (izq < j)
			quicksort(filas, izq, j, l);
		if (i < der)
			quicksort(filas, i, der, l);
	}
	

	void cadenas() {
		quicksort(filas, 0, filas->size() - 1, 0);
	}

	vector<Fila*>* ordenado() {
		return filas;
	};

};

#endif // __ORDENAMIENTO_HPP__