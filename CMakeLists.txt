# We require at least cmake 2.8
cmake_minimum_required (VERSION 2.8) 
# Name our project
project (cpp11fun) 

# We set a variable like so (this "creates" the variable if it doesn't exist)
# sort of like those creepy "dynamic" languages . . . sigh.
set(UNIVERSAL_FLAGS "-Werror -Wall -Wpedantic -O2")

# Check for the compiler being used and set some variables accordingly
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	message("It seems that you're using clang")
	set(CMAKE_CXX_FLAGS "${UNIVERSAL_FLAGS} -std=c++11 -stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${UNIVERSAL_FLAGS} -std=c++11")
endif()

# Recurse into the source directory
add_subdirectory(src)