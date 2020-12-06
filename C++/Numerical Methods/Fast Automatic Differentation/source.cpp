//Natalia Durlik
#include "funkcja.h"
#include <iostream>
#include <cmath>

using namespace std;

class Jet {
public:
	double f;
	double fx;
	double fy;
	double fxx;
	double fxy;
	double fyy;
	Jet() = default;
	Jet(double c) : f(c), fx(0.0), fy(0.0), fxx(0.0), fxy(0.0), fyy(0.0) {}
	Jet(double val, bool is_x) :f(val), fx(is_x ? 1.0 : 0.0), fy(is_x ? 0.0 : 1.0), fxx(0.0), fxy(0.0), fyy(0.0) {}
	double operator[](unsigned n) const {
		if (n == 0) return f;
		if (n == 1) return fx;
		if (n == 2) return fy;
		if (n == 3) return fxx;
		if (n == 4) return fxy;
		if (n == 5) return fyy;
		return f;
	}
	double& operator[](unsigned n) {
		if (n == 0) return f;
		if (n == 1) return fx;
		if (n == 2) return fy;
		if (n == 3) return fxx;
		if (n == 4) return fxy;
		if (n == 5) return fyy;
		return f;
	}
	Jet operator-() const{
		Jet c = *this;
		for (unsigned i = 0; i < 6; i++) {
			c[i] = -c[i];
		}
		return c;
	}
};

Jet operator+(const Jet& a, const Jet& b) {
	Jet c(a);
	for (unsigned i = 0; i < 6; i++) {
		c[i] += b[i];
	}
	return c;
}

Jet operator-(const Jet& a, const Jet& b) {
	Jet c(a);
	for (unsigned i = 0; i < 6; i++) {
		c[i] -= b[i];
	}
	return c;
}

Jet operator*(const Jet& a, const Jet& b) {
	Jet c;
	c.f = a.f * b.f;
	c.fx = a.fx * b.f + b.fx * a.f;
	c.fy = a.fy * b.f + b.fy * a.f;
	c.fxx = a.fxx * b.f + 2 * b.fx * a.fx + b.fxx * a.f;
	c.fxy = a.fxy * b.f + a.fx * b.fy + b.fx * a.fy + b.fxy * a.f;
	c.fyy = a.fyy * b.f + 2 * b.fy * a.fy + b.fyy * a.f;
	return c;
}

Jet operator/(const Jet& a, const Jet& b) {
	Jet c;
	c.f = a.f / b.f;
	c.fx = (a.fx - b.fx * c.f) / b.f;
	c.fy = (a.fy - b.fy * c.f) / b.f;
	c.fxx = (a.fxx - 2 * b.fx * c.fx - b.fxx * c.f) / b.f;
	c.fxy = (a.fxy - b.fx * c.fy - b.fy * c.fx - b.fxy * c.f) / b.f;
	c.fyy = (a.fyy - 2 * b.fy * c.fy - b.fyy * c.f) / b.f;
	return c;
}

std::ostream& operator<<(std::ostream& out, const Jet& a) {
	for (unsigned i = 0; i < 6; i++) {
		out << a[i] << " ";
	}
	return out;
}

Jet sin(const Jet& a) {
	Jet c;
	c.f = std::sin(a.f);
	double cos_af = std::cos(a.f);
	c.fx = a.fx * cos_af;
	c.fy = a.fy * cos_af;
	c.fxx = a.fxx * cos_af - a.fx * a.fx * c.f;
	c.fxy = a.fxy * cos_af - a.fx * a.fy * c.f;
	c.fyy = a.fyy * cos_af - a.fy * a.fy * c.f;
	return c;
}

Jet cos(const Jet& a) {
	Jet c;
	c.f = std::cos(a.f);
	double sin_af = std::sin(a.f);
	c.fx = -a.fx * sin_af;
	c.fy = -a.fy * sin_af;
	c.fxx = -(a.fxx * sin_af + a.fx * a.fx * c.f);
	c.fxx = -(a.fxx * sin_af + a.fx * a.fx * c.f);
	c.fxy = -(a.fxy * sin_af + a.fx * a.fy * c.f);
	c.fyy = -(a.fyy * sin_af + a.fy * a.fy * c.f);
	return c;
}

Jet exp(const Jet& a) {
	Jet c;
	c.f = std::exp(a.f);
	c.fx = a.fx * c.f;
	c.fy = a.fy * c.f;
	c.fxx = a.fxx * c.f + c.fx * a.fx;
	c.fxy = a.fxy * c.f + c.fx * a.fy;
	c.fyy = a.fyy * c.f + c.fy * a.fy;
	return c;
}


int main() {
	int M;
	cin >> M;
	cout.precision(15);
	while (M--) {
		double x, y;
		cin >> x >> y;
		cout << funkcja(Jet(x, true), Jet(y, false)) << endl;
	}
}