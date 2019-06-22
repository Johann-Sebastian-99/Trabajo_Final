#ifndef __PANTALLA_HPP__
#include <iostream>
using namespace std;

class Pantalla {
public:
	Pantalla() {

	}

	void MenuInicio() {
		cout << "1.- Crear Nuevo Dataframe" << endl;
		cout << "2.- Cargar Dataframe Existente" << endl;
		cout << "3.- Salir del Programa" << endl;
	}

	void MenuArchivo() {
		cout << "1.- Archivo .txt" << endl;
		cout << "2.- Archivo .csv" << endl;
		cout << "3.- Otro" << endl;

		cout << "Escriba el formato del archivo: " << endl;

		cout << "Escriba el nombre del archivo: " << endl;
	}

	void Filtrado() {
		cout << "Elija la columna(numero de columna): " << endl;
		
		cout << "Escriba el dato que desea filtrar: " << endl;
	}

	void Seleccion() {
		cout << "Elija la columna(numero de columna): " << endl;
	}

	void Ordenar() {
		cout << "Cual columna desea ordenar?" << endl;
	}

	void OpcionesDataframe(){
		cout << "1.- Agregar fila" << endl;
		cout << "2.- Eliminar fila" << endl;
		cout << "3.- Ordenar por columnas" << endl;
		cout << "4.- Seleccionar columnas" << endl;
		cout << "5.- Filtrar por columnas" << endl;
		cout << "6.- Guardar Dataframe" << endl;
	}

};


#endif // !__PANTALLA_HPP__