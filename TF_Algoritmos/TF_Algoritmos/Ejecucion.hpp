#ifndef __EJECUCION_HPP__
#define __EJECUCION_HPP__
#include "Dataframe.hpp"
#include "Pantalla.hpp"

class Ejecucion {
private:
	DataFrame* matriz;
	Pantalla* pantallas;

public:
	Ejecucion() {
		matriz = new DataFrame();
		pantallas = new Pantalla();
	}

	void ejecutando() {
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
				matriz->definir_columnas(pantallas->CreacionDataframe());
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
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						
						break;
					}
				} while (accion != 6);
			}
		} while (opcion != 3);
	}
};

#endif // !__EJECUCION_HPP__