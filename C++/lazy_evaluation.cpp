#include <iostream>
#include <algorithm>
using namespace std;

template <int N>
class Vector {
	int data[N];
public:
	Vector() {
		cout << " Default constr" << endl;
	}
	Vector(std::initializer_list<int> list) {
		cout << " Init list constr" << endl;
		auto it = list.begin();
		for (int i = 0; i < N; i++) {
			data[i] = *it++;
		}
	}
	Vector(const Vector& m) {
		std::copy(m.data, m.data + N, data);
		cout << " Copy constr" << endl;
	}
	int operator[](int index) const {
		return data[index];
	}
	int& operator[](int index) {
		return data[index];
	}
	friend ostream& operator << (ostream& out, const Vector& m) {
		for (auto x : m.data) {
			cout << x << ", ";
		}
		return out;
	}
	int size() const { return N; }
};

template<typename L, typename R>
class AddVector {
	L left;
	R right;
public:
	AddVector(L&& left_, R&& right_) :left(std::forward<L>(left_)), right(std::forward<R>(right_)) {}
	//AddVector(const AddVector&& a) = default;
	template<int N>
	operator Vector<N>() const {// I'm assuming that all vectors in sum have same length
		/*L c(left);
		for (int i = 0; i < right.size(); i++) {
			c[i] += right[i];
		}
		return c;*/
		Vector<N> c;
		for (int i = 0; i < N; i++) {
			c[i] = (*this)[i];
		}
		return c;
	}
	int operator[](int idx) const {
		return left[idx] + right[idx];
	}
	int operator[](int idx) {
		return left[idx] + right[idx];
	}
};

template<typename L, typename R>
AddVector<L, R> operator+(L&& a, R&& b) {
	return AddVector<L, R>(std::forward<L>(a), std::forward<R>(b));
}

template<int N, int M>
AddVector<Vector<N>, Vector<M>> operator+(const Vector<N>& a, const Vector<M>& b) {
	return AddVector<Vector<N>, Vector<M>>(a, b);
}

template<typename L, typename R>
class SubVector {
	L left;
	R right;
public:
	SubVector(L&& left_, R&& right_) :left(std::forward<L>(left_)), right(std::forward<R>(right_)) {}
	template<int N>
	operator Vector<N>() const {// I'm assuming that all vectors in sum have same length
		Vector<N> c;
		for (int i = 0; i < N; i++) {
			c[i] = (*this)[i];
		}
		return c;
	}
	int operator[](int idx) const {
		return left[idx] - right[idx];
	}
	int operator[](int idx) {
		return left[idx] - right[idx];
	}
};

template<typename L, typename R>
SubVector<L, R> operator-(L&& a, R&& b) {
	return SubVector<L, R>(std::forward<L>(a), std::forward<R>(b));
}

template<int N, int M>
SubVector<Vector<N>, Vector<M>> operator+(const Vector<N>& a, const Vector<M>& b) {
	return SubVector<Vector<N>, Vector<M>>(a, b);
}

template<typename L, typename R>
class MultVector {
	L left;
	R right;
public:
	MultVector(L&& left_, R&& right_) :left(std::forward<L>(left_)), right(std::forward<R>(right_)) {}
	template<int N>
	operator Vector<N>() const {// I'm assuming that all vectors in sum have same length
		Vector<N> c;
		for (int i = 0; i < N; i++) {
			c[i] = (*this)[i];
		}
		return c;
	}
	int operator[](int idx) const {
		return left * right[idx];
	}
	int operator[](int idx) {
		return left * right[idx];
	}
};

template<typename L, typename R>
MultVector<L, R> operator*(L&& a, R&& b) {
	return MultVector<L, R>(std::forward<L>(a), std::forward<R>(b));
}

template<int N>
MultVector<int, Vector<N>> operator*(const int& a, const Vector<N>& b) {
	return MultVector<int, Vector<N>>(a, b);
}

template<int N>
MultVector<int, Vector<N>> operator*(const Vector<N>& b, const int& a) {
	return a * b;
}

int main() {
	using V = Vector<10>;
	V v{ 1,2,3,4,5,6,7,8,9,10 };
	V x(v);
	V y{ 4,4,2,5,3,2,3,4,2,1 };

	cout << "Lazy operations :\n";
	// It does not create temporary Vectors
	// It computes resulting vector coordinate by coordinate
	// (evaluating whole expression)
	//V z = v + x + y + y;
	V z = v + x + 3 * y - 2 * x;
	cout << z << endl;
	
	// Computes only one coordinate of Vector
	int e = (z + x + y)[2];
	cout << " e = " << e << endl;
	/*return 0;*/
}
/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 */