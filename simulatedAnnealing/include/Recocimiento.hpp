#include <algorithm>
#include "./../../geneticoBasico/include/tipos/Mapa.hpp"

class RecoSim: public Mapa {
	private:
		// variables relevantes
		int *_ruta, *_aux, *_tmp, *_vecindad, _aceptado, _maxAceptado, _maxTpasos, _maxPasos;

		double _dist, _T, _congelante;

		int _media, _low, _up, _count, _numCiudadesOut;
		void _invertir();
		void _transpt();
	public:
		RecoSim(int size, Punto *coordenadas, int maxTsteps, double T, double congelante);
		void recocido();
		virtual ~RecoSim();
};

/*
*	Reservamos la memoria para los vectores e inicializamos con una ruta dummy
*/
RecoSim::RecoSim(int size, Punto *coordenadas, int maxTpasos, double T, double congelante): Mapa(size, coordenadas) {
	_size 			= size;					// Number of cities to visit
	_maxTpasos		= maxTpasos;			// Temperature is lowered not more than maxTsteps
	_T 				= T;		   			// Starting temperature - has to be high enough
	_congelante		= congelante;			// Factor to multiply temperature at each cooling step
	_maxPasos 		= 100 * _size; 			// Number of steps at constant temperature
	_maxAceptado 	= 10 * _size;  			// Number of accepted steps at constant temperature


	_vecindad	= (int*) calloc ( 6,  4);
	_aux		= (int*) calloc ( _size, 4);
	_ruta	 	= (int*) malloc ( _size * 4);

	for (int i = 0; i < _size; i++) {
		_ruta[i] = i;
	}

	printf("Temperatura: %f, maxAceptados: %i,  costo: %f \n", _T, _aceptado, costo(_ruta));
}


void RecoSim::_invertir() {
	// 1. take route[1] to route[i-1] and add them in order to new_route
	// no requerimos copia de la ruta, pues trabajamos directamente sobre _sinCruces
	// pero copiamos el segmento a reescribir en una memoria auxiliar

	for (_count = _vecindad[0]; _count <= _vecindad[1]; _count++) {
		_aux[_count] = _ruta[_count];
	}

	// 2. take route[i] to route[k] and add them in reverse order to new_route
	// reescribimos sobre la ruta el segmento en sentido inverso
	int auxCount = 0;
	for (_count = _vecindad[0]; _count <= _vecindad[1]; _count++) {
		_ruta[_count] = _aux[_vecindad[1] - auxCount];
		auxCount++;
	}

	// 3. take route[k+1] to end and add them in order to new_route
	// como trabajamos sobre la ruta no requerimos sobreescribir el resto de la misma
}


void RecoSim::recocido(){

	for (int t = 0; t < _maxTpasos; t++) {

		_aceptado = 0;
		for (int i = 0; i < _maxPasos; i++) {
			_vecindad[0] = randInt(0, _size);
			_vecindad[1] = randInt(0, _size -1);

			if (_vecindad[1] < _vecindad[0]) {
				std::swap(_vecindad[0], _vecindad[1]);
			} else {
				_vecindad[1]++;
			}

			_vecindad[2] = (_vecindad[0] - 1) % _size;
			_vecindad[3] = (_vecindad[1] + 1) % _size;

			if(_vecindad[2] == -1) {
				_vecindad[2] = _size - 1;
			}

			_dist = _distancias[_size * _ruta[_vecindad[2]] + _ruta[_vecindad[1]]] +
					_distancias[_size * _ruta[_vecindad[3]] + _ruta[_vecindad[0]]] -
					_distancias[_size * _ruta[_vecindad[2]] + _ruta[_vecindad[0]]] -
					_distancias[_size * _ruta[_vecindad[3]] + _ruta[_vecindad[1]]];

			if (_dist < 0 || ( exp(- _dist / _T) > randR())) {
				_aceptado++;
				_invertir();
			}


			if (_aceptado > _maxAceptado) {
				break;
			}
		}

		printf("temperatura: %f, maxAceptados: %i,  costo: %f \n", _T, _aceptado, costo(_ruta));
		_T *= _congelante;

		if (_aceptado == 0) {
			break;
		}
	}
	print(_ruta, _size);
}

/*
*	liberamos la memoria alojada
*/
RecoSim::~RecoSim() {
	free(_vecindad);
	free(_ruta);
	free(_aux);
}
