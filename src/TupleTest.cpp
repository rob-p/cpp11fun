#include <iostream>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

/**
 * Notice the new return type syntax (where the return type comes after)
 * the function arguments via ->.  In this case, auto precedes the function
 * name and the return type comes after the "->", which compes after
 * the argument list.  Here we use decltype to have the compiler infer
 * the appropriate types for the expressions u + v and u * v
 */
template <typename U, typename V>
auto sumProd(U u, V v) -> tuple<decltype(u+v), decltype(u*v)> {
	return make_tuple(u+v, u*v);
}

int main(int argc, char* argv[]) {
	int a = 5;
	float b = 6.2;

	// We use a tuple to return multiple values from a function easily
	auto sp = sumProd(a, b);

	// The syntax to get the elements of a tuple is still a bit strange
	cout << "sum = " << get<0>(sp) << ", prod = " << get<1>(sp) << "\n";
}
