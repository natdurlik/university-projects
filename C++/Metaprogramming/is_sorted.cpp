#include <iostream>
#include <algorithm>
using namespace std;

template<int ...Args>
struct IntegerList {};

template <typename Arg, typename... Args>
void print(std::ostream& out, Arg&& arg, Args&&... args) {
	out << std::forward<Arg>(arg);
	((out << ',' << std::forward<Args>(args)), ...); //unfolding c++17
}

template<int ...Args>
std::ostream& operator<<(std::ostream& out, const IntegerList<Args...>& list) {
	print(out, Args...);
	return out;
}

template<class L1, class L2>
struct Join {};

template<int ...L1, int... L2>
struct Join<IntegerList<L1...>, IntegerList<L2...>> {
	using type = IntegerList<L1..., L2...>;
};

template<int ...Args>
struct SortedAux {
	static const bool value = true;
};

template<int A, int B, int...Args>
struct SortedAux<A, B, Args...> {
	static const bool value = A <= B && SortedAux<B, Args...>::value;
};

template<typename T>
struct IsSorted {};

template<int ...Args>
struct IsSorted<IntegerList<Args...>> {
	static const bool value = SortedAux<Args...>::value;
};

template<int A,int...Args>
struct MaxAux {
	static const int value = std::max(A,MaxAux<Args...>::value);
};

template<int A>
struct MaxAux<A> {
	static const int value = A;
};

template<typename T>
struct Max {};

template<int ...Args>
struct Max<IntegerList<Args...>> {
	static constexpr int value = MaxAux<Args...>::value;
};

int main() {
	using listA = IntegerList<5, -1, 5, 2, 1>;
	using listB = IntegerList<1, 4, 6, 9>;
	cout << "List A : " << listA() << endl;
	cout << "List B : " << listB() << endl;
	using listC = Join<listA, listB>::type;
	cout << "List C : " << listC() << endl;


	cout << boolalpha;
	cout << "Is A sorted? " << IsSorted<listA>::value << endl; //f
	cout << "Is B sorted? " << IsSorted<listB>::value << endl; //t
	cout << "Is C sorted? " << IsSorted<listC>::value << endl; //f


	cout << Max<listA>::value << endl; //5
	cout << Max<listB>::value << endl; //9
	cout << Max<listC>::value << endl; //9
}
