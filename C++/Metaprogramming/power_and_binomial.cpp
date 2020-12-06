#include <iostream>

template<int N, int P>
struct Power {
	static const long long value = N * Power<N, P - 1>::value;
};

template<int N>
struct Power<N, 1> {
	static const long long value = N;
};

constexpr long long  power(int n, int p) {
	long long s = n;
	for (int i = 1; i < p; i++) {
		s *= n;
	}
	return s;
}


template<int N, int K>
struct Binomial {
	static const long long value = Binomial<N - 1, K>::value + Binomial<N - 1, K - 1>::value;
};

template<int N>
struct Binomial<N, 1> {
	static const long long value = N;
};

template<int N>
struct Binomial<N, 0> {
	static const long long value = 1;
};

template<int N>
struct Binomial<N, N> {
	static const long long value = 1;
};

constexpr long long binomial(int n, int k) {
	if (k == 0 || n == k) return 1;
	else if (k == 1) return n;
	else if (k > n) return 0;
	return binomial(n - 1, k) + binomial(n - 1, k - 1);
}


int main() {
	std::cout << Power<5, 3>::value << std::endl; // 125
	std::cout << Power<100, 1>::value << std::endl; // 100
	std::cout << Power<2, 10>::value << std::endl; // 1024
	constexpr int p = power(2, 10);
	std::cout << Binomial<4, 2>::value << std::endl; //6
	std::cout << Binomial<20, 5>::value << std::endl; //15504
	std::cout << Binomial<100, 0>::value << std::endl; //1
	std::cout << Binomial<100, 1>::value << std::endl; //100
	std::cout << Binomial<100, 7>::value << std::endl;  //16007560800
	constexpr int b = binomial(10, 2);
}