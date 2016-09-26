void print_int_vector(int *v, size_t sz) {
	printf("[ ");
	for (size_t i = 0; i < sz - 1; i++) {
		printf("%i, ", *(v+i));
	}
	printf("%i ]\n", *(v + sz - 1));
}


void print_size_t_vector(size_t *v, size_t sz) {
	printf("[ ");
	for (size_t i = 0; i < sz - 1; i++) {
		printf("%zu, ", *(v+i));
	}
	printf("%zu ]\n", *(v + sz - 1));
}


void print_float_vector(float *v, size_t sz) {
	printf("[ ");
	for (size_t i = 0; i < sz - 1; i++) {
		printf("%f, ", *(v+i));
	}
	printf("%f ]\n", *(v + sz - 1));
}


void print_double_vector(double *v, size_t sz) {
	printf("[ ");
	for (size_t i = 0; i < sz - 1; i++) {
		printf("%f, ", *(v+i));
	}
	printf("%f ]\n", *(v + sz - 1));
}


void print_int_matriz(int *v, size_t szX, size_t szY) {
	printf("[ \n");
	for (size_t j = 0; j < szY; j++) {
		printf(" [ ");
		for (size_t i = 0; i < szX - 1; i++) {
			printf("%i, ", *(v + j*(szX) + i));
		}
		printf("%i ]\n", *(v + (j+1)*(szX) - 1 ));
	}
	printf("]\n");

}


void print_size_t_matriz(size_t *v, size_t szX, size_t szY) {
	printf("[ \n");
	for (size_t j = 0; j < szY ; j++) {
		printf(" [ ");
		for (size_t i = 0; i < szX - 1; i++) {
			printf("%zu, ", *(v + j*(szX) + i));
		}
		printf("%zu ]\n", *(v + (j+1)*(szX) - 1 ));
	}
	printf("]\n");

}


void print_float_matriz(float *v, size_t szX, size_t szY) {
	printf("[ \n");
	for (size_t j = 0; j < szY ; j++) {
		printf(" [ ");
		for (size_t i = 0; i < szX - 1; i++) {
			printf("%f, ", *(v + j*(szX) + i));
		}
		printf("%f ]\n", *(v + (j+1)*(szX) - 1 ));
	}
	printf("]\n");

}


void print_double_matriz(double *v, size_t szX, size_t szY) {
	printf("[ \n");
	for (size_t j = 0; j < szY ; j++) {
		printf(" [ ");
		for (size_t i = 0; i < szX - 1; i++) {
			printf("%f, ", *(v + j*(szX) + i));
		}
		printf("%f ]\n", *(v + (j+1)*(szX) - 1 ));
	}
	printf("]\n");

}
