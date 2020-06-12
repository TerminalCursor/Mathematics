#include "General.h"

double d_pow(double x, int p) {
	if(p == 0)
		return 1.0f;
	if(p > 1)
		return x * d_pow(x, p - 1);
	else
		return x;
}

long l_pow(long x, long p) {
	if(p == 0)
		return 1;
	if(p > 1)
		return x * l_pow(x, p - 1);
	else
		return x;
}

double square_root(double n) {
	double i, precision = 0.00001;

	for(i = 1; i*i <= n; ++i);

	for(--i; i*i < n; i+= precision);

	return i;
}

int gcd(int a, int b) {
	if(a < b)
		return gcd(b, a);
	else {
		int r = a % b;
		if(r == 0)
			return b;
		else
			return gcd(b, r);
	}
}
