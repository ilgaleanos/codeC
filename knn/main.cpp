/*
*	@author := ilgaleanos@gmail.com*
*	El siguiente algoritmo es una implementacion simple del algoritmo knn o
*	k vecindades cercanas, para ello tendremos una matriz (_size,_dim) de datos
* 	y un vector (1,_dim) los cuales se pueden o no inicializar de manera pseudoaletoria.
*	el objetivo es encontrar con cuales "filas" de la matriz está mas "cerca" el
*	vector dado, aquí usamos la distancia euclideana. La función retorna los k
*	índices de las filas mas cercanas a nuestro vector. No se ha realizado aún la
*	implementación de lectura de datos desde disco.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_sort_vector_double.h>
#include <sys/time.h>

#include "./include/Knn.hpp"
using namespace std;


int main (void) {
	Knn * esp = new Knn(20,2,true);
	esp->normalizar();
	esp->distancia(10);
	delete esp;
	return 0;
}
