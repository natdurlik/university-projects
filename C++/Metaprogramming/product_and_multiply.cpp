#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

template<typename T, int I, int N>
struct DPFor {
	static T loop(T* a, T* b) {
		return a[I] * b[I] + DPFor<T, I + 1, N>::loop(a, b);
	}
};

template<typename T, int N>
struct DPFor<T, N, N> {
	static T loop(T* a, T* b) {
		return T{};//0
	}
};

template<typename T, int I, int J,int N, int M>
struct MultForJ {
	static T loop(T* m, T* x) {
		return m[I * M + J] * x[J] + MultForJ<T, I, J + 1, N, M>::loop(m, x);
	}
};

template<typename T, int I, int N, int M>
struct MultForJ<T,I,M,N,M> {
	static T loop(T* m, T* x) {
		return T{};//0
	}
};

template<typename T,int I, int N, int M>
struct MultForI {
	static void loop(T*m,T*x,T*y) {
		y[I] = MultForJ<T, I, 0, N, M>::loop(m, x);
		MultForI<T, I + 1, N, M>::loop(m,x,y);
	}
};

template<typename T, int N, int M>
struct MultForI<T,N,N,M> {
	static void loop(T* m, T* x, T* y) {}
};

template<int N, typename T> //tried using struct DotProduct, but operator() cannot be static
T DotProduct(T* a, T* b) {
	return DPFor<T, 0, N>::loop(a, b);
}

template<int N, int M, typename T>
void Multiply(T* matrix, T* x, T* y) {
	MultForI<T,0,N,M>::loop(matrix, x, y);
}

int main() {
	double a[] = { 1, 2, 3 };
	double b[] = { 1, 1, 1 };
	std::cout << DotProduct<3>(a, b) << std::endl; // 6 

	double x[] = { 1, 1, 0 };
	double A[] = { 1, 0, 0,
	 2, -5, 1 };
	double y[2];
	Multiply<2, 3>(A, x, y);
	std::cout << y[0] << " " << y[1]; // 1 -3
}


/*template<typename T, int I, int N>
struct For {
	static T loop(T* data) {
		return std::max(data[I], For<T, I + 1, N>::loop(data));
	}
};

template<typename T, int N>
struct For<T, N, N> {
	static T loop(T* data) {
		return std::numeric_limits<T>::min();
	}
};

template<int N, typename T>
struct Max {
	static T find(T* data) {
		return For<T, 0, N>::loop(data);
	}
};*/

/*template<int N, typename T>
struct DotProduct {
	static T prod(T* a, T* b) {
		return DPFor<T, 0, N>::loop(a, b);
	}
};*/