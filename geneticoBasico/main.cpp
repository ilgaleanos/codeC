#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./include/tipos/Punto.hpp"
#include "./include/tipos/Mapa.hpp"
#include "./include/tipos/Colonia.hpp"

using namespace std;

int main()
{
	srand(time(NULL));

	Punto coordenadas[] = { Punto(1,1), Punto(-1,1), Punto(0,0) };
	Colonia *colonia = new Colonia( 3, &coordenadas[0]);

	colonia->setZanganoAsReina();
	colonia->getDistancias();
	print(colonia->costoReina());
	// delete mapa;
	delete colonia;
	return 0;
}
