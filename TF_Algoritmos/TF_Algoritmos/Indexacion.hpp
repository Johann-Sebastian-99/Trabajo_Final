#ifndef __INDEXACION_HPP__
#define __INDEXACION_HPP__
#include <vector>
#include "ArbolAVL.hpp"
using namespace std;

class Indexacion {
	vector<Arbol<int>*>* enteros;
	vector<Arbol<float>*>* flotantes;
	vector<Arbol<char>*>* caracteres;
	vector<Arbol<string>*>* cadenas;

public:
	Indexacion() {
		enteros = nullptr;
		flotantes = nullptr;
		caracteres = nullptr;
		cadenas = nullptr;
	}

	void insertar(int valor) {
		if (enteros == nullptr) enteros = new vector<Arbol<int>*>;
		enteros->push_back(new Arbol<int>());
	}
	void insertar(float valor) {
		if (flotantes == nullptr) flotantes = new vector<Arbol<float>*>;
		flotantes->push_back(new Arbol<float>());
	}
	void insertar(char valor) {
		if (caracteres == nullptr) enteros = new vector<Arbol<int>*>;
		enteros->push_back(new Arbol<int>());
	}
	void insertar(string valor) {
		if (cadenas == nullptr) enteros = new vector<Arbol<int>*>;
		enteros->push_back(new Arbol<int>());
	}
	
};

#endif // !__INDEXACION_HPP__