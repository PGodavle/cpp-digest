Here are the additional corner cases, details on **`static`**, **`virtual`**, and **`const`**, along with subtle pitfalls that often catch developers off guard:

---

## 1. `const` & `volatile` Qualifiers (Member Functions vs. Parameters)

### Member Function Level (`const` overloading)

You **can** overload a class member function based on its `const` qualifier. The compiler selects the overload depending on whether the invoking object is `const` or non-`const`.

```cpp
class Container {
public:
    // Called when the object is non-const
    int& get() { return data; }

    // Called when the object is const
    const int& get() const { return data; }

private:
    int data = 10;
};

```

### Parameter Level (`const` vs non-`const`)

* **By Value:** You **cannot** overload based on `const` when passing by value because the parameter is just a local copy.
```cpp
void process(int x);
void process(const int x); // ERROR: Redefinition (re-declares the same function)

```


* **By Reference or Pointer:** You **can** overload based on `const` references or pointers.
```cpp
void process(int& x);       // For non-const lvalues
void process(const int& x); // For const lvalues or rvalues (Valid Overload)

```



---

## 2. `static` Member Functions

* **`static` vs Non-`static` Member Functions:** You **cannot** overload two member functions with the same name and parameter list where one is `static` and the other is non-`static`.
```cpp
class Manager {
public:
    void run(int x);
    static void run(int x); // ERROR: Redefinition
};

```


* **No `const` for `static`:** `static` member functions do not have a `this` pointer, so they cannot be qualified with `const`, `volatile`, or ref-qualifiers (`&`/`&&`).

---

## 3. `virtual` Functions & Overloading vs. Overriding

Mixing **overloading** and **overriding** across base and derived classes is a major source of bugs.

### Hiding Base Class Overloads (Name Hiding)

If a derived class declares a function with the same name as a function in the base class, it **hides all overloads** of that function from the base class, even if the parameter signatures are different.

```cpp
class Base {
public:
    virtual void display(int x);
    virtual void display(double x);
};

class Derived : public Base {
public:
    // Overrides display(int), but HIDES display(double)!
    void display(int x) override; 
};

Derived d;
d.display(5);    // Works: Calls Derived::display(int)
d.display(3.14); // Converts 3.14 to int and calls Derived::display(int)!
                 // Base::display(double) is hidden!

```

> **Fix:** Unhide base class overloads using the `using` keyword in the derived class:
> ```cpp
> class Derived : public Base {
> public:
>     using Base::display; // Brings all Base::display overloads into scope
>     void display(int x) override;
> };
> 
> ```
> 
> 

---

## 4. Modern C++ Ref-Qualifiers (`&` and `&&`)

Since C++11, you can overload member functions based on whether the calling object is an **lvalue** (temporary/value) or an **rvalue** (expiring object).

```cpp
class Buffer {
public:
    // Called when invoked on an lvalue (e.g., buf.data())
    std::vector<int> data() & { return vec; }

    // Called when invoked on an rvalue (e.g., std::move(buf).data())
    std::vector<int> data() && { return std::move(vec); }

private:
    std::vector<int> vec;
};

```

---

## 5. Additional Corner Cases & Edge Cases

### A. Arrays vs. Pointers in Parameters

Array declarations in parameter lists decay to pointers. Therefore, these two declarations are considered identical:

```cpp
void calculate(int arr[]);
void calculate(int* arr); // ERROR: Redefinition

```

### B. Function Types as Parameters

Passing a function by value decays into a function pointer:

```cpp
void execute(void func());
void execute(void (*func)()); // ERROR: Redefinition

```

### C. `typedef` / `using` Aliases

Type aliases do not create new types, so overloading using a `typedef` and its underlying type causes a compilation error:

```cpp
using Velocity = double;

void setSpeed(double v);
void setSpeed(Velocity v); // ERROR: Redefinition

```

### D. Default Arguments Creating Ambiguity

Default arguments do not change a function's signature, but they can cause ambiguity at the call site.

```cpp
void compute(int x, int y = 0);
void compute(int x);

compute(10); // ERROR: Ambiguous call! Compiler doesn't know which one to choose.

```

---

## Quick Reference Checklist

| Feature / Scenario | Can Be Overloaded? | Reason |
| --- | --- | --- |
| `int f(int)` vs `double f(int)` | ❌ No | Return type alone is ignored |
| `void f(int x)` vs `void f(const int x)` | ❌ No | Top-level `const` by-value decays |
| `void f(int& x)` vs `void f(const int& x)` | Yes | Low-level `const` reference differs |
| `void f()` vs `void f() const` | Yes | Invoking object `this` qualifier differs |
| `void f()` vs `static void f()` | ❌ No | `static` vs non-`static` same scope conflict |
| `void f(int*)` vs `void f(int[])` | ❌ No | Array decays to pointer |
| `void f(int)` vs `void f(int, int = 0)` | ⚠️ Compiles | Fails at call-site (`f(5)`) due to ambiguity |
