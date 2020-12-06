#pragma once
#include "staticMatrix.h"

template<typename T>
class Matrix <typename T, 0, 0> {
	int n;
	int m;
	T* data = nullptr;
public:
	Matrix(int n_, int m_, Uninitialized u) :n(n_), m(m_) {
		data = new T[n * m];
		std::cout << "constructor of dynamic uninitialized matrix\n";
	}
	Matrix() = default;
	Matrix(int n_, int m_) : n(n_), m(m_) {
		data = new T[n * m];
		for (int i = 0; i < n * m; i++) {
			data[i] = T{};
		}
		std::cout << "constructor of " << n << " x " << m << " dynamic matrix\n";
	}
	Matrix(std::initializer_list<std::initializer_list<T>> init_list) : n(init_list.size()) {
		int maxi = 0;
		for (auto i = init_list.begin(); i != init_list.end(); i++) {//data_[] doesnt work
			if (i->size() > maxi) maxi = i->size();
		}
		m = maxi;
		std::cout << "constructor of " << n << " x " << m << " dynamic matrix  from initializer_list\n";
		data = new T[n * m];
		T* p = data;
		for (auto& i : init_list) {
			std::copy(i.begin(), i.end(), p);
			std::fill(p + i.size(), p + m, 0.0);
			p += m;
		}
	}
	Matrix(const Matrix& a) :n(a.n), m(a.m) {
		std::cout << "copy constructor of " << n << " x " << m << " matrix" << std::endl;
		data = new T[n * m];
		std::copy(a.data, a.data + (n * m), data);
	}
	Matrix(Matrix&& a) : n(a.n), m(a.m) {
		data = a.data;
		a.data = nullptr;
		std::cout << "move constructor of " << n << " x " << m << " matrix\n";
	}
	template<std::size_t N, std::size_t M>
	explicit Matrix(const Matrix<T, N, M>& a) : n(N), m(M) {
		data = new T[n * m];
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				data[(i - 1) * m + (j - 1)] = a(i, j);
			}
		}
		std::cout << "explicit constructor of dynamic " << N << " " << M << " matrix from static\n";
	}
	~Matrix() {
		delete[] data;
	}
	Matrix& operator=(Matrix&& a) {
		if (&a != this) {//never happens? FIXME
			delete[] data;
			data = a.data;
			n = a.n;
			m = a.m;
			a.data = nullptr;
		}
		std::cout << "move assignment\n";
		return *this;
	}
	friend Matrix<T, 0, 0> operator+(const Matrix<T, 0, 0>& a, const Matrix<T, 0, 0>& b) {
		if (a.numberOfColumns() != b.numberOfColumns() || a.numberOfRows() != b.numberOfRows()) throw MatrixException();
		return sum<T,0,0>(a,b);
	}
	friend Matrix<T, 0, 0> operator*(const Matrix<T, 0, 0>& a, const Matrix<T, 0, 0>& b) {
		if (a.numberOfColumns() != b.numberOfRows()) throw MatrixException();
		return product<T,0,0>(a,b);
	}
	T operator()(int i, int j) const {
		return data[(i - 1) * m + (j - 1)];
	}
	T& operator()(int i, int j) {
		return data[(i - 1) * m + (j - 1)];
	}
	int numberOfRows() const {
		return n;
	}
	int numberOfColumns() const {
		return m;
	}
};

template<typename T, std::size_t N, std::size_t M>
Matrix<T, 0, 0> operator*(const Matrix<T, 0, 0>& a, const Matrix<T, N, M>& b) {
	if (a.numberOfColumns() != b.numberOfRows()) throw MatrixException();
	return product<T, 0, 0>(a, b);
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, 0, 0> operator*(const Matrix<T, N, M>& a, const Matrix<T, 0, 0>& b) {
	if (a.numberOfColumns() != b.numberOfRows()) throw MatrixException();
	return product<T, 0, 0>(a, b);
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> operator+(const Matrix<T, 0, 0>& a, const Matrix<T, N, M>& b) {
	if (a.numberOfColumns() != b.numberOfColumns() || a.numberOfRows() != b.numberOfRows()) throw MatrixException();
	return sum<T, N, M>(a, b);
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& a, const Matrix<T, 0, 0>& b) {
	if (a.numberOfColumns() != b.numberOfColumns() || a.numberOfRows() != b.numberOfRows()) throw MatrixException();
	return sum<T, N, M>(a, b);
}
