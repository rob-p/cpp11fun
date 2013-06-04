#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

void copyVector(vector<int> v) {
	size_t origSize = v.size();
    for (size_t i = 0; i < origSize; ++i) {
    	v.emplace_back(v[i]);
    }
}

void refVector(vector<int>& v) {
	size_t origSize = v.size();
    for (size_t i = 0; i < origSize; ++i) {
    	v.emplace_back(v[i]);
    }
}

vector<int> moveVector(vector<int>&& v) {
	size_t origSize = v.size();
    for (size_t i = 0; i < origSize; ++i) {
    	v.emplace_back(v[i]);
    }
    return v;	
}

vector<int> createVector(size_t size) {
	vector<int> v(size, 0);
	for (size_t i = 0; i < size; ++i) {
		v[i] = i;
	}
	return v;
}

class MemChunk {
public:
	explicit MemChunk() : ptr_(nullptr), amt_(0) { cerr << "default constructor\n"; }

	// copy
	MemChunk(MemChunk& other) : amt_(other.amt_) { 
		cerr << "copy constructor\n";
		cerr.flush();
		ptr_.reset(new int[amt_]);
		copy(ptr_.get(), ptr_.get() + amt_, other.ptr_.get());
	}

	MemChunk& operator=(MemChunk& other) {
		cerr << "assignment operator\n";
		amt_ = other.amt_;
		ptr_.reset(new int[amt_]);
		copy(ptr_.get(), ptr_.get() + amt_, other.ptr_.get());
		return *this;
	}

	MemChunk& operator=(MemChunk&& other) {
		cerr << "move assignment operator\n";
		amt_ = other.amt_;
		ptr_.reset(other.ptr_.release());
		other.ptr_.reset(nullptr);
		return *this;
	}

	// move
	MemChunk(MemChunk&& other) : amt_(other.amt_) { 
		cerr << "move constructor\n";
		cerr.flush();
		ptr_.reset(other.ptr_.release());
		other.ptr_.reset(nullptr);
	}

	~MemChunk() {}

	void fill(size_t size) {
		ptr_.reset(new int[size]);
		for (size_t i = 0; i < size; ++i) {
			ptr_[i] = i;
		}
		amt_ = size;
	}

	size_t size() { return amt_; }
private:
	unique_ptr<int[]> ptr_;
	size_t amt_;
};

MemChunk makeMemChunk(size_t size) {
	MemChunk m;
	m.fill(size);
	return m;
}
int main(int argc, char* argv[]) {
	// Random code from http://en.cppreference.com/w/cpp/numeric/random.

	// Seed with a real random value, if available
    random_device rd;
 
    // Choose a random mean between 1 and 6
    default_random_engine e1(rd());
    uniform_int_distribution<int> uniform_dist(1, 1000);

    vector<int> v;
    size_t origSize = 5000000;
    for (size_t i = 0; i < origSize; ++i) {
    	v.emplace_back(uniform_dist(e1));
    }

    cout << "v.size() = " << v.size() << "\n";

    cout << "calling copyVector\n";
    copyVector(v);
    cout << "v.size() = " << v.size() << "\n";

    cout << "passing v by reference\n";
    refVector(v);
    cout << "v.size() = " << v.size() << "\n";

    cout << "truncating v back to " << origSize << " elements\n";
    v.resize(origSize);
    cout << "v.size() = " << v.size() << "\n";

    // This is for illustration purposes only.  You wouldn't move
    // a vector into and out of a function (just pass by ref instead)
    cout << "moving v into and out of the function\n";
    v = moveVector(std::move(v));
    cout << "v.size() = " << v.size() << "\n";

    // However, the typical nice usage scenario that is enabled by
    // move semantics is the following.
    cout << "creating a vector with " << origSize 
         << " elements and moving it out of the function\n";
    auto v2 = createVector(origSize);
    cout << "v2.size() = " << v.size() << "\n";

    // the {} are necessary or otherwise the compiler seems to
    // do some super crazy special optimization where *no* constructor
    // is even called.
    // However, the point is that (as you can see by what's printed) since
    // the return values of makeMemChunk() is an rvalue, the compiler uses
    // the move constructor which is able to move (i.e. steal) the memory
    // chunk from the existing MemChunk instance.
    MemChunk m({makeMemChunk(origSize)});
    cout << "m.size() = " << m.size() << "\n";
}
