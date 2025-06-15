# 1. Generic Lambdas and Lambda Capture Initializers
## Generic Lambdas
In C++11, lambdas were limited by fixed parameter types. C++14 removes this restriction by allowing lambdas to use auto in parameter lists. This means the lambda becomes generic—capable of operating on arguments of various types without needing explicit overloads.
## Lambda Capture Initializers
C++14 also introduces initialized lambda captures (sometimes called generalized lambda captures), which allow you to define new names or move objects into the lambda’s capture list.
# 2. Relaxed constexpr Functions
C++11 introduced constexpr functions to compute values at compile time, but their capabilities were very restricted (only a single return statement, no loops or conditionals). C++14 relaxes these restrictions considerably. Now, constexpr functions can contain multiple statements, loops, and conditional logic—turning them into powerful tools for compile-time calculations.
# 3. Variable Templates
Variable templates allow you to define a family of variables or constants parameterized by a type (or other parameters). This makes it easier to write generic code for constants and small helper values.
# 4. Binary Literals and Digit Separators
C++14 introduces binary literals using a 0b or 0B prefix. It also allows you to use single quotes as digit separators, which increases readability for large numbers.
# 5. Standard Library Improvements
C++14 brought along several useful additions to the standard library:

### std::make_unique
Before C++14, you had to manually create std::unique_ptr objects using new. std::make_unique offers a safer, exception-resistant way to create them.

### std::integer_sequence and std::index_sequence
These utilities provide compile-time sequences of integers. They are especially useful in template metaprogramming to, for example, unpack parameter packs or create compile-time loops.

# 6. Return Type Deduction in Lambdas
In C++14, the compiler can automatically deduce the return type of a lambda if it isn’t explicitly specified. This makes lambda expressions even more concise.
