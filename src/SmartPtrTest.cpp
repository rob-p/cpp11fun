#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

void fiddleWithFile() {
	string fname{"/tmp/file.txt"};
	auto closer = [](ofstream* of) { cout << "Remembering to close the file now\n"; of->close(); };
	unique_ptr<ofstream, decltype(closer)> ofile(new ofstream(fname), closer);

	(*ofile) << "La di da da\n";
}


int main(int argc, char* argv[]) {
	
	/**
	 * There are 3 types of smart pointers in C++11; unique_ptr, shared_ptr and weak_ptr.
	 *
	 * unique_ptr:
	 * unique_ptr is as it sounds; a unique (i.e. owning) pointer to some dynamically allocated resource.
	 * -- A unique pointer has a single owner, and the resource is freed (deleted) when the owning
	 *    pointer goes out of scope.
	 * -- Referring to the raw pointer underlying an out-of-scope unique_ptr is the same as referring
	 *    to memory that has already been freed --- it's *bad* undefined behavior.
	 * -- Using the default deleter, unique_ptr incurs *zero* size overhead.
	 * -- A unique pointer can't be copied, but it can be *moved* (using C++11's new move semantics).
	 *    Dereferencing a unique pointer which has been *moved* is the same as accessing a possibly 
	 *    dangling pointer -- also very bad undefined behavior -- the pointer could be null or random.
	 *
	 * shared_ptr:
	 * shared_ptr is a reference-counted pointer that has multiple "owners" (referencers).  The resources
	 * allocated by a shared pointer are freed when the last shared_ptr that refers to the resources goes
	 * out of scope.
	 * -- A shared pointer has multiple "owners", but one owner does not need to know about the others;
	 *    the resource is automatically reference counted.
	 * -- As long as you remain in smart pointer land, there shouldn't be a risk of referncing a deleted
	 *    resource via a shared_ptr.
	 * -- A shared pointer has size overhead (for the reference counting), but usually no dereferencing 
	 *    overhead.
	 *
	 * weak_ptr:
	 * weak_ptr holds a weak (i.e. non-owning) reference to a resource owned by a shared_ptr.  The weak_ptr
	 * itself cannot directly access the resource it references (it must first be converted to a shared_ptr).
	 * The weak_ptr, however, does not contribute to the reference count of the resource, so it allows for dealing
	 * with things like cyclical memory references in smart pointer land.
	 */

	// We can create a new unique pointer like-so (we could also have created it from an existing "raw" pointer)
	unique_ptr<int> ptrA(new int);
	*ptrA = 5;
	cout << "*ptrA = " << *ptrA << "\n";

	// Use the C++11 nullptr type to create a null smart pointer
	unique_ptr<int> ptrA2(nullptr);
	// Move the 
	ptrA2 = move(ptrA);
	// show that the ownership has transferred
	cout << "*ptrA2 = " << *ptrA2 << "\n";
	// We can even swap it back
	ptrA.swap(ptrA2);
	
	// Destructor gets called when the pointer goes out of scope
	{
		auto del = [](int* i) -> void { cout << "My value is " << *i << " and I'm going away now\n"; delete i;};
		unique_ptr<int, decltype(del)> ptrB(new int, del);
		*ptrB = 10;
		cout << *ptrB << "\n";
	} // ptrB is destructed here

	// call a function that uses smart pointers for resource handling
	fiddleWithFile();

	// the exclusion of make_unique from the C++11 standard was an oversight 
	// which will be rectified in the C++14 standard.
	auto sp = make_shared<int>(5);
	cout << "Now with a shared_ptr *sp = " << *sp << "\n";
	cout << "sp.use_count = " << sp.use_count() << "\n";
	{
		auto sp2 = sp;
		cout << "Here, we share the reference to the underlying resource.  *sp2 = " << *sp2 << "\n";
		cout << "sp.use_count = " << sp.use_count() << "\n";
	} // we decrement the count here, but don't free the memory
	cout << "sp.use_count = " << sp.use_count() << "\n";
}
