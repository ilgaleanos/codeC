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
		Mapa(int _size, Punto *coordenadas);

		inline int getSize();
		inline void getDistancias();
		inline Punto * getCoordenadas();

		double costo (int *ruta);

		virtual ~Mapa();
};


Mapa::Mapa(int size, Punto *coordenadas) {
	_size = size;
	_coordenadas = coordenadas;
	_distancias = (double*) calloc (_size * _size, 8);

	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size; j++) {
			_distancias[ _size * i + j ] = coordenadas[j].distancia(&coordenadas[i]);
		}
	}
}


inline int Mapa::getSize() {
	return _size;
}


inline Punto * Mapa::getCoordenadas() {
	return _coordenadas;
}


inline void Mapa::getDistancias() {
	print( _distancias, _size, _size );
}


double Mapa::costo(int *ruta) {
	_costo = _distancias[ _size * ruta[_size-1] + ruta[0] ];
	for (int i = 0; i < _size - 1; i++) {
		_costo += _distancias[ _size * ruta[i] + ruta[i+1]];
	}
	return _costo;
}



Mapa::~Mapa() {
	free(_distancias);
}
