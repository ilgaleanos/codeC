#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./include/utiles.h"

using namespace std;

int main()
{
	// srand(time(NULL));

	Punto coordenadas[] = { Punto(1,1), Punto(2,2), Punto(3,3) };
	int ruta[] = {0,1,2};

	Mapa *mapa = new Mapa(3, &coordenadas[0]);

	printf("%f\n", mapa->costo(&ruta[0]) );

	delete mapa;

	return 0;
}
