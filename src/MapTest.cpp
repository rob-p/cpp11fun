#include <unordered_map> // the new standard hash-map
#include <vector>
#include <iostream>
#include "Utils.hpp"

using namespace std;

// Template aliases allow us to create new names
// for templatized types (without fixing the types)
template <typename Key, typename Value>
using HashMap = unordered_map<Key, Value>;

int main(int argc, char* argv[]) {

	// Create a new map using the new initializer lists
	HashMap<int, string> m{{1, "hello"}, {2, "world"}};
	// We can do the same thing with vectors
	vector<int> nums{1,2,3,4,5};

	// Use our fancy (resolved at compile-time) string functions
	std::cout << str(m) << "\n";
	std::cout << str(nums) << "\n";

}
