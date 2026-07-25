**Function overloading** is a core feature of C++ that allows you to define multiple functions with the **same name** within the same scope, provided they have **different parameter lists** (different signatures).

It is a form of **compile-time polymorphism** (or static polymorphism), meaning the compiler decides which function to execute based on the arguments provided during the function call.

---

## 1. What Makes a Function Signature Unique?

To overload a function successfully, the functions must differ in their **parameter signatures**. The compiler distinguishes overloaded functions based on:

1. **Number of parameters:**
```cpp
void print(int a);
void print(int a, int b); // Valid overload

```


2. **Types of parameters:**
```cpp
void print(int a);
void print(double a); // Valid overload

```


3. **Sequence/Order of parameter types:**
```cpp
void print(int a, double b);
void print(double a, int b); // Valid overload

```



---

## 2. Rules & Edge Cases: What Cannot Be Overloaded?

Not all differences in a function declaration qualify for overloading.

### Return Type Alone Is Not Enough

You **cannot** overload a function by changing only its return type. The compiler cannot determine which function to call based on return value alone.

```cpp
int getValue();
double getValue(); // ERROR: Ambiguous declaration

```

### `static` vs Non-`static` Functions

Functions with the same parameter list cannot be overloaded based solely on the presence of the `static` keyword.

```cpp
class Sample {
    void display();
    static void display(); // ERROR: Re-definition
};

```

### Parameters Differing Only by Default Arguments

If default arguments create ambiguity when calling a function without parameters, the compiler throws a compile-time error.

```cpp
void greet(string name = "User");
void greet(); // ERROR: Calling greet() is ambiguous

```

### Const Member Functions (Class Scope)

In C++ classes, member functions **can** be overloaded based on whether the function itself is marked as `const`.

```cpp
class Data {
public:
    void process() { cout << "Non-const called\n"; }
    void process() const { cout << "Const called\n"; }
};

```

---

## 3. How Function Overloading Works: Name Mangling

In pure C, function overloading is not supported because the C compiler saves function symbols directly by their declared names.

In C++, the compiler uses a process called **Name Mangling** (or Name Decoration). It transforms the function name into a unique internal symbol by combining:

* Function name
* Parameter types and counts
* Scope (namespace/class)

For example, `void add(int, int)` might be mangled into `_Z3addii`, whereas `void add(double, double)` becomes `_Z3adddd`. This allows the linker to distinguish between overloaded functions.

---

## 4. How the Compiler Selects the Best Match

When an overloaded function is called, the compiler resolves the call through **Function Overload Resolution** using the following precedence hierarchy:

```text
       1. Exact Match (No conversions required)
                          |
                          v
       2. Promotion (e.g., char/short -> int, float -> double)
                          |
                          v
       3. Standard Conversion (e.g., int -> double, pointer conversions)
                          |
                          v
       4. User-Defined Conversions (e.g., implicit constructor, conversion operators)
                          |
                          v
       5. Variadic Arguments (...)

```

> **Warning — Ambiguous Calls:** If two or more functions match at the same precedence level, the compiler generates an **Ambiguity Error**.
> ```cpp
> void print(float x);
> void print(double x);
> 
> print(3.14); // OK: 3.14 is double literal -> calls print(double)
> print(0);    // Ambiguous if implicit conversions match equally
> 
> ```
> 
> 

---

## 5. Summary Table

| Concept | Supported? | Details |
| --- | --- | --- |
| **Different parameter count/types** | Yes | Core mechanism of overloading |
| **Different return type only** | No | Causes compile error |
| **Const member functions** | Yes | Valid inside classes (`void f()` vs `void f() const`) |
| **Pass-by-value vs Pass-by-reference** | ⚠️ Ambiguous | Declaring `f(int)` and `f(int&)` creates call-site ambiguity |
| **Polymorphism type** | Compile-time | Resolved during compilation via Name Mangling |
