/*
*	Este objeto se almacenara la mejor ruta, se generarán y se cruzarán rutas
*	_size := número de ciudades heredado de mapa
*	_reina := mejor ruta encontrada
*	_zangano := ruta generada de forma seudo-aleatoria
*	_hijo := ruta obtenida por medio de cruce
*/
#include <algorithm>

class Colonia: public Mapa {
	private:
		// variables relevantes
		int *_reina, *_zangano, *_hijo;
		double _costoReina, _costoZangano, _costoHijo;

		// auxiliares
		int *_tmp;
		void _generar(int *vector);
		void _seleccionar();
	public:
		Colonia (int size, Punto *coordenadas);

		void setZanganoAsReina();
		void setHijoAsReina();

		inline double costoReina();
		inline double costoZangano();
		inline double costoHijo();

		void Cruzar();

		virtual ~Colonia();
};


Colonia::Colonia(int size, Punto *coordenadas): Mapa(size, coordenadas) {
	_reina 		= (int*) calloc ( _size, 4);
	_zangano 	= (int*) calloc ( _size, 4);
	_hijo 		= (int*) calloc ( _size, 4);

	for (int i = 0; i < _size; i++) {
		_reina[i] 	= i;
		_zangano[i]	= i;
		_hijo[i]	= i;
	}

	_generar(_reina);
	_costoReina = costo(_reina);
	print(_reina,_size);
}


void Colonia::_generar(int *vector) {
	for (int i = 0; i < _size; i++) {
		std::swap( vector[i], vector[ uniform_distribution(0, _size) ]);
	}
}


void Colonia::setZanganoAsReina() {
	_tmp = _reina;
	_reina = _zangano;
	_zangano = _tmp;
}


void Colonia::setHijoAsReina() {
	_tmp = _reina;
	_reina = _hijo;
	_zangano = _tmp;
}


inline double Colonia::costoReina() {
	return _costoReina;
}


inline double Colonia::costoZangano() {
	return _costoZangano;
}


inline double Colonia::costoHijo() {
	return _costoHijo;
}



Colonia::~Colonia() {
	free(_zangano);
	free(_reina);
	free(_hijo);
}
