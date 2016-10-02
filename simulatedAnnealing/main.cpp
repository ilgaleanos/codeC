/*
*	@author := ilgaleanos@gmail.com
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./include/Recocimiento.hpp"

using namespace std;

int main()
{
	srand(time(NULL));

	int maxTpasos = 100;
	double T = 100, congelante = 0.9;
	RecoSim *simulacion = new RecoSim(442, &pcb442[0], maxTpasos , T, congelante);
	simulacion->recocido();

	delete simulacion;
	return 0;
}
