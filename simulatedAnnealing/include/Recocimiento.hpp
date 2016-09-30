/*
*
*/
#include <algorithm>
#include "./../../geneticoBasico/include/tipos/Mapa.hpp"

class RecoSim: public Mapa {
	private:
		// variables relevantes
		int *_ruta, *_aux, *_tmp, *_moviendo, _aceptado, _maxAceptado, _maxTpasos, _maxPasos;

		double _costoRuta, _dist, _T, _congelante;

		int _media, _low, _up, _count, _Ncount;
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


	_moviendo	= (int*) calloc ( 6,  4);
	_aux		= (int*) calloc ( _size,  4);
	_ruta	 	= (int*) malloc ( _size * 4);

	for (int i = 0; i < _size; i++) {
		_ruta[i] = i;
	}

	_costoRuta = costo(_ruta);
	printf("Temperatura: %f, maxAceptados: %i,  costo: %f \n", _T, _aceptado, _costoRuta);
}


// mitad de la longitud del segmento a invertir
// the segment is reversed in the following way n[0]<->n[1], n[0]+1<->n[1]-1, n[0]+2<->n[1]-2,...
// Start at the ends of the segment and swap pairs of cities, moving towards the center.
void RecoSim::_invertir() {
	_media = (1 + ( (_moviendo[1] - _moviendo[0]) % _size) )/2;
	for (int j = 0; j < _media; j++) {
		_up 	= (_moviendo[0] + j) % _size;
		_low = (_moviendo[1] - j) % _size;
		std::swap( _ruta[_low], _ruta[ _up ]);
	}
}


void RecoSim::_transpt() {
	_count = 0;
	_up = (_moviendo[1] - _moviendo[0]) % _size;
	for (int i = 0; i <= _up; i++) {
		_aux[_count] = _ruta[ (i + _moviendo[0]) % _size ];
		_count++;
	}

	_up = (_moviendo[2] - _moviendo[5]) % _size;
	for (int i = 0; i <= _up; i++) {
		_aux[_count] = _ruta[ (i + _moviendo[5]) % _size ];
		_count++;
	}

	_up = (_moviendo[4] - _moviendo[3]) % _size;
	for (int i = 0; i <= _up; i++) {
		_aux[_count] = _ruta[ (i + _moviendo[3]) % _size ];
		_count++;
	}

	_tmp = _ruta;
	_ruta = _aux;
	_aux = _tmp;
}


void RecoSim::recocido(){

	for (int t = 0; t < _maxTpasos; t++) {

		_aceptado = 0;
		for (int i = 0; i < _maxPasos; i++) {
			while( 1 ) {
				_moviendo[0] = randInt(0, _size);
				_moviendo[1] = randInt(0, _size -1);

				if (_moviendo[1] < _moviendo[0]) {
					std::swap(_moviendo[0], _moviendo[1]);
				} else {
					_moviendo[1]++;
				}

				_Ncount = (_moviendo[0] + _size - _moviendo[1] - 1) % _size;

				if (_Ncount) {
					break;
				}
			}

			_moviendo[2] = (_moviendo[0] - 1) % _size;
			_moviendo[3] = (_moviendo[1] + 1) % _size;

			if (0.5 > randR()) {
				_dist = _distancias[_size * _ruta[_moviendo[2]] + _ruta[_moviendo[1]]] +
						_distancias[_size * _ruta[_moviendo[3]] + _ruta[_moviendo[0]]] -
						_distancias[_size * _ruta[_moviendo[2]] + _ruta[_moviendo[0]]] -
						_distancias[_size * _ruta[_moviendo[3]] + _ruta[_moviendo[1]]];

				if (_dist < 0 || ( exp(- _dist / _T) > randR())) {
					_aceptado++;
					_invertir();
				}
			} else {
				_moviendo[4] = (_moviendo[1] + 1 +  randInt(0, _Ncount - 1)) % _size;
				_moviendo[5] = (_moviendo[5] + 1) % _size;

				_dist = - 	_distancias[_size * _ruta[_moviendo[1]] + _ruta[_moviendo[3]]] -
							_distancias[_size * _ruta[_moviendo[0]] + _ruta[_moviendo[2]]] -
							_distancias[_size * _ruta[_moviendo[4]] + _ruta[_moviendo[5]]] +
							_distancias[_size * _ruta[_moviendo[0]] + _ruta[_moviendo[4]]] +
							_distancias[_size * _ruta[_moviendo[1]] + _ruta[_moviendo[5]]] +
							_distancias[_size * _ruta[_moviendo[2]] + _ruta[_moviendo[3]]];

				if (_dist < 0 || ( exp(- _dist / _T) > randR())) {
					_aceptado++;
					_transpt();
				}
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
	free(_moviendo);
	free(_ruta);
	free(_aux);
}
