#ifndef _X_CC_INLINE_H_
#define _X_CC_INLINE_H_

// Inlining for a function (and version >= C++17, vars) says that
// - within the same translation unit: the definition must be reachable not necessarily before point of access
// - with external linkage: each inline declaration must be inline, must have the same address in each translation unit and
//   (most important part) there may be more than one definition.
//   This is fine as long as each definition appears in a different translation unit.
//   If there are multiple definitions across TUs, undefined behavior.
//   For non-static inline functions and variables, all the definitions must be identical.
//
// Note: a function declared inside a class is implicitly inlined.
// Note: A static constexpr data member of a class is implicitly inline from C++17
// Note: a function or variable declared constexpr is implicitly inlined.
// Note: a function that has been deleted is implicitly inlined (since its impl can appear in other translation units)
// Note: Function-local static objects in all function definitions are shared across all translation units
//   (they all refer to the same object defined in one translation unit) 
//
// Preprocessor guards prevent double #includes within the same translation unit.
// One Definition Rule still applies within the same translation unit.

#include <atomic>
#include <string_view>

// Within inline and constexpr, you can safely define constants inside header files
// The string will be at the same address everytime because of inline.
// If they are not marked as inline then there will be a separate instance of the variable for each .cc file that includes this header.
// constexpr ensures that the value is safely initialized and destroyed.
inline constexpr std::string_view kHelloWorld = "Hello World.";

// inline vs static: inline enforces same address across each translation unit. static enforces linkage within the same TU.
// Therefore, static undoes/negates inline. Static makes a variable private to its TU (file).

// use: function included in multiple source files must be inline
inline int sum( int a, int b )
{
    return a + b;
}

// use: variable with external linkage included in multiple source files must be inline
inline std::atomic<int> counter( 0 );

// Check storage-duration.cpp for how this gets used.

#endif
