#ifndef UTILS_HPP
#define UTILS_HPP

#include <type_traits>
#include <sstream>

using namespace std;

// We need a wraper that will provide a "type" field
template<typename> struct Void { typedef void type; };

// The "default" type T does not have a key
template<typename T, typename Sfinae = void>
struct has_key: std::false_type {};

// Use decltype to access the key_type field of the 
// provided type T if it exists.  If T has a key_type trait
// then this will succeed, and we can instantiate this struct.
// If T doesn't have a key_type trait, then SFINAE means that that
// struct won't be instantiated and we'll fall back to the default
// above.
template<typename T>
struct has_key<
    T
    , typename Void<
        decltype( typename T::key_type{} )
    >::type
>: std::true_type {};


/*
Print a map-like container
 */
template <typename T, bool b>
struct ContainerPrinter{
	static string str(T& container) {
		ostringstream s;
 	    /* 
  	     Loop over and print out the map using the new c++11
   	     style for loop.  The new-style loop will work for any 
	     type that has begin() and end() methods that return an iterator,
	     OR if there are _free_ functions begin() and end() which
	     consume the type and return an iterator.
   	    */
		s << "[";
		for (auto& e : container) {
			s << e.first << " : " << e.second << ", ";
		}
		s.seekp(-2, ios_base::end);
		s << "]";
    	return s.str();
    }
};

/*
Print a list-like container
 */
template <typename T>
struct ContainerPrinter <T, false> {
	static string str(T& container) {
		ostringstream s;
		s << "[";
		for (auto& e : container) {
			s << e << ", ";
		}
		s.seekp(-2, ios_base::end);
		s << "]";
	    return s.str();
    }
};

/*
Compile-time selection between list-like and map-like printing.
 */
template <typename T>
string str(T& container) {
	return ContainerPrinter<T, has_key<T>::value>::str(container);
}

#endif // UTILS
