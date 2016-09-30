/*
*	@author := ilgaleanos@gmail.com
*	Implementacion de una solución heurística para el problema TSP simétrico.
*	En el siguiente programa se ve una implementacion de un algoritmo que aunque
*	no es algoritmo genético, carece de propiedades esenciales de estos, pues
*	a mi modo de ver no son más que lastres en rendimiento y calidad; estas son
*	la generacion de una población, y la mutación. De manera que sigo
*	los principios de cruce y seleccion de algunas colonias de insectos en las
*	cuales existe una reina que es la joya genética de la colonia y una serie de
*	zánganos que compiten por generar una nueva generación. Así pues la población
*	no es necesaria sino simplemente es necesario generar a cada iteración un
*	zángano y dejar que el entorno decida si su descendecia debe ser la elegida.
*	De esta manera se soluciona el problema de una gran población y se tiene
*	"Mutacion" de forma coherente y casi permanente obteniendo asi un mayor
*	rango de busqueda. De Igual forma se implementa un optimizador local para
*	evitar de manera más contundente mínimos locales.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./include/tipos/Mapa.hpp"
#include "./include/tipos/Colonia.hpp"

using namespace std;

int main()
{
	srand(time(NULL));
	int n = 29, cambios, iter = n * n;
	Colonia *colonia = new Colonia( n, &bays29[0]);

	bool bandera = false;
	size_t regresiva = n;

	while( regresiva > 0) {

		// este es un parametro a gusto, pequeño permite mas ejecuciones y grande
		// ejecuta busquedas más exhaustivas ambas resultan adecuadas según tamaño
		cambios = iter;
		while(cambios > 0) {
			bandera = colonia->cruzar();
			if(bandera){
				regresiva = n;
				cambios = iter;
			}
			cambios--;
		}

		for (size_t i = 0; i < n; i++) {
			bandera = colonia->opt2();
			if(bandera){
				regresiva = n;
			}
		}

		regresiva--;
	}

	delete colonia;
	return 0;
}
