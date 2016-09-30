/*
*	Objeto auxiliar, las coordenadas del ejercicio son un array de puntos
*	distancia := distancia euclidiana
*/
class Punto {
	private:
		float _x;
		float _y;
	public:
		Punto(const float &x, const float &y);
		inline float getX();
		inline float getY();
		inline void setX(const float &x);
		inline void setY(const float &y);
		inline float distancia (Punto *p);
};

Punto::Punto(const float &x, const float &y) {
	_x = x;
	_y = y;
}

inline float Punto::getX() {
	return _x;
}

inline float Punto::getY() {
	return _y;
}

inline void Punto::setX(const float &x) {
	_x = x;
}

inline void Punto::setY(const float &y) {
	_y = y;
}

/*
*	Calcula la distancia euclidiana entre dos puntos
*/
inline float Punto::distancia(Punto *p) {
	float Dx = (_x - p->_x), Dy = (_y - p->_y);
	return sqrt( (Dx * Dx) + (Dy * Dy) );
}
