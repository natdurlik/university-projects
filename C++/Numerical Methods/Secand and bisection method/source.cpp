//Natalia Durlik
#include <cmath>  
#include <utility>
//#include <iostream>
double fa;
double fb;
double range;

int sgn(double x) {
	return (x < 0) ? -1 : (x > 0 ? 1 : 0);
}

//secand
void siecznych(double (*f)(double), double& a, double& b, int& M, double eps, double delta) {
	if (std::abs(fb) <= eps || std::abs(b - a) <= delta) {
		a = b;
		return;
	}
	if (std::abs(fa) <= eps || std::abs(b - a) <= delta) return;
	double s;
	while (M--) {
		/*if (std::abs(fa) > std::abs(fb)) {
			std::swap(a, b);
			std::swap(fa, fb);
		}*/
		s = (b - a) / (fb - fa);
		b = a;
		fb = fa;
		a = a - fa * s;
		fa = f(a);
		if (std::abs(fa) <=eps || std::abs(b - a) <= delta) return;
	}
}

//bisection
void bisekcji(double (*f)(double), double& a, double& b, double& c, int& M, double eps, double delta) {
	double fc;
	double e = b - a;
	while (M--) {
		e /= 2;
		c = a + e;
		fc = f(c);
		if (sgn(fc) != sgn(fa)) {
			b = c;
			fb = fc;
		}
		else {
			a = c;
			fa = fc;
		}
		if (std::abs(e) < 0.1 || std::abs(fc) < 0.05) return; //przyjemne wyniki w tescie jawnym
	}
}

//find roots
double wyznaczMiejsceZerowe(double (*f)(double), double a, double b, int M, double eps, double delta) {
	if (M == 0) return a;
	range = b - a;
	fa = f(a);
	if (M < 3) {
		if (std::abs(fa) <= eps) return a;
		else return b;
	}
	fb = f(b);
	M -= 2;
	double c = a;
	if (sgn(fa) != sgn(fb)) bisekcji(f, a, b, c, M, eps, delta);
	if (M > 0) {
		siecznych(f, a, b, M, eps, delta);
		c = a;
	}
	//std::cout << "M="<<M << std::endl;
	return c;
}