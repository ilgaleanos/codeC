/*
*	Este objeto se almacenara la mejor ruta, se generarán y se cruzarán rutas
*	Hereda de Mapa que aunque no es una herencia clara se necesita la función
*	costo, y la matriz distancias las cuales pertenecen a mapa además de _size.
*	_size := número de ciudades heredado de mapa
*	_reina := mejor ruta encontrada
*	_zangano := ruta generada de forma seudo-aleatoria
*	_hijo := ruta obtenida por medio de cruce
*	_sinCruces := copia de la reina para 2opt
*	_aux := memoria auxiliar del reverso de ruta
*	Entiéndase como gen la distancia entre dos ciudades
*	_dReina := valor de un gen de la reina
*	_dZangano := valor de un gen del zangano
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

		void _generar(int *v);
		int _index(int *v, const int &el);
		bool _contenido(int *v, const int &el, const int &limit );
		void _asignarEntero(int *v, const int &limit);
		void _optSwap(const int &i, const int &k);
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

/*
*	Reservamos la memoria para los vectores e inicializamos con una ruta dummy
*/
Colonia::Colonia(int size, Punto *coordenadas): Mapa(size, coordenadas) {
	_reina 		= (int*) malloc ( _size * 4);
	_zangano 	= (int*) malloc ( _size * 4);
	_hijo 		= (int*) malloc ( _size * 4);
	_sinCruces	= (int*) malloc ( _size * 4);
	_aux		= (int*) malloc ( _size * 4);

	// no usamos calloc pues el costo de inicializar mejor lo usamos para
	// inicializar a nuestra necesidad en particular en el siguiente for
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

/*
*	Hacemos una barajada del vector para generar nuevas rutas
*/
void Colonia::_generar(int *v) {
	for (int i = 0; i < _size; i++) {
		std::swap( v[i], v[ randInt(0, _size) ]);
	}
	return;
}

/*
*	Hacemos del zangano la nueva reina
*/
void Colonia::setZanganoAsReina() {
	_tmp = _reina;
	_reina = _zangano;
	_zangano = _tmp;
	return;
}

/*
*	Hacemos del hijo la nueva reina
*/
void Colonia::setHijoAsReina() {
	_tmp = _reina;
	_reina = _hijo;
	_hijo = _tmp;
	return;
}

/*
*	Hacemos de la ruta del 2opt la nueva reina
*/
void Colonia::setSinCrucesAsReina() {
	_tmp = _reina;
	_reina = _sinCruces;
	_sinCruces = _tmp;
	return;
}

/*
*	getter del costo de la reina
*/
inline double Colonia::costoReina() {
	return _costoReina;
}

/*
*	Retorna la posicion de una ciudad dentro de la ruta
*/
int Colonia::_index(int *v, const int &el) {
	for (int i = 0; i < _size; i++) {
		if( v[i] == el ){
			return i;
		}
	}
	return -1;
}

/*
*	Nos indica si la una ciudad ya se ha visitado
*/
bool Colonia::_contenido(int *v, const int &el, const int &limit ) {
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

/*
*	Nos hace visitar una ciudad que no hayamos visitado
*/
void Colonia::_asignarEntero(int *v, const int &limit) {
	for (int i = 0; i < _size; i++) {
		if( v[_size-1] != i && _contenido(v, i, limit) == false){
			v[limit] = i;
			return;
		}
	}
	return;
}

/*
*	funcion de cruce y selección entre zanganos generados aleatoriamente y la
*	reina de la colonia (mejor ruta), el algoritmo de cruce se basa en la
*	comparación de cada gen representado por la distancia entre dos ciudades
*	el algoritmo escoge al mejor de los dos (distancia mas cercana), y se lo
*	asigna al hijo. Tanto si el zangano como el hijo son mejores que la reina
*	actual, se realiza un cambio de reina.
*/
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

/*
*	cambio de orden de una sección de la ruta, funcion auxiliar de opt2
*/
void Colonia::_optSwap(const int &i, const int &k) {
	// 1. take route[1] to route[i-1] and add them in order to new_route
	// no requerimos copia de la ruta, pues trabajamos directamente sobre _sinCruces
	// pero copiamos el segmento a reescribir en una memoria auxiliar

	for (_count = i; _count <= k; _count++) {
		_aux[_count] = _sinCruces[_count];
	}

	// 2. take route[i] to route[k] and add them in reverse order to new_route
	// reescribimos sobre la ruta el segmento en sentido inverso
	int auxCount = 0;
	for (_count = i; _count <= k; _count++) {
		_sinCruces[_count] = _aux[k - auxCount];
		auxCount++;
	}

	// 3. take route[k+1] to end and add them in order to new_route
	// como trabajamos sobre la ruta no requerimos sobreescribir el resto de la misma
}

/*
*	Esta funcion es una ayudante en la busqueda global que lleva el algoritmo
*	genético pues el algoritmo genético es muy poco capaz de solucionar cruces
*	cuando alcanza cierta optimización de manera que con esta heurística
*	evitamos caer más facilmente en minimos locales y le damos al genético la
*	posibilidad de buscar en un espectro un poco más ámplio
*/
bool Colonia::opt2() {
	// sobre costo de trabajar sobre la misma ruta, note que aunque lo generamos
	// en esta parte nos evitamos el sobrecosto de la funcion _optSwap que esta
	// siendo invocada un mayor número de veces
	for (int i = 0; i < _size; i++) {
		_sinCruces[i] = _reina[_size - i - 1];
	}

	for (int i = 0; i < _size - 1; i++) {
		for (int k = i + 1; k < _size ; k++) {
			_optSwap( i, k);
			_costoSinCruces = costo(_sinCruces);

			// asignacion de la nueva reina en caso de generarse
			if (_costoSinCruces < _costoReina) {
				setSinCrucesAsReina();
				_costoReina = _costoSinCruces;
				print(_reina,_size);
				print(_costoReina);
				return true;

			// rollback de la inversion del segmento de ruta
			} else {
				int auxCount = 0;
				for (_count = i; _count <= k; _count++) {
					_sinCruces[_count] = _reina[_size - _count -1];
					auxCount++;
				}
				_costoSinCruces = _costoReina;
			}
		}
	}

	return false;
}


/*
*	liberamos la memoria alojada
*/
Colonia::~Colonia() {
	free(_zangano);
	free(_reina);
	free(_hijo);
	free(_sinCruces);
	free(_aux);
}
