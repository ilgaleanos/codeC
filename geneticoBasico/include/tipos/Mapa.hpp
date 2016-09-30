/*
*	Este objeto contiene toda la información contextual para la búsqueda de rutas
*	_size := número de ciudades
*	_coordenadas := coordenadas de las ciudades en la grilla
*	_distancias := matriz de distancias (tsp simétrico)
*	_costo := logitud del ciclo hamiltoniano
*/
#include "./../statics/utiles.hpp"
#include "./../coordenadas/coor.hpp"

class Mapa {
	protected:
		int _size;
		double *_distancias;
	private:
		double _costo;
		Punto *_coordenadas;
	public:
		Mapa(int &size, Punto *coordenadas);

		inline int getSize();
		inline void getDistancias();
		inline Punto * getCoordenadas();

		double costo (int *ruta);

		virtual ~Mapa();
};

/*
*	Calculamos la matriz simétrica de distancias a partir de las coordenadas
*	de las ciudades apoyándonos en la clase punto
*/
Mapa::Mapa(int &size, Punto *coordenadas) {
	_size = size;
	_coordenadas = coordenadas;
	_distancias = (double*) calloc (_size * _size, 8);

	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
			_distancias[ _size * i + j ] = coordenadas[j].distancia(&coordenadas[i]);
		}
	}
}

/*
*	getter de la cantidad de ciudades
*/
inline int Mapa::getSize() {
	return _size;
}

/*
*	getter de las coordenadas
*/
inline Punto * Mapa::getCoordenadas() {
	return _coordenadas;
}

/*
*	print de las distancias
*/
inline void Mapa::getDistancias() {
	print( _distancias, _size, _size );
}

/*
*	Encargada de calcular el costo de recorrer una ruta en este mapa
*/
double Mapa::costo(int *ruta) {
	_costo = _distancias[ _size * ruta[_size-1] + ruta[0] ];
	for (int i = 0; i < _size - 1; i++) {
		_costo += _distancias[ _size * ruta[i] + ruta[i+1]];
	}
	return _costo;
}


/*
*	liberamos memoria
*/
Mapa::~Mapa() {
	free(_distancias);
}
