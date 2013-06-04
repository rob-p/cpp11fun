#include <iostream>

using namespace std;

constexpr size_t fac(size_t i) {
	return (i == 0) ? 1 : i * fac(i-1);
}

int main(int argc, char* argv[]) {
	
	// This is computed *completely* at compile-time.
	constexpr auto r = fac(8);

	cerr << "fac(8) = " << r << "\n";

}
