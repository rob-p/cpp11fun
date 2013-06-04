#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	
	// The counter is atomic (on supported hardware, it'll use)
	// compare and swap to avoid software-level locking
	std::atomic<size_t> counter{0};
	size_t itPerThread = 500000;

	vector<std::thread> threads;
	// spawn off 4 threads;
	for (size_t i = 0; i < 4; ++i) {
	  threads.emplace_back( std::thread([&counter, itPerThread]() -> void {
	  	for (size_t j = 0; j < itPerThread; ++j) { ++counter; }
	  }
	  ));
	}

	for (auto& t : threads) { t.join(); }

	cout << "Counter = " << counter << "\n";
}
