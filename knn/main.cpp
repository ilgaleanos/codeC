/*
*	@author := ilgaleanos@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_sort_vector_double.h>
#include <sys/time.h>

#include "./include/Knn.hpp"
using namespace std;


int main (void) {
	Knn * esp = new Knn(20,2);
	esp->distancia(10);
	delete esp;
	return 0;
}
