# 1. Structured Bindings
Structured bindings allow you to “decompose” an aggregate (like a std::tuple, std::pair, array, or even a struct) into individual named variables. This makes dealing with grouped data much more natural.
# 2. if constexpr
The if constexpr statement enables compile-time decision making. It allows the compiler to discard code paths that are not valid for a given type or condition, which is very useful in template metaprogramming.
# 3. Inline Variables
Inline variables let you define variables in header files without violating the One Definition Rule (ODR). They behave like inline functions and can be defined in multiple translation units.
# 4. Fold Expressions
Fold expressions simplify writing variadic templates by automatically “folding” a parameter pack over an operator. This reduces the boilerplate code for operations such as summing values or performing logical operations.
# 5. Class Template Argument Deduction (CTAD)
CTAD allows the compiler to deduce template arguments from constructor arguments, very similar to how function argument deduction works. This reduces redundancy and makes template class usage less cumbersome.
# 6. New Standard Library Types
C++17 introduced several new types that greatly enrich the standard library:
### a. std::optional
std::optional<T> represents an object that might or might not contain a value. It is a safer and more expressive alternative to using pointers or special values to represent “no value.”
### b. std::variant
std::variant is a type-safe union that can hold one of several types. It is useful when you need a variable that could be one of several different, but fixed, types.
### c. std::any
std::any is a type-safe container for single values of any type. It allows you to store and later retrieve a value without knowing its type at compile time.
### d. std::string_view
std::string_view provides a lightweight, non-owning view into a character sequence. It can be used to pass strings to functions without copying and without being tied to a specific string type.

# 7. Parallel Algorithms
C++17 extends many of the standard library algorithms in <algorithm> to support parallel execution. With execution policies like std::execution::seq, std::execution::par, and std::execution::par_unseq, you can request that algorithms run in parallel where appropriate.
# 8. Filesystem Library
What It Is: The Filesystem library (available in <filesystem>) provides facilities for performing file system operations such as traversing directories, querying file attributes, and manipulating paths—all in a platform-independent manner.
# 9. New Attributes
What It Is: C++17 introduced the attribute [[nodiscard]], which can be applied to functions or types to indicate that the return value should not be ignored. This helps catch bugs where a function’s result is critical.
