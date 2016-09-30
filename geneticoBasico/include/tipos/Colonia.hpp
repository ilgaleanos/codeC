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
		int *_reina, *_zangano, *_hijo, *_sinCruces , *_aux;
		double _costoReina, _costoZangano, _costoHijo, _costoSinCruces;

		// auxiliares
		int *_tmp;
		int _count;
		double _dReina, _dZangano;
		int _indexReina, _indexZangano;

		void _generar(int *vector);
		int _index(int *v, int el);
		bool _contenido(int *v, int el, int limit );
		void _asignarEntero(int *v, int limit);
		void _optSwap(int i, int k);
	public:
		Colonia (int size, Punto *coordenadas);

		void setZanganoAsReina();
		void setHijoAsReina();
		void setSinCrucesAsReina();

		inline double costoReina();
		bool cruzar();
		bool opt2();
		virtual ~Colonia();
};


Colonia::Colonia(int size, Punto *coordenadas): Mapa(size, coordenadas) {
	_reina 		= (int*) calloc ( _size, 4);
	_zangano 	= (int*) calloc ( _size, 4);
	_hijo 		= (int*) calloc ( _size, 4);
	_sinCruces	= (int*) calloc ( _size, 4);
	_aux		= (int*) calloc ( _size, 4);

	for (int i = 0; i < _size; i++) {
		_reina[i] 		= i;
		_zangano[i]		= i;
		_hijo[i]		= i;
		_sinCruces[i]	= i;
	}

	_generar(_reina);
	_costoReina = costo(_reina);

	print(_reina,_size);
	print(_costoReina);
}


void Colonia::_generar(int *vector) {
	for (int i = 0; i < _size; i++) {
		std::swap( vector[i], vector[ uniform_distribution(0, _size) ]);
	}
	return;
}


void Colonia::setZanganoAsReina() {
	_tmp = _reina;
	_reina = _zangano;
	_zangano = _tmp;
	return;
}


void Colonia::setHijoAsReina() {
	_tmp = _reina;
	_reina = _hijo;
	_hijo = _tmp;
	return;
}


void Colonia::setSinCrucesAsReina() {
	_tmp = _reina;
	_reina = _sinCruces;
	_sinCruces = _tmp;
	return;
}


inline double Colonia::costoReina() {
	return _costoReina;
}


int Colonia::_index(int *v, int el) {
	for (int i = 0; i < _size; i++) {
		if( v[i] == el ){
			return i;
		}
	}
	return -1;
}


bool Colonia::_contenido(int *v, int el, int limit ) {
	if (v[_size-1] == el) {
		return true;
	}
	for (size_t i = 0; i < limit; i++) {
		if (v[i] == el) {
			return true;
		}
	}
	return false;
}


void Colonia::_asignarEntero(int *v, int limit) {
	for (int i = 0; i < _size; i++) {
		if( v[_size-1] != i && _contenido(v, i, limit) == false){
			v[limit] = i;
			return;
		}
	}
	return;
}


bool Colonia::cruzar() {

	_generar(_zangano);
	_costoZangano = costo(_zangano);

	if( _costoZangano < _costoReina) {
		setZanganoAsReina();
		_costoReina = _costoZangano;
		print(_reina,_size);
		print(_costoReina);
		return true;
	}

	if( _distancias[ _size * _reina[_size-1] + _reina[0]] < _distancias[ _size * _zangano[_size-1] + _zangano[0]] ) {
		_hijo[_size-1] = _reina[_size-1];
		_hijo[0] = _reina[0];
	} else {
		_hijo[_size-1] = _zangano[_size-1];
		_hijo[0] = _zangano[0];
	}

	_count = 0;
	while( _count < _size -1) {

		_indexReina = _index(_reina, _hijo[_count]);
		_indexZangano = _index(_zangano, _hijo[_count]);

		if (_indexReina == _size-1) {
			_dReina = _distancias[ _size * _reina[_size-1] + _reina[0]];
			_indexReina = -1;
		} else {
			_dReina = _distancias[ _size * _reina[_indexReina] + _reina[_indexReina+1]];
		}

		if (_indexZangano == _size-1) {
			_dZangano = _distancias[ _size * _zangano[_size-1] + _zangano[0]];
			_indexZangano = -1;
		} else {
			_dZangano = _distancias[ _size * _zangano[_indexZangano] + _zangano[_indexZangano+1]];
		}


		if( _dReina < _dZangano ) {
			// si no esta contenido el index de la reina
			if( ! _contenido( _hijo, _reina[_indexReina+1], _count)) {
				_hijo[_count+1] = _reina[_indexReina+1];

			// si no esta contenido el index del zangano
			} else if( ! _contenido( _hijo, _zangano[_indexZangano+1], _count)) {
				_hijo[_count+1] = _zangano[_indexZangano+1];

			// completamos con un digito
			} else if(_count < _size-2) {
				_asignarEntero(_hijo, _count+1);
			}

		} else {
			// si no esta contenido el index del zangano
			if( ! _contenido( _hijo, _zangano[_indexZangano+1], _count)) {
				_hijo[_count+1] = _zangano[_indexZangano+1];

			// si no esta contenido el index de la reina
			} else if( ! _contenido( _hijo, _reina[_indexReina+1], _count)) {
				_hijo[_count+1] = _reina[_indexReina+1];

			// completamos con un digito
			} else if(_count < _size-2) {
				_asignarEntero(_hijo, _count+1);
			}

		}
		_count++;
	}

	// verificamos si nació una nueva reina
	_costoHijo = costo(_hijo);
	if( _costoHijo < _costoReina) {;
		setHijoAsReina();
		_costoReina = _costoHijo;
		print(_reina,_size);
		print(_costoReina);
		return true;
	}

	return false;
}


void Colonia::_optSwap(int i, int k) {
	// 1. take route[1] to route[i-1] and add them in order to new_route

	for (_count = i; _count <= k; _count++) {
		_aux[_count] = _sinCruces[_count]; // copiamos datos
	}

	// 2. take route[i] to route[k] and add them in reverse order to new_route
	int auxCount = 0;
	for (_count = i; _count <= k; _count++) {
		_sinCruces[_count] = _aux[k - auxCount];
		auxCount++;
	}

	// 3. take route[k+1] to end and add them in order to new_route
}


bool Colonia::opt2() {
	for (int i = 0; i < _size; i++) {
		_sinCruces[i] = _reina[i];
	}

	for (int i = 0; i < _size - 1; i++) {
		for (int k = i + 1; k < _size ; k++) {
			_optSwap( i, k);
			_costoSinCruces = costo(_sinCruces);
			if (_costoSinCruces < _costoReina) {
				setSinCrucesAsReina();
				_costoReina = _costoSinCruces;
				print(_reina,_size);
				print(_costoReina);
				return true;
			}
		}
	}

	return false;
}



Colonia::~Colonia() {
	free(_zangano);
	free(_reina);
	free(_hijo);
	free(_sinCruces);
	free(_aux);
}
