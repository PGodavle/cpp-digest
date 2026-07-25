# Rule of Five (C++11)

## Overview

The **Rule of Five** is a C++ best practice guideline that extends the Rule of Three by incorporating move semantics introduced in C++11. If you define any of the five special member functions, you should explicitly define all five to maintain proper resource management and prevent subtle bugs.

## The Five Special Member Functions

| Function | Purpose |
|----------|---------|
| **Destructor** `~Class()` | Clean up resources |
| **Copy Constructor** `Class(const Class&)` | Create a deep copy of an object |
| **Copy Assignment** `Class& operator=(const Class&)` | Assign one object's data to another |
| **Move Constructor** `Class(Class&&)` | Transfer ownership of resources |
| **Move Assignment** `Class& operator=(Class&&)` | Transfer ownership during assignment |

## Copy vs Move Semantics

### Copy Operations (Before C++11)

**Copy Constructor:**
```cpp
MyString(const MyString& other)
{
    data = new char[strlen(other.data) + 1];
    strcpy(data, other.data);  // Deep copy
}
```

**Drawback:** Expensive allocation and memory duplication.

### Move Operations (C++11 and Later)

**Move Constructor:**
```cpp
MyString(MyString&& other)
{
    data = other.data;      // Transfer ownership
    other.data = nullptr;   // Leave source empty
}
```

**Advantages:**
- ✅ No allocation
- ✅ No copying
- ✅ Very fast
- ✅ Efficient resource transfer

**Visual Representation:**
```
Before Move:
s1 ----> [Heap Memory]

After Move:
s2 ----> [Heap Memory]
s1 ----> nullptr
```

### Move Assignment Operator

**Move Assignment:**
```cpp
MyString& operator=(MyString&& other)
{
    if(this != &other)
    {
        delete[] data;          // Clean up old resources
        data = other.data;      // Transfer ownership
        other.data = nullptr;   // Leave source empty
    }
    return *this;
}
```

**Key Points:**
- Clean up existing resources first
- Transfer ownership from source to destination
- Leave the source in a valid but unspecified state

## Complete Example

```cpp
class MyString
{
private:
    char* data;

public:
    // Destructor
    ~MyString()
    {
        delete[] data;
    }

    // Copy Constructor
    MyString(const MyString& other)
    {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // Copy Assignment
    MyString& operator=(const MyString& other)
    {
        if(this != &other)
        {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // Move Constructor
    MyString(MyString&& other) noexcept
    {
        data = other.data;
        other.data = nullptr;
    }

    // Move Assignment
    MyString& operator=(MyString&& other) noexcept
    {
        if(this != &other)
        {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};
```

## When to Apply the Rule of Five

Apply the Rule of Five when your class:
- **Manages dynamic memory** (pointers, arrays)
- **Manages file handles** or other system resources
- **Manages database connections**
- **Contains non-copyable/non-movable members**

## When the Compiler Generates Defaults

The compiler automatically generates special member functions. However:
- If you define **any** of the five, the compiler won't auto-generate the others
- Always explicitly define all five to avoid surprises
- Use `= default` for functions you want the compiler to generate
- Use `= delete` for functions you want to prevent

```cpp
class NonCopyable
{
public:
    NonCopyable() = default;
    ~NonCopyable() = default;
    
    // Prevent copying
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    
    // Allow moving
    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
};
```

## Summary Checklist

If you define one of these five special member functions, define all five:

- [ ] `~Class()` — Destructor
- [ ] `Class(const Class&)` — Copy Constructor
- [ ] `Class& operator=(const Class&)` — Copy Assignment
- [ ] `Class(Class&&)` — Move Constructor
- [ ] `Class& operator=(Class&&)` — Move Assignment

## Key Takeaways

✨ **Remember:** The Rule of Five helps ensure your classes behave predictably and efficiently with both copying and moving semantics. Explicit definitions prevent resource leaks, dangling pointers, and double-delete bugs.

## Further Reading

- [C++11 Move Semantics](https://en.cppreference.com/w/cpp/utility/move)
- [Special Member Functions](https://en.cppreference.com/w/cpp/language/member_functions)
- [Rule of Three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B))
