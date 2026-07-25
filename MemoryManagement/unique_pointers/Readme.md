# std::unique_ptr — Exclusive ownership

A concise guide to `std::unique_ptr` with clear examples, best practices and common pitfalls.

## Table of contents

- [Overview](#overview)
- [Why use std::unique_ptr?](#why-use-stduniqueptr)
- [Creating unique_ptr](#creating-unique_ptr)
- [Accessing data and members](#accessing-data-and-members)
- [Copy vs Move semantics](#copy-vs-move-semantics)
- [Passing and returning unique_ptr](#passing-and-returning-unique_ptr)
- [Important member functions](#important-member-functions)
- [Arrays and unique_ptr](#arrays-and-unique_ptr)
- [Polymorphism](#polymorphism)
- [Performance](#performance)
- [Common mistakes](#common-mistakes)
- [Quick interview questions](#quick-interview-questions)

---

## Overview

`std::unique_ptr` is a lightweight smart pointer that enforces exclusive ownership of a dynamically allocated object. When the owning `unique_ptr` is destroyed or reset, the managed object is automatically deleted.

Benefits:

- Automatic lifetime management (no manual `delete`).
- Small and efficient (typically the size of a raw pointer).
- No reference-counting overhead.

---

## Why use std::unique_ptr?

- Clear ownership semantics: exactly one owner at a time.
- Exception-safe resource management (prefer `std::make_unique`).
- Integrates well with RAII and modern C++ move semantics.

---

## Creating unique_ptr

Preferred (recommended):

```cpp
auto ptr = std::make_unique<int>(100);
```

Works but less preferred:

```cpp
std::unique_ptr<int> ptr(new int(100));
```

Why prefer `make_unique()`?

- Cleaner code
- Exception-safe (no leak if construction throws)
- Avoids repeating the type

---

## Accessing data and members

Use `*` and `->` like a raw pointer:

```cpp
#include <memory>
#include <iostream>

int main() {
    auto ptr = std::make_unique<int>(25);
    std::cout << *ptr << '\n'; // prints 25

    struct Student { void print() { std::cout << "Hello\n"; } };
    auto s = std::make_unique<Student>();
    s->print(); // prints Hello
}
```

---

## Copy vs Move semantics

- Copying is NOT allowed. `unique_ptr` represents exclusive ownership and is non-copyable:

```cpp
auto p1 = std::make_unique<int>(10);
auto p2 = p1; // compile-time error
```

- Moving is allowed. Ownership is transferred with `std::move`:

```cpp
auto p1 = std::make_unique<int>(10);
auto p2 = std::move(p1); // p1 becomes nullptr, p2 owns the object
```

Example:

```cpp
#include <memory>
#include <iostream>

int main() {
    auto p1 = std::make_unique<int>(500);
    auto p2 = std::move(p1);

    if (!p1) std::cout << "Moved\n";
    std::cout << *p2 << '\n'; // prints 500
}
```

---

## Passing and returning unique_ptr

To transfer ownership into a function, accept a `unique_ptr` by value and call the function with `std::move`:

```cpp
void takeOwnership(std::unique_ptr<int> p) { /* p now owns the resource */ }

auto ptr = std::make_unique<int>(10);
takeOwnership(std::move(ptr)); // ptr becomes nullptr
```

If you only need read-only access, pass by const reference to avoid transferring ownership:

```cpp
void readOnly(const std::unique_ptr<int>& p) { std::cout << *p << '\n'; }
```

Returning a `unique_ptr` transfers ownership to the caller (move or RVO):

```cpp
std::unique_ptr<int> create() { return std::make_unique<int>(100); }
auto p = create();
```

---

## Important member functions

- get()
  - Returns the raw pointer without changing ownership.
  - Example: `int* raw = ptr.get();`

- release()
  - Releases ownership and returns the raw pointer. The caller is responsible for deleting it.

```cpp
auto ptr = std::make_unique<int>(10);
int* raw = ptr.release(); // ptr -> nullptr
delete raw; // must delete manually
```

- reset()
  - Deletes the currently owned object (if any) and optionally takes ownership of a new pointer.

```cpp
ptr.reset(new int(20)); // deletes previous object, now owns new one
```

- swap()
  - Exchanges managed objects with another `unique_ptr`.

```cpp
p1.swap(p2);
```

---

## Arrays and unique_ptr

Use the array specialization to manage arrays so `delete[]` is used:

Wrong:

```cpp
std::unique_ptr<int> arr(new int[10]); // wrong, will call delete
```

Correct:

```cpp
std::unique_ptr<int[]> arr(new int[10]);
arr[0] = 100;
```

---

## Polymorphism

`unique_ptr` works with polymorphism when storing through a base pointer that has a virtual destructor:

```cpp
class Base { public: virtual ~Base() = default; };
class Derived : public Base { };

std::unique_ptr<Base> p = std::make_unique<Derived>();
```

---

## Performance

- `sizeof(std::unique_ptr<T>)` is typically the same as a raw pointer.
- No reference counting: very lightweight and fast.

---

## Common mistakes

- Forgetting `std::move()` when transferring ownership (results in compile errors).
- Calling `delete` on `ptr.get()` — double delete or undefined behavior, since `unique_ptr` will delete it on destruction.
- Using `release()` and then forgetting to `delete` the returned raw pointer — memory leak.

---

## Quick interview questions

Q: Why can't `unique_ptr` be copied?

A: It models exclusive ownership — copying would allow multiple owners.

Q: Why support move semantics?

A: To transfer ownership safely without copying the underlying resource.

Q: Difference between `release()` and `reset()`?

- `release()` releases ownership and returns the raw pointer; caller must delete it.
- `reset()` deletes the managed object (if any) and optionally takes ownership of a new pointer.

Q: Difference between `get()` and `release()`?

- `get()` returns the raw pointer while ownership remains with `unique_ptr`.
- `release()` returns the raw pointer and relinquishes ownership.

Q: Why prefer `make_unique()`?

- Exception safety, cleaner syntax, and no repeated type.

---

If you want, I can also rename this file to `README.md` (case-sensitive) and add links to related docs in the repository.
