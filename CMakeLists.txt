cmake_minimum_required(VERSION 3.5)

project(xcc
	VERSION 0.1
	DESCRIPTION "C++ language feature playground"
	LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (algorithm src/algorithm.cpp)
add_executable (crtp src/crtp.cpp)
add_executable (endian src/endian.cpp)
add_executable (explicit src/explicit.cpp)
add_executable (fake-cmdline src/fake-cmdline.cpp)
add_executable (friend src/friend.cpp)
add_executable (functors src/functors.cpp)
add_executable (io src/io.cpp)
add_executable (lambdas src/lambdas.cpp)
add_executable (numeric src/numeric.cpp)
add_executable (object-pointer-cmp src/object-pointer-cmp.cpp)
add_executable (rng src/rng.cpp)
add_executable (storage-duration src/storage-duration.cpp)
add_executable (string-view src/string-view.cpp)
add_executable (typecasting src/typecasting.cpp)
add_executable (variant src/variant.cpp)
add_executable (vtable src/vtable.cpp)

# The actually cool section: metaprogramming!
add_executable (primer src/metaprogramming/primer.cpp)
add_executable (variadic src/metaprogramming/variadic.cpp)
