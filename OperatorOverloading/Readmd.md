Operator Overloading allows you to redefine how C++ operators (like +, -, <<, [], (), etc.) behave when applied to user-defined types (classes/structs). It makes your custom objects behave intuitively like built-in types.

Core Syntax Rules
Member Function: ReturnType operator<op>(const ClassName& rhs);

Friend / Global Function: friend ReturnType operator<op>(const ClassName& lhs, const ClassName& rhs);

Cannot Overload: ., ::, ?:, sizeof, typeid.

Cannot Change: Arity (number of operands), precedence, or associativity.
