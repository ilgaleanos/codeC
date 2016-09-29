/*
*	Este objeto contiene toda la información contextual para la búsqueda de rutas
*	_size := número de ciudades
*	_pCoordenadas := coordenadas de las ciudades en la grilla
*	_distancias := matriz de distancias (tsp simétrico)
*	_costo := logitud del ciclo hamiltoniano
*/

class Mapa {
	private:
		int _size;
		Punto *_pCoordenadas;
		double *_distancias;
		double _costo;
	public:
		Mapa(int _size, Punto *pCoordenadas);
		inline int getSize();
		inline Punto * getCoordenadas();
		inline double * getDistancias();
		inline double getCosto();
		double costo (int *ruta);
		~Mapa();
};

Mapa::Mapa(int size, Punto *pCoordenadas) {
	_size = size;
	_pCoordenadas = pCoordenadas;
	_distancias = (double*) calloc (_size * _size, 8);

	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
			_distancias[ _size * i + j ] = pCoordenadas[j].distancia(&pCoordenadas[i]);
		}
	}
}

inline int Mapa::getSize() {
	return _size;
}

inline Punto * Mapa::getCoordenadas() {
	return _pCoordenadas;
}

inline double * Mapa::getDistancias() {
	return _distancias;
}

inline double Mapa::getCosto() {
	return _costo;
}

double Mapa::costo(int *ruta) {
	_costo = _distancias[ _size * ruta[_size-1] + ruta[0] ];
	for (int i = 0; i < _size - 1; i++) {
		_costo += _distancias[i] + _distancias[i+1];
	}
	return _costo;
}

Mapa::~Mapa() {
	free(_distancias);
}
