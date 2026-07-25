# C++ Resource Management Rules

A comprehensive guide to understanding the Rule of Three, Rule of Five, and Rule of Zero—essential concepts for writing safe and efficient C++ code.

## Table of Contents
- [Quick Comparison](#quick-comparison)
- [Detailed Explanations](#detailed-explanations)
- [Code Examples](#code-examples)
- [Interview Questions & Answers](#interview-questions--answers)
- [Key Takeaways](#key-takeaways)

---

## Quick Comparison

| Rule | C++ Version | Special Member Functions | When to Use |
|------|-------------|--------------------------|-------------|
| **Rule of Three** | C++98 | Destructor, Copy Constructor, Copy Assignment | Class manually manages resources |
| **Rule of Five** | C++11 | Rule of Three + Move Constructor + Move Assignment | Class manually manages resources and should support efficient moves |
| **Rule of Zero** | Modern C++ | None | Prefer RAII types (std::string, std::vector, smart pointers) |

---

## Detailed Explanations

### Rule of Three

**When:** Your class explicitly manages resources (memory, file handles, network connections, etc.)

**Why:** If you define a custom destructor, you almost certainly need to define a copy constructor and copy assignment operator. The compiler-generated versions perform shallow copies, which can lead to:
- Double deletion of resources
- Memory leaks
- Data corruption

**Example:**
```cpp
class DynamicArray {
private:
    int* data;
    size_t size;

public:
    // Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // Copy Constructor
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    }

    // Copy Assignment Operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        return *this;
    }
};
```

---

### Rule of Five

**When:** Your class manually manages resources AND you want to support move semantics (C++11 and later)

**Why:** Move semantics allow efficient transfer of resources without expensive deep copies. Implement both move constructor and move assignment operator.

**Example:**
```cpp
class DynamicArray {
private:
    int* data;
    size_t size;

public:
    // Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // Copy Constructor
    DynamicArray(const DynamicArray& other) { /* deep copy */ }

    // Copy Assignment
    DynamicArray& operator=(const DynamicArray& other) { /* deep copy */ }

    // Move Constructor (C++11)
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // Move Assignment (C++11)
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        return *this;
    }
};
```

---

### Rule of Zero

**When:** Your class doesn't need custom resource management

**Why:** This is the **preferred approach** in modern C++. By using RAII types (standard containers, smart pointers), you leverage the compiler-generated special member functions.

**Example:**
```cpp
// Rule of Zero - No special member functions needed!
class DataContainer {
private:
    std::vector<int> data;           // Automatic memory management
    std::string name;                // Automatic string management
    std::unique_ptr<Resource> res;   // Automatic resource cleanup

public:
    // Constructor only
    DataContainer(const std::string& n) : name(n) {}
    
    // Everything else (destructor, copy, move) is automatically generated!
};
```

---

## Code Examples

### When Rule of Three is NOT Enough

```cpp
// Old C++98 approach (Rule of Three only)
class Buffer {
private:
    char* ptr;
    size_t size;

public:
    ~Buffer() { delete[] ptr; }
    Buffer(const Buffer& other) { /* deep copy */ }
    Buffer& operator=(const Buffer& other) { /* deep copy */ }
    
    // Problem: Temporary buffers get copied instead of moved (inefficient!)
};

Buffer createBuffer() {
    Buffer b;  // Will be copied when returned (expensive!)
    return b;
}
```

### Modern C++11+ Approach (Rule of Five)

```cpp
class Buffer {
private:
    char* ptr;
    size_t size;

public:
    ~Buffer() { delete[] ptr; }
    Buffer(const Buffer& other) { /* deep copy */ }
    Buffer& operator=(const Buffer& other) { /* deep copy */ }
    
    // NEW: Move operations
    Buffer(Buffer&& other) noexcept 
        : ptr(other.ptr), size(other.size) {
        other.ptr = nullptr;
        other.size = 0;
    }
    
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            size = other.size;
            other.ptr = nullptr;
            other.size = 0;
        }
        return *this;
    }
};

Buffer createBuffer() {
    Buffer b;  // Return value optimization + move (very efficient!)
    return b;
}
```

### Best Practice (Rule of Zero)

```cpp
// Modern C++: Prefer this!
class Buffer {
private:
    std::vector<char> data;  // Manages itself!

public:
    // No special member functions needed - they're all auto-generated!
    // No memory leaks possible!
    // Automatically move-optimized!
};
```

---

## Interview Questions & Answers

### 1. Why do we need the Rule of Three?

A class that owns resources needs proper deep copying. The compiler-generated copy operations perform **shallow copies**, which leads to:
- **Double deletion**: Both the original and copy try to delete the same resource
- **Resource corruption**: Both objects think they own the same memory
- **Memory leaks**: Resources aren't properly freed

**Example of the problem:**
```cpp
// Without Rule of Three - DANGEROUS!
class BadArray {
    int* data;
public:
    BadArray(int size) : data(new int[size]) {}
    // Missing destructor, copy constructor, copy assignment!
};

BadArray a(10);
BadArray b = a;  // Shallow copy! Both point to same memory
// a destroyed: deletes data
// b destroyed: tries to delete already-deleted data -> CRASH!
```

---

### 2. Why was the Rule of Five introduced?

Move semantics (C++11) avoid unnecessary deep copies. The Rule of Five lets you:
- **Transfer ownership** of resources efficiently
- **Eliminate expensive allocations** during temporary object creation
- **Support modern C++ patterns** like factory functions and return value optimization

**Performance impact:**
```cpp
// Rule of Three only: Two deep copies during return
std::vector<int> createVector() {
    std::vector<int> v(1000000);  // Allocate 1M elements
    return v;  // Copy 1M elements (wasteful!)
}

// Rule of Five: Move semantics, no copy overhead
std::vector<int> v = createVector();  // Just move the pointer!
```

---

### 3. Which rule should you follow in modern C++?

**The Rule of Zero whenever possible.** 

Prefer standard library containers and smart pointers so you don't need to implement special member functions yourself. This approach:
- ✅ Eliminates bugs from manual resource management
- ✅ Automatically uses move semantics
- ✅ Is cleaner and more maintainable
- ✅ Leverages years of standard library optimization

---

### 4. When is the Rule of Five necessary?

When your class **directly owns a resource**:
- Dynamically allocated memory (`new` / `delete`)
- File handles (`FILE*`, file descriptors)
- Network sockets
- Mutexes or synchronization primitives
- Custom memory pools
- OS or third-party library resources

**If you're using `std::vector`, `std::string`, `std::unique_ptr`, etc., use Rule of Zero instead!**

---

### 5. Can you have only a destructor?

**Technically yes, but it's usually a warning sign.**

If you define a destructor, the Rule of Three says you should also define copy operations. If you're in C++11+, consider the Rule of Five.

**Exception:** Some classes genuinely don't need copying (like managers or singletons), but this is rare.

```cpp
// Unusual but sometimes valid:
class FileWriter {
    FILE* file;
public:
    ~FileWriter() { fclose(file); }
    
    // Intentionally deleted (non-copyable)
    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;
};
```

---

## Key Takeaways

| Rule | Use When | Best For |
|------|----------|----------|
| **Zero** | Always prefer this | 99% of modern C++ code |
| **Five** | Direct resource ownership | Low-level libraries, custom containers |
| **Three** | Legacy C++98 code | Older codebases, embedded systems |

### Memory for the Interview:

- **Rule of Three:** "If I manage a resource, I must define how to destroy, copy-construct, and copy-assign it."
- **Rule of Five:** "Also define how to move-construct and move-assign it efficiently."
- **Rule of Zero:** "Avoid manual resource management by using RAII types, so I define none of these functions."

---

## Resources

- [C++ Reference: Rule of Three](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [C++ Reference: Rule of Five](https://en.cppreference.com/w/cpp/language/rule_of_five)
- [C++ Core Guidelines: Class Design](https://github.com/isocpp/CppCoreGuidelines)
