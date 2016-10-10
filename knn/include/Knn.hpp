/*
*	Objeto implementado con el apoyo de la libreria GSL consultar la documentación
*	https://www.gnu.org/software/gsl/ para una completa vista aclaratoria.
*/

#ifndef HAVE_INLINE
#define  HAVE_INLINE
#endif

/*
*	(_size, _dim) 		:= dimension de la matrix
*	gsl_vector_view 	:= vector de vista para normalizar
*/
class Knn {
	private:
		size_t _size, _dim;
		gsl_vector_view _columna;
		double _distancia_tmp, _norm_tmp;
		gsl_vector * _vector, * _distancias;
		gsl_matrix * _matriz;
	public:
		Knn(const size_t &size, const size_t &dim, const bool &ban);
		inline double get_vector_val(const size_t &i);
		inline double get_matrix_val(const size_t &i, const size_t &j);
		inline void set_vector_val(const size_t &i, const double &val);
		inline void set_matrix_val(const size_t &i, const size_t &j, const double &val);

		void normalizar();
		void distancia(const size_t &tam);

		virtual ~Knn();
};

/*
*	La bandera ban nos indica si debemos inicializar de manera aleatoria el problema
*	solicitamos memoria para la matriz, el vector objetivo y de distancias
*/
Knn::Knn(const size_t &size, const size_t &dim, const bool &ban) {
	_size = size;
	_dim = dim;
	_vector 	= gsl_vector_alloc (_dim);
	_distancias = gsl_vector_alloc (_size);
	_matriz 	= gsl_matrix_alloc (_size, _dim);


	// Seed generation based on time
	if (ban == true) {
		/* code */struct timeval tv;
		gettimeofday(&tv,0);
		unsigned long seed = tv.tv_sec + tv.tv_usec;

		gsl_rng_env_setup();
		const gsl_rng_type * T = gsl_rng_default;
		gsl_rng * r = gsl_rng_alloc (T);
		gsl_rng_set(r, seed);

		for (size_t j = 0; j < _dim; j++) {
			gsl_vector_set(_vector, j, gsl_rng_uniform(r));
		}

		for (size_t i = 0; i < _size; i++) {
			for (size_t j = 0; j < _dim; j++) {
				gsl_matrix_set(_matriz, i, j, gsl_rng_uniform(r));
			}
		}
	}

}

/*
*	getters y setters externos para vector y matriz
*/
inline double Knn::get_vector_val(const size_t &i) {
	return gsl_vector_get(_vector, i);
}

inline void Knn::set_vector_val(const size_t &i, const double &val) {
	gsl_vector_set(_vector, i, val);
}

inline double Knn::get_matrix_val(const size_t &i, const size_t &j) {
	return gsl_matrix_get(_matriz, i, j);
}

inline void Knn::set_matrix_val(const size_t &i, const size_t &j, const double &val) {
	gsl_matrix_set(_matriz, i, j, val);
}

/*
*	Normalización de _matriz basados en norma euclidea
*/
void Knn::normalizar() {
	for (size_t j = 0; j < _dim; j++) {
		_columna = gsl_matrix_column(_matriz, j);
		_norm_tmp = 1 / gsl_blas_dnrm2(&_columna.vector);
		gsl_vector_scale(&_columna.vector, _norm_tmp);
	}
}

/*
*	Cálculo de vecindades cercanas basados en distancia euclidea
*/
void Knn::distancia(const size_t &tam) {
	if ( tam >= _size) {
		fprintf(stderr,"%s\n","ERROR: Búsqueda de vecinos supera dimensión de vecindad");
		return;
	}

	double val;
	for (size_t i = 0; i < _size; i++) {
		_distancia_tmp = 0;

		for (size_t j = 0; j < _dim; j++) {
			val = gsl_matrix_get(_matriz, i, j);
			_distancia_tmp += val * val;
		}

		_distancia_tmp = sqrt(_distancia_tmp);
		gsl_vector_set(_distancias, i, _distancia_tmp);
	}

	size_t * small = (size_t*) malloc (tam * 8);
	gsl_sort_vector_smallest_index(small, tam, _distancias);

	for (size_t i = 0; i < tam - 1; i++) {
		printf("%zu,", small[i] );
	}
	printf("%zu\n", small[tam - 1] );

	free (small);
}

/*
*	Liberamos memoria
*/
Knn::~Knn() {
	gsl_vector_free (_vector);
	gsl_vector_free (_distancias);
	gsl_matrix_free (_matriz);
}
