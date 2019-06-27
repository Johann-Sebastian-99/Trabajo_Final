#include <iostream>
#include "Dataframe.hpp"
#include "Pantalla.hpp"
#include <string>
#include <vector>
using namespace std;
int main() {
	DataFrame* matriz;
	Pantalla* pantallas;
	matriz = new DataFrame();
	pantallas = new Pantalla();
	
	int opcion;
	int accion;
	pair<string, char> archivo;
	do {
		do {
			system("cls");
			opcion = pantallas->MenuInicio();
		} while (opcion < 1 || opcion > 3);
		switch (opcion)
		{
		case 1:
			system("cls");
			matriz->definir_columnas(pantallas->CreacionDataframe());
			break;
		case 2:
			system("cls");
			archivo = pantallas->MenuArchivo();
			system("cls");
			matriz->cargarMatriz(archivo.first, archivo.second);
			break;
		}
		if (opcion != 3) {
			do {
				system("cls");
				if (matriz->cantidad_filas() == 0) {
					cout << "La matriz esta vacia . . . ";
				}
				else {
					matriz->mostrar();
				}
				cout << endl << endl;
				cout << "Presione una tecla si desea ejecutar una accion . . . ";
				system("pause>0");
				do {
					system("cls");
					accion = pantallas->OpcionesDataframe();
				} while (accion < 1 || accion > 6);
				switch (accion)
				{
				case 1:
					system("cls");
					matriz->valores_fila();
					break;
				case 2:
					system("cls");
					pantallas->Ordenar(matriz);
					break;
				case 3:
					system("cls");
					pantallas->seleccionado(matriz);
					break;
				case 4:
					system("cls");
					pantallas->Filtrado(matriz);
					break;
				case 5:
					archivo = pantallas->MenuArchivo();
					matriz->guardarMatriz(archivo.first, archivo.second);
					break;
				}
			} while (accion != 6);
		}
	} while (opcion != 3);
}