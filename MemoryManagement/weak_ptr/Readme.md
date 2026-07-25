# `std::weak_ptr`

## 📚 Learning Objectives

After completing this topic, you should be able to:

- ✅ Understand why `weak_ptr` exists
- ✅ Explain the difference between ownership and observation
- ✅ Understand circular references
- ✅ Use `lock()`, `expired()`, and `use_count()`
- ✅ Explain `weak_ptr` in interviews
- ✅ Know when to use `weak_ptr` instead of `shared_ptr`

---

## 1️⃣ Why do we need `weak_ptr`?

Suppose we already have:

```cpp
std::shared_ptr<int> ptr = std::make_shared<int>(100);
```

Now another object wants to observe this object.

**Should it own it?**

Not necessarily. Sometimes it only wants to access it if it still exists.

That's exactly why `weak_ptr` exists.

---

## 2️⃣ What is `weak_ptr`?

A `weak_ptr` is a **non-owning smart pointer**.

- ✗ Does NOT increase the reference count
- ✗ Cannot own an object
- ✓ Can observe an object

Think of it as: *"I know this object exists, but I don't own it."*

### Ownership Diagram

```
shared_ptr                      weak_ptr
   ↓                           shared_ptr
   ├─→ Object                      ↓
                                   ├─→ Object
                                   ↑
                                weak_ptr

Owns the object.              Observes the object.
                              Does NOT own it.
```

---

## 3️⃣ Creating `weak_ptr`

```cpp
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(100);
    std::weak_ptr<int> wp = sp;
}
```

**Note:**
- No `std::move()`
- No copy of object
- Just observing

---

## 4️⃣ Does `weak_ptr` increase reference count?

### Example

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(50);
    std::cout << sp.use_count() << std::endl;        // Output: 1

    std::weak_ptr<int> wp = sp;
    std::cout << sp.use_count() << std::endl;        // Output: 1
}
```

**Answer: NO** — Reference count never changes.

### Memory Diagram

```
shared_ptr
   ↓
Object (Count = 1)
   ↑
weak_ptr

Weak pointer is NOT counted.
```

---

## 5️⃣ Can we dereference `weak_ptr`?

### ❌ Wrong

```cpp
std::weak_ptr<int> wp;
*wp;  // Compile Error!
```

**Reason:** A weak pointer may point to nothing (object already destroyed).

---

## 6️⃣ `lock()`

To use a weak pointer, convert it into a `shared_ptr` using `lock()`.

### Example

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(500);
    std::weak_ptr<int> wp = sp;

    if(auto temp = wp.lock())  // Safe access
    {
        std::cout << *temp;    // Output: 500
    }
}
```

### Memory Diagram

```
shared_ptr
   ↓
Object
   ↑
weak_ptr
   ↓ (lock())
   ↓
temporary shared_ptr
```

---

## 7️⃣ What happens internally?

When we call `auto temp = wp.lock();`:

**Reference Count Changes:**

| Stage | Count |
|-------|-------|
| Before lock() | 1 |
| After lock() | 2 |
| After temp is destroyed | 1 |

A temporary `shared_ptr` is created, incrementing the reference count. When the temporary goes out of scope, the count decreases.

---

## 8️⃣ `expired()`

Checks if the object has already been deleted.

### Example

```cpp
#include <iostream>
#include <memory>

int main()
{
    std::weak_ptr<int> wp;

    {
        auto sp = std::make_shared<int>(100);
        wp = sp;
        std::cout << wp.expired() << std::endl;  // Output: 0 (false)
    }

    std::cout << wp.expired() << std::endl;      // Output: 1 (true)
}
```

| Value | Meaning |
|-------|---------|
| 0 | false - Object still exists |
| 1 | true - Object already destroyed |

---

## 9️⃣ `use_count()`

Returns the number of `shared_ptr` owners.

### Example

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(100);
    std::weak_ptr<int> wp = sp;
    std::cout << wp.use_count();  // Output: 1
}
```

### When copying `shared_ptr`

```cpp
auto sp2 = sp;
std::cout << wp.use_count();  // Output: 2
```

**Note:** `weak_ptr` never increases the count.

---

## 🔟 `reset()`

Breaks observation.

```cpp
auto sp = std::make_shared<int>(100);
std::weak_ptr<int> wp = sp;

wp.reset();  // Now wp → Empty
```

---

## 1️⃣1️⃣ `swap()`

Swaps observed objects.

```cpp
std::weak_ptr<int> w1;
std::weak_ptr<int> w2;

w1.swap(w2);  // Exchange observed objects
```

---

## 1️⃣2️⃣ Circular Reference Problem

### ⚠️ THE Most Important Interview Question

**Problem Scenario:**

```
Employee owns Company
    ↓
Company owns Employee
```

### Using `shared_ptr` (❌ WRONG)

Both reference counts stay at 1, even after `main()` ends. Memory is never deleted — **Memory Leak!**

### Example

```cpp
#include <iostream>
#include <memory>

class Company;

class Employee
{
public:
    std::shared_ptr<Company> company;
    
    ~Employee() { std::cout << "Employee Destroyed\n"; }
};

class Company
{
public:
    std::shared_ptr<Employee> employee;
    
    ~Company() { std::cout << "Company Destroyed\n"; }
};

int main()
{
    auto e = std::make_shared<Employee>();
    auto c = std::make_shared<Company>();

    e->company = c;
    c->employee = e;
}
// Output: (nothing printed - memory leak!)
```

### Memory Diagram

```
Employee
   ↓
Company
   ↑
shared_ptr
   ↓
shared_ptr

Both keep each other alive forever. ☠️
```

### ✅ Solution: Use `weak_ptr`

```cpp
class Company
{
public:
    std::weak_ptr<Employee> employee;  // Change this!
};
```

Now the reference count can become 0 and everything is destroyed correctly.

### Output (Fixed)

```
Company Destroyed
Employee Destroyed
No leak! ✅
```

---

## 1️⃣3️⃣ Internal Working

### `shared_ptr` Stores

```
Pointer → Control Block
```

### `Control Block` Contains

- Reference Count
- Weak Count
- Custom Deleter
- Allocator

### `weak_ptr` Points to

Same Control Block (does NOT own the object).

### Memory Diagram

```
shared_ptr
   ↓
┌────────────────────┐
│  Control Block     │
├────────────────────┤
│ Strong Count = 1   │
│ Weak Count = 1     │
└────────────────────┘
   ↓
Actual Object
```

---

## 1️⃣4️⃣ Performance

`weak_ptr` stores:
- Pointer
- Control Block Pointer

**Characteristics:**
- ✅ Very lightweight
- ✅ No ownership overhead
- ✅ No object copy

---

## 1️⃣5️⃣ Common Mistakes

### ❌ Mistake 1: Dereferencing directly

```cpp
*wp;  // Wrong!
```

**✅ Correct:**
```cpp
if(auto sp = wp.lock()) {
    *sp;  // Safe access
}
```

---

### ❌ Mistake 2: Assuming `weak_ptr` keeps object alive

```cpp
std::weak_ptr<int> wp;

{
    auto sp = std::make_shared<int>(10);
    wp = sp;
}

// Object is already destroyed here!
```

---

### ❌ Mistake 3: Forgetting to check `lock()`

```cpp
auto sp = wp.lock();
std::cout << *sp;  // Dangerous! sp might be null
```

**✅ Correct:**
```cpp
if(auto sp = wp.lock()) {
    std::cout << *sp;
}
```

Always verify that `lock()` succeeded before using the returned `shared_ptr`.

---

## 1️⃣6️⃣ `shared_ptr` vs `weak_ptr`

| Feature | `shared_ptr` | `weak_ptr` |
|---------|------------|-----------|
| Owns Object | ✅ Yes | ❌ No |
| Increases Reference Count | ✅ Yes | ❌ No |
| Can Dereference | ✅ Yes | ❌ (Use `lock()`) |
| Deletes Object | ✅ Yes | ❌ Never |
| Use Case | Ownership | Observation |

---

## 1️⃣7️⃣ Interview Questions

### Q1: Why was `weak_ptr` introduced?

To observe objects managed by `shared_ptr` without increasing the reference count, and to **break circular ownership**.

---

### Q2: Does `weak_ptr` increase reference count?

**No.** Only `shared_ptr` changes the reference count.

---

### Q3: Why can't `weak_ptr` be dereferenced?

Because the object **may already be destroyed**.

---

### Q4: Why use `lock()`?

`lock()` safely creates a temporary `shared_ptr` **only if the object still exists**.

---

### Q5: What does `expired()` do?

Checks whether the managed object has already been destroyed.

---

### Q6: What causes memory leak in `shared_ptr`?

**Circular reference.**

**Example:**
```
A ↔ B (circular dependency)
```

**Solution:** Use `weak_ptr` on one side.

---

### Q7: Can `weak_ptr` become `shared_ptr`?

**Yes**, using `lock()`:

```cpp
auto sp = wp.lock();
```

---

## 📝 Practice Programs

1. Create a `weak_ptr` from a `shared_ptr`
2. Verify that `use_count()` does not change after creating a `weak_ptr`
3. Use `lock()` to access the object safely
4. Use `expired()` before and after the owning `shared_ptr` goes out of scope
5. Use `reset()` on a `weak_ptr`
6. Swap two `weak_ptr` objects
7. Build an Employee ↔ Company example with a circular reference using `shared_ptr`
8. Fix the circular reference by replacing one `shared_ptr` with a `weak_ptr`
9. Print constructor and destructor messages to observe object lifetimes
10. Create multiple `weak_ptr`s observing the same object and verify that they don't affect the `shared_ptr` count

---

## 🎯 Key Takeaways

- ✅ `weak_ptr` is a **non-owning observer** of an object managed by `shared_ptr`
- ✅ It does **not increase** the shared ownership count
- ✅ You **cannot dereference** a `weak_ptr` directly
- ✅ Use `lock()` to **safely** obtain a temporary `shared_ptr`
- ✅ Use `expired()` to check whether the object has already been destroyed
- ✅ The **most common use** of `weak_ptr` is to **break circular references**
- ✅ `weak_ptr` works by referring to the same control block as the corresponding `shared_ptr`, but without contributing to the strong reference count

---

## 📊 Smart Pointer Summary

| Feature | `unique_ptr` | `shared_ptr` | `weak_ptr` |
|---------|------------|-------------|-----------|
| Ownership | Exclusive | Shared | None (Observer) |
| Copy Allowed | ❌ No | ✅ Yes | ✅ Yes |
| Move Allowed | ✅ Yes | ✅ Yes | ✅ Yes |
| Reference Count | ❌ | ✅ Strong Count | ❌ Doesn't Increase Strong Count |
| Can Dereference | ✅ | ✅ | ❌ (Use `lock()`) |
| Best Use Case | Single owner | Multiple owners | Observing / Breaking cycles |
