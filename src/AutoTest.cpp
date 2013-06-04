#include <iostream>
#include <vector>
using namespace std;


int main(int argc, char* argv[]) {

	// C++11 has the ability to automatically deduce types 
	// in certain situations.
	// Here's an int
	auto num = 5;

	// Here's a float (the result of adding an int and float)
	auto sum = 5 + 6.3f;

	cout << "num = " << num << " sum = " << sum << "\n";

	vector<float> v{1.0f, 2.1f, 3.0f, 4.4f, 5.8f};
	// Notice the lack of ugly, manually-defined, iterator types here
	for (auto& e : v) {
		cout << e << " ";
	}
	cout << "\n";
}
