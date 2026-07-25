# Rule of Three (C++)

If a class manages a resource (raw memory, file handle, network socket, etc.), and you define any one of the following special member functions, you most likely need to define all three:

- Destructor
- Copy constructor
- Copy assignment operator

Signatures:

```cpp
~Class();
Class(const Class&);
Class& operator=(const Class&);
```

Why? A short example:

```cpp
class String {
    char* data;

public:
    String() { data = new char[100]; }
    ~String() { delete[] data; }
};
```

The compiler will implicitly generate a copy constructor and copy assignment operator that perform a shallow copy:

```cpp
String s1;
String s2 = s1; // s2.data == s1.data (shallow copy)
```

After this shallow copy both objects point to the same heap memory. When both destructors run, the same memory is deleted twice — undefined behavior (double free).

To fix this, implement deep copy semantics:

```cpp
class String {
    char* data;

public:
    String() : data(new char[100]) {}

    // Copy constructor (deep copy)
    String(const String& other) : data(new char[100]) {
        std::memcpy(data, other.data, 100);
    }

    // Copy assignment operator (deep copy)
    String& operator=(const String& other) {
        if (this == &other) return *this; // handle self-assignment
        char* new_data = new char[100];
        std::memcpy(new_data, other.data, 100);
        delete[] data;
        data = new_data;
        return *this;
    }

    ~String() { delete[] data; }
};
```

Notes and modern guidance

- Rule of Three -> Rule of Five: With C++11 moves, if you need copy/move behavior you may also implement the move constructor and move assignment operator (the "Rule of Five").
- Prefer RAII and standard types: use std::string, std::vector, or smart pointers (std::unique_ptr, std::shared_ptr) to avoid manual memory management.
- If your class should be non-copyable, delete the copy operations explicitly:

```cpp
Class(const Class&) = delete;
Class& operator=(const Class&) = delete;
```

Summary

If your class directly manages resources, think about ownership and copying semantics. Defining one special member that affects ownership usually means you must explicitly define the others to ensure safe, correct behavior.
