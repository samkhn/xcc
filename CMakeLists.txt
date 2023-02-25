cmake_minimum_required(VERSION 3.5)

project(xcc
	VERSION 0.1
	DESCRIPTION "Experiments with the C++ language/compiler"
	LANGUAGES CXX)

add_executable(endian endian.cpp)
add_executable(explicit explicit.cpp)
add_executable(fake-cmdline fake-cmdline.cpp)
add_executable(friend friend.cpp)
add_executable(functors functors.cpp)
add_executable(lambdas lambdas.cpp)
add_executable(object-pointer-cmp object-pointer-cmp.cpp)
add_executable(storage-duration storage-duration.cpp)
add_executable(string-view string-view.cpp)
add_executable(typecasting typecasting.cpp)
add_executable(variant variant.cpp)
add_executable(vtable vtable.cpp)

# The actually cool section: metaprogramming!
add_executable(primer metaprogramming/primer.cpp)
add_executable(variadic metaprogramming/variadic.cpp)
