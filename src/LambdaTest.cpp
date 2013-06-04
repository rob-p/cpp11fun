#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void higherOrder(function<int(int)>& f) {
	// invoke the passed in function; see how simple higher-order functions and
	// callbacks are in C++11!
	cout << "f(7) = " << f(7) << "\n";
}

int main(int argc, char* argv[]) {
	
	// C++11 now supports proper lambda expression.
	
	vector<int> v{1,5,6,3,4,2,9};
	std::for_each(v.begin(), v.end(), [](int i) { cout << i << " "; } );
    cout << "\n";

	// Let's sort the vector using a lambda expression for comparision
	std::sort(v.begin(), v.end(), [](int a, int b) -> bool { return a < b;} );
	std::for_each(v.begin(), v.end(), [](int i) { cout << i << " "; } );
    cout << "\n";

    // Lambda expressions can also be used to make proper closures
    int a = 5;
    // The "=" in the capture block "[]" means to capture any referenced
    // variables by value
    auto f = [=] (int b) -> int { return a + b; };
    cout << "a = " << a << ", b = 6, " << "f(b) = " << f(6) << "\n";

    auto inc = [&] (int i) -> void { a += i; };
    cout << "a = " << a << ", calling inc(5). ";
    inc(5);
    cout << "a = " << a << "\n";

    int b = 2;
    auto inc2 = [b, &a](int i) mutable -> void { a += i; b += i; };
    cout << "a = " << a << ", b = " << b << ", calling inc2(5). ";
    inc2(5);
    cout << "a = " << a << ", b = " << b << "\n";

    // Closures have unique types (created by the compiler) by default.
    // If you need to explicitly pass around a closure, you have to 
    // assign it an appropriate (named) type.
    // Here, it's a function that returns an int and takes an int.
    function<int(int)> h = [=](int b) -> int { return a + b; };

    // Pass our function to another function
    higherOrder(h);
}
