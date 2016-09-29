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
	Mapa *mapa = new Mapa(3, &coordenadas[0]);
	Colonia *colonia = new Colonia( 3 );

	colonia->setZanganoAsReina();
	print_double_matriz( mapa->getDistancias(), 3, 3);
	printf("%f\n", mapa->costo( colonia->getReina() ) );

	delete mapa;
	delete colonia;
	return 0;
}
