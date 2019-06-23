#ifndef __FILA_HPP__
#define __FILA_HPP__
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

class Fila {
private:
	vector<int>* enteros;
	vector<char>* caracteres;
	vector<float>* flotantes;
	vector<string>* cadenas;

public:
	Fila() {
		enteros = nullptr;
		caracteres = nullptr;
		flotantes = nullptr;
		cadenas = nullptr;
	}

	void insertar(int valor) {
		if (!enteros) enteros = new vector<int>;
		enteros->push_back(valor);
	}
	void insertar(char valor) {
		if (!caracteres) caracteres = new vector<char>;
		caracteres->push_back(valor);
	}
	void insertar(float valor) {
		if (!flotantes) flotantes = new vector<float>;
		flotantes->push_back(valor);
	}
	void insertar(string valor) {
		if (!cadenas) cadenas = new vector<string>;
		cadenas->push_back(valor);
	}

	int getI(size_t in) {
		return enteros->at(in);
	}
	char getC(size_t in) {
		return caracteres->at(in);
	}
	float getF(size_t in) {
		return flotantes->at(in);
	}
	string getS(size_t in) {
		return cadenas->at(in);
	}
};

#endif // !__FILA_HPP__