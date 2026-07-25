# Rule of Zero

## Overview

The **Rule of Zero** is a modern C++ principle that advocates for **not writing explicit destructors, copy constructors, copy assignments, move constructors, or move assignments** whenever possible. Instead, rely on standard library classes to manage resources for you.

> **The best rule is often: Don't write any of them.**

---

## The Problem with Manual Resource Management

In older C++ codebases, developers had to manually define multiple special member functions:

```cpp
class Employee {
private:
    char* name;           // Manual memory management
    int* salaryHistory;   // Manual memory management
    int size;
    
public:
    Employee(const std::string& n);
    ~Employee();                           // Destructor
    Employee(const Employee& other);       // Copy constructor
    Employee& operator=(const Employee& other); // Copy assignment
    Employee(Employee&& other) noexcept;   // Move constructor
    Employee& operator=(Employee&& other) noexcept; // Move assignment
};
```

This approach is error-prone and requires careful handling of resource acquisition and release.

---

## The Solution: Use Standard Library Classes

Replace raw pointers and manual memory management with standard library containers:

### Bad Practice (Manual Management)
```cpp
class Employee {
private:
    char* data;           // Raw pointer
    int* arr;             // Raw pointer
    
public:
    // Need to implement all special member functions...
};
```

### Good Practice (Rule of Zero)
```cpp
class Employee {
private:
    std::string name;              // Manages its own memory
    std::vector<int> salaryHistory; // Manages its own memory
    
public:
    // No special member functions needed!
};
```

---

## Key Standard Library Classes for Resource Management

| Use Case | Replace | With |
|----------|---------|------|
| Dynamic strings | `char*` | `std::string` |
| Dynamic arrays | `int*` / `T*` | `std::vector<T>` |
| Unique ownership | Manual `new`/`delete` | `std::unique_ptr<T>` |
| Shared ownership | Manual `new`/`delete` | `std::shared_ptr<T>` |
| Fixed-size arrays | `T[]` | `std::array<T, N>` |
| Key-value pairs | Custom implementations | `std::map<K, V>` |
| Unordered lookup | Custom hash tables | `std::unordered_map<K, V>` |

---

## Example: Rule of Zero in Action

### Before (Rule of Five)
```cpp
class Employee {
private:
    std::string name;
    int salary;
    
public:
    Employee(const std::string& n, int s) : name(n), salary(s) {}
    
    ~Employee() {} // Explicitly defined (not needed)
    Employee(const Employee&) = default; // Must define
    Employee& operator=(const Employee&) = default; // Must define
    Employee(Employee&&) noexcept = default; // Must define
    Employee& operator=(Employee&&) noexcept = default; // Must define
};
```

### After (Rule of Zero)
```cpp
class Employee {
private:
    std::string name;
    std::vector<int> salaryHistory;
    
public:
    Employee(const std::string& n) : name(n) {}
    
    // No special member functions needed!
    // Compiler-generated versions work perfectly
};
```

---

## Benefits

✅ **Simpler code** - Fewer special member functions to write and maintain  
✅ **Fewer bugs** - Less opportunity for resource leaks or double-deletes  
✅ **Better performance** - Standard library classes are highly optimized  
✅ **Exception safety** - RAII is handled correctly by standard classes  
✅ **Move semantics** - Automatically efficient with standard containers  
✅ **Less boilerplate** - Let the compiler generate what you need  

---

## When You Can't Use the Rule of Zero

There are rare cases where you need to define special member functions:

- Managing **non-RAII resources** (file handles, network sockets, database connections)
- Custom **synchronization or locking logic**
- **Performance-critical** operations requiring manual optimization
- **Legacy code** integration requirements

In these cases, follow the **Rule of Three** (pre-C++11) or **Rule of Five** (C++11 and later).

---

## Related Concepts

- **Rule of Three**: If you define destructor, copy constructor, or copy assignment, define all three
- **Rule of Five**: Add move constructor and move assignment to Rule of Three
- **RAII (Resource Acquisition Is Initialization)**: Resources are tied to object lifetime
- **Move semantics**: Efficient transfer of resources between objects

---

## Best Practices

1. **Prefer standard library classes** over raw pointers
2. **Use `std::string`** instead of `char*`
3. **Use `std::vector`** instead of dynamic arrays
4. **Use `std::unique_ptr`** for single ownership
5. **Use `std::shared_ptr`** for shared ownership
6. **Avoid raw `new` and `delete`** in modern C++
7. **Let the compiler generate** special member functions when possible

---

## References

- [C++ Standard Library Documentation](https://en.cppreference.com/)
- [Rule of Three, Rule of Five](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [Move semantics](https://en.cppreference.com/w/cpp/language/move)
