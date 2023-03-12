cmake_minimum_required(VERSION 3.5)

project(xcc
	VERSION 0.1
	DESCRIPTION "C++ language feature playground"
	LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Language runtime and abstract machine
add_executable (endian src/rt/endian.cc)
add_executable (object-pointer-cmp src/rt/object-pointer-cmp.cc)

# Standard libraries
add_executable (algorithm src/stl/algorithm.cc)
add_executable (input_test src/stl/input_test.cc)
add_executable (io src/stl/io.cc)
add_executable (numeric src/stl/numeric.cc)
add_executable (rng src/stl/rng.cc)
add_executable (string-view src/stl/string-view.cc)

# Generative programming
add_executable (crtp src/meta/crtp.cc)
# TODO: https://devblogs.microsoft.com/cppblog/cpp23-deducing-this/
# you can implement CRTP by deducing the this parameter.
# Deducing this gives a new way to specify non-static member funcs
add_executable (primer src/meta/primer.cc)
add_executable (variadic src/meta/variadic.cc)

# Scopes
add_executable (storage-duration src/scope/storage-duration.cc)

# Higher order functions and functional programming patterns
add_executable (closure src/func/closure.cc)
add_executable (functors src/func/functors.cc)
add_executable (lambdas src/func/lambdas.cc)
add_executable (continuation src/func/continuation.cc)

# Dynamic dispatch and (sub)typing
add_executable (explicit src/types/explicit.cc)
add_executable (variant src/types/variant.cc)
add_executable (friend src/types/friend.cc)
add_executable (typecasting src/types/typecasting.cc)
add_executable (vtable src/types/vtable.cc)
# don't compile but use as example: src/types/rule-of-zero.cc
