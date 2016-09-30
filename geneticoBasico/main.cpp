#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./include/tipos/Mapa.hpp"
#include "./include/tipos/Colonia.hpp"

using namespace std;

int main()
{
	srand(time(NULL));
	int n = 48;
	Colonia *colonia = new Colonia( n, &att48[0]);

	bool bandera = false;
	size_t regresiva = 20 * n;

	while( regresiva > 0) {

		for (size_t i = 0; i < 2 * n; i++) {

			bandera = colonia->cruzar();
			if(bandera){ regresiva = 20 * n; }

		}

		for (size_t i = 0; i < 2 * n; i++) {

			bandera = colonia->opt2();
			if(bandera){ regresiva = 20 * n; }

		}

		regresiva--;
	}

	delete colonia;
	return 0;
}
