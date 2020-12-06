#pragma once
#include <iostream>
#include <algorithm>

class MatrixException : public std::runtime_error {
public:
	MatrixException() : runtime_error("bad Matrices sizes") {}
};

struct Uninitialized {};
template<typename T, int N, int M>
class Matrix {
	T data[N * M];
public:
	Matrix(Uninitialized u) {
		std::cout << "constructor of static uninitialized matrix\n";
	}
	Matrix(int n, int m, Uninitialized u) {
		std::cout << "constructor of static uninitialized matrix\n";
	}
	Matrix() {
		std::fill(data, data + (N * M), T{});
		std::cout << "constructor of static " << N << " " << M << " matrix\n";
	}
	Matrix(const Matrix& a) {
		std::copy(a.data, a.data + (N * M), data);
		std::cout << "copy constructor of static " << N << " x " << M << " matrix\n";
	}
	Matrix(std::initializer_list<std::initializer_list<T>> init_list) {
		T* p = data;
		for (auto& i : init_list) {
			std::copy(i.begin(), i.end(), p);
			//std::fill(p + i.size(), p + M, T{});
			p += M;
		}
		std::cout << "constructor of static " << N << " x " << M << " matrix from initializer list\n";
	}
	explicit Matrix(const Matrix<T, 0, 0>& a) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				//this(i, j) = a(i, j);
				data[(i - 1) * M + (j - 1)] = a(i, j);
			}
		}
		std::cout << "explicit constructor of static " << N << " " << M << " matrix from dynamic\n";
	}
	T operator()(int i, int j) const {
		return data[(i - 1) * M + (j - 1)];
	}
	T& operator()(int i, int j) {
		return data[(i - 1) * M + (j - 1)];
	}
	int numberOfRows() const {
		return N;
	}
	int numberOfColumns()  const {
		return M;
	}
};

template<typename T, std::size_t N, std::size_t M, std::size_t N1, std::size_t M1, std::size_t N2, std::size_t M2>
Matrix<T, N, M> product(const Matrix<T, N1, M1>& a, const Matrix<T, N2, M2>& b) {
	Matrix<T, N, M> c(a.numberOfRows(), b.numberOfColumns(), Uninitialized{});
	for (int i = 1; i <= a.numberOfRows(); i++) {
		for (int j = 1; j <= b.numberOfColumns(); j++) {
			T tmp{};
			for (int k = 1; k <= a.numberOfColumns(); k++) {
				tmp += a(i, k) * b(k, j);
			}
			c(i, j) = tmp;
		}
	}
	return c;
}

template<typename T, std::size_t N1, std::size_t M1, std::size_t M2>
Matrix<T, N1, M2> operator*(const Matrix<T, N1, M1>& a, const Matrix<T, M1, M2>& b) {
	return product<T, N1, M2>(a, b);
}

template<typename T, std::size_t N, std::size_t M, std::size_t N1, std::size_t M1, std::size_t N2, std::size_t M2>
Matrix<T, N, M> sum(const Matrix<T, N1, M1>& a, const Matrix<T, N2, M2>& b) {
	Matrix<T, N, M> c(a.numberOfRows(), b.numberOfColumns(), Uninitialized{});
	//Matrix <T, N,M> c = a;
	for (int i = 1; i <= a.numberOfRows(); i++) {
		for (int j = 1; j <= a.numberOfColumns(); j++) {
			//c(i, j) += b(i, j);
			c(i, j) = a(i, j) + b(i, j);
		}
	}
	return c;
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& a, const Matrix<T, N, M>& b) {
	return sum<T, N, M>(a, b);
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, M, N> transpose(const Matrix<T, N, M>& a) {
	Matrix<T, M, N> b(a.numberOfColumns(), a.numberOfRows(), Uninitialized{});
	for (int i = 1; i <= a.numberOfRows(); i++) {
		for (int j = 1; j <= a.numberOfColumns(); j++) {
			b(j, i) = a(i, j);
		}
	}
	return b;
}
