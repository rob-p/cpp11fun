#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

// used as conversion
constexpr long double operator "" _km( long double m )
{
	return m * 1000.0;
}

// used as conversion
constexpr long double operator "" _m( long double m )
{
	return m;
}

// used as conversion
constexpr long double operator "" _cm( long double m )
{
	return m / 100.0;
}

int main(int argc, char* argv[]) {


	long double a = 5.2_km;
	a += 300.0_m;
	a -= 150.0_cm;

	cout << "a = " << a << "\n";

}
