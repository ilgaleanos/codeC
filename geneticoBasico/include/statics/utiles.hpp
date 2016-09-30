inline void print(int n) {
	printf("%i\n", n);
}

inline void print(size_t n) {
	printf("%zu\n", n);
}

inline void print(float n) {
	printf("%f\n", n);
}

inline void print(double n) {
	printf("%f\n", n);
}

void print(int *v, const size_t &sz) {
	printf("[ ");
	for (size_t i = 0; i < sz - 1; i++) {
		printf("%i, ", v[i]);
	}
	printf("%i ]\n", v[sz - 1]);
}


void print(size_t *v, const size_t &sz) {
	printf("[ ");
	for (size_t i = 0; i < sz - 1; i++) {
		printf("%zu, ", v[i]);
	}
	printf("%zu ]\n", v[sz - 1]);
}


void print(float *v, const size_t &sz) {
	printf("[ ");
	for (size_t i = 0; i < sz - 1; i++) {
		printf("%f, ", v[i]);
	}
	printf("%f ]\n", v[sz - 1]);
}


void print(double *v, const size_t &sz) {
	printf("[ ");
	for (size_t i = 0; i < sz - 1; i++) {
		printf("%f, ", v[i]);
	}
	printf("%f ]\n", v[sz - 1]);
}


void print(int *v, const size_t &szX, const size_t &szY) {
	printf("[ \n");
	for (size_t j = 0; j < szY; j++) {
		printf(" [ ");
		for (size_t i = 0; i < szX - 1; i++) {
			printf("%i, ", v[szX * j + i]);
		}
		printf("%i ]\n", v[szX * (j+1) - 1] );
	}
	printf("]\n");

}


void print(size_t *v, const size_t &szX, const size_t &szY) {
	printf("[ \n");
	for (size_t j = 0; j < szY ; j++) {
		printf(" [ ");
		for (size_t i = 0; i < szX - 1; i++) {
			printf("%zu, ", v[szX * j + i]);
		}
		printf("%zu ]\n", v[szX *(j+1) - 1]);
	}
	printf("]\n");

}


void print(float *v, const size_t &szX, const  size_t &szY) {
	printf("[ \n");
	for (size_t j = 0; j < szY ; j++) {
		printf(" [ ");
		for (size_t i = 0; i < szX - 1; i++) {
			printf("%f, ", v[szX * j + i]);
		}
		printf("%f ]\n", v[szX *(j+1) - 1]);
	}
	printf("]\n");

}


void print(double *v, const size_t &szX, const size_t &szY) {
	printf("[ \n");
	for (size_t j = 0; j < szY ; j++) {
		printf(" [ ");
		for (size_t i = 0; i < szX - 1; i++) {
			printf("%f, ", v[szX * j + i]);
		}
		printf("%f ]\n", v[szX *(j+1) - 1]);
	}
	printf("]\n");

}

/*
*	Esta función devuelve un entero seudo-aleatorio entre [rangeLow, rangeHigh)
*/
inline int uniform_distribution(const int &rangeLow, const int &rangeHigh) {
	return rand()/(1.0 + RAND_MAX) * (rangeHigh - rangeLow)  + rangeLow;
}
