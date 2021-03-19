//Natalia Durlik

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>  

using namespace std;


const int N = 100000000;
const int R = 1000;
int M = 0;


double x[N];
double y[N];
int pixels[R][R];

inline double t(int i) {
	return 6.0 / (x[i] * x[i] + y[i] * y[i] + 1);
}

inline void next_x(int i, double u) {
	x[i] = 1 + u * (x[i - 1] * cos(t(i - 1)) - y[i - 1] * sin(t(i - 1)));
}

inline void next_y(int i, double u) {
	y[i] = u * (x[i - 1] * sin(t(i - 1)) + y[i - 1] * cos(t(i - 1)));
}

inline int x_to_coords(double x) {
	return (x + 1.0) * 333.33;
}

inline int y_to_coords(double y) {
	return (y + 1.5) * 285.7;
}

void generate_points(double u) {
	for (int i = 1; i < N; i++) {
		next_x(i, u);
		next_y(i, u);

		int xc = x_to_coords(x[i]);
		int yc = y_to_coords(y[i]);

		if (xc >= 0 && xc < R && yc >= 0 && yc < R) {
			pixels[xc][yc]++;
			M = max(pixels[xc][yc], M);
		}
	}
}

void load_to_file(double u) {

	static int num = 0;
	num++;

	ofstream file;
	file.open("u" + to_string(num) + ".txt");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < R; j++) {
			file << 1.0 - (double)((double)pixels[i][j] / (double)M);
			if (j != R - 1) file << ", ";
		}
		if (i != R - 1) file << "\n";
	}
	file.close();
}

void reset_pixels() {
	M = 0;
	x[0] = 0.0;
	y[0] = 0.0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < R; j++) {
			pixels[i][j] = 0;
		}
	}
}


int main() {

	for (double u = 0.6; u < 1.0; u += 0.001) {
		reset_pixels();
		generate_points(u);
		load_to_file(u);
	}
}