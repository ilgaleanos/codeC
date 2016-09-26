/*
*	Objeto auxiliar, las coordenadas del ejercicio son un array de puntos
*	distancia := distancia euclidiana
*/
class Punto {
	private:
		int _x;
		int _y;
	public:
		Punto(int x, int y);
		inline int getX();
		inline int getY();
		inline void setX(int x);
		inline void setY(int y);
		inline double distancia (Punto *p);
};

Punto::Punto(int x, int y) {
	_x = x;
	_y = y;
}

inline int Punto::getX() {
	return _x;
}

inline int Punto::getY() {
	return _y;
}

inline void Punto::setX(int x) {
	_x = x;
}

inline void Punto::setY(int y) {
	_y = y;
}

inline double Punto::distancia(Punto *p) {
	int Dx = (_x - p->_x), Dy = (_y - p->_y);
	return sqrt( (Dx * Dx) + (Dy * Dy) );
}
