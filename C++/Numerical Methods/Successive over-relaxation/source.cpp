//Natalia Durlik
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print_vector(const vector<double>& x) {
	for (int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}
}

struct Matrix {
	vector<vector<double>> data;
	int N;
	int M;//wstegi
	Matrix(int N_, int M_) :data(M_), N(N_), M(M_) {
		for (int i = 0; i < M / 2; i++) {
			data[i].resize(N + i - (M / 2));
			data[M - 1 - i].resize(N + i - (M / 2));
		}
		data[M / 2].resize(N);
	}
	int size() const { return M; }
	double operator ()(int i, int j) const {
		int idx = M / 2 + i - j;
		if (idx < M && idx >= 0) {
			if (i - j < 0) return data[M / 2 + i - j][i];
			return data[M / 2 + i - j][j];
		}
		return data[0][0];
	}
	double& operator ()(int i, int j) {
		int idx = M / 2 + i - j;
		if (idx < M && idx >= 0) {
			if (i - j < 0) return data[M / 2 + i - j][i];
			return data[M / 2 + i - j][j];
		}
		return data[0][0];
	}
};


void SOR(const Matrix& A, const vector<double>& b, const vector<double>& x0, int L, double w) {
	vector<double> x = x0;
	int n = b.size();
	int m = A.size();
	for (int iter = 0; iter < L; iter++) {
		for (int i = 0; i < n; i++) {
			auto sum = b[i];
			for (int j = std::max(0, i - m / 2); j < i; j++) {
				sum -= A(i, j) * x[j];
			}
			for (int j = i + 1; j < std::min(n, i + m / 2 + 1); j++) {
				sum -= A(i, j) * x[j];
			}
			x[i] = (1 - w) * x[i] + w * sum / A(i, i);
		}
	}
	print_vector(x);
}

int main() {
	int N, M, L;
	double w;
	cin >> N;
	cin >> M;
	Matrix matrix(N, M);
	vector<double> x0(N);
	vector<double> b(N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < matrix.data[i].size(); j++) {
			cin >> matrix.data[i][j];
		}
	}
	for (int i = 0; i < N; i++) cin >> b[i];
	for (int i = 0; i < N; i++) cin >> x0[i];
	cin >> w;
	cin >> L;
	std::cout.precision(16);
	SOR(matrix, b, x0, L, w);
}