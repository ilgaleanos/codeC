/*
*	Esta función devuelve un entero seudo-aleatorio entre [rangeLow, rangeHigh)
*/
inline int uniform_distribution(int rangeLow, int rangeHigh) {
	return rand()/(1.0 + RAND_MAX) * (rangeHigh - rangeLow)  + rangeLow;
}
