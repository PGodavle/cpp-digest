# std::shared_ptr

## Learning Objectives

After completing this topic, you should be able to:

- Understand shared ownership.
- Explain reference counting.
- Use `make_shared()`.
- Understand the Control Block.
- Pass `shared_ptr` correctly.
- Know when to use `shared_ptr`.
- Explain internal working during interviews.

---

## 1. Why `shared_ptr`?

Suppose two objects need to use the same resource.

Example

Window

↓

Image

↑

Thumbnail

Both need the same image.

### Using `unique_ptr`

Window

↓

Image

Thumbnail

×

No Ownership — Not possible.

Need

Window

↓

Image

↑

Thumbnail

Both own it.

That's why `shared_ptr` exists.

---

## 2. What is `shared_ptr`?

A smart pointer with

**Shared Ownership**

Multiple smart pointers can own the same object.

```
p1
↓
Object
↑
p2
↑
p3
```

Memory is deleted only when

**Reference Count ↓ 0**

---

## 3. Creating `shared_ptr`

**Method 1**

```cpp
std::shared_ptr<int> ptr(new int(100));
```

Works.

**Method 2 (Recommended)**

```cpp
auto ptr = std::make_shared<int>(100);
```

Always prefer `make_shared()`.

---

## 4. Accessing Data

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto ptr = std::make_shared<int>(50);

    std::cout << *ptr;
}
```

Output

```
50
```

### Member Access

```cpp
class Student
{
public:

    void print()
    {
        std::cout << "Hello";
    }
};

int main()
{
    auto ptr = std::make_shared<Student>();

    ptr->print();
}
```

Output

```
Hello
```

---

## 5. Copying `shared_ptr`

Unlike `unique_ptr`, copy is allowed.

```cpp
auto p1 = std::make_shared<int>(100);

auto p2 = p1;
```

Memory

Reference Count = 2

```
p1
↓
Object
↑
p2
```

Another Copy

```cpp
auto p3 = p2;
```

Now

Reference Count = 3

```
p1
↓
Object
↑
p2
↑
p3
```

Example

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto p1 = std::make_shared<int>(500);

    auto p2 = p1;

    std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
}
```

Output

```
500
500
```

---

## 6. Reference Count

Check count

```cpp
auto ptr = std::make_shared<int>(10);

std::cout << ptr.use_count();
```

Output

```
1
```

Copy

```cpp
auto p2 = ptr;

std::cout << ptr.use_count();
```

Output

```
2
```

Example

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto p1 = std::make_shared<int>(10);

    std::cout << p1.use_count() << std::endl;

    auto p2 = p1;

    std::cout << p1.use_count() << std::endl;
}
```

Output

```
1
2
```

---

## 7. How Reference Count Changes

Step 1

```
p1
↓
Object
Count = 1
```

Copy

```
p1
↓
Object
↑
p2
Count = 2
```

Destroy `p2`

```
p1
↓
Object
Count = 1
```

Destroy `p1`

```
Count = 0
↓
delete object
```

---

## 8. Internal Working

Every `shared_ptr` points to

+----------------+
| Control Block  |
+----------------+
| Reference Count|
| Weak Count     |
| Deleter        |
| Allocator      |
+----------------+

↓

Actual Object

This Control Block is the heart of `shared_ptr`.

---

## 9. `make_shared()`

Preferred

```cpp
auto ptr = std::make_shared<int>(100);
```

Instead of

```cpp
std::shared_ptr<int> ptr(new int(100));
```

Why?

Only one allocation.

Object + Control Block → Single Allocation

Using `new`:

Allocation 1 → Object

Allocation 2 → Control Block

More allocations.

---

## 10. Passing `shared_ptr`

**By Value**

```cpp
void print(std::shared_ptr<int> ptr)
{
}
```

Reference count +1 — temporary copy created.

**Preferred**

```cpp
void print(const std::shared_ptr<int>& ptr)
{
}
```

Reference count: no change — much faster.

---

## 11. Returning `shared_ptr`

```cpp
std::shared_ptr<int> create()
{
    return std::make_shared<int>(50);
}

int main()
{
    auto ptr = create();
}
```

Perfectly valid.

---

## 12. Important Member Functions

**`get()`**

Returns raw pointer.

```cpp
auto ptr = std::make_shared<int>(10);

int* p = ptr.get();

std::cout << *p;
```

Output

```
10
```

Ownership still with `shared_ptr`.

**`reset()`**

Deletes current ownership.

```cpp
auto ptr = std::make_shared<int>(20);

ptr.reset();
```

Reference count 0 — memory deleted.

Replace object

```cpp
ptr.reset(new int(100));
```

**`swap()`**

```cpp
auto p1 = std::make_shared<int>(1);

auto p2 = std::make_shared<int>(2);

p1.swap(p2);

std::cout << *p1 << " " << *p2;
```

Result

```
2 1
```

**`unique()`** — checks if I am the only owner

```cpp
auto ptr = std::make_shared<int>(10);

std::cout << ptr.unique();
```

Output

```
1
```

After copy

```cpp
auto p2 = ptr;

std::cout << ptr.unique();
```

Output

```
0
```

---

## 13. Polymorphism

```cpp
class Base
{
public:

    virtual ~Base() = default;
};

class Derived : public Base
{
};

int main()
{
    std::shared_ptr<Base> ptr =
        std::make_shared<Derived>();
}
```

Perfectly valid.

---

## 14. Thread Safety

Good news: reference counting is thread safe.

But object access is NOT thread safe — you need a mutex.

---

## 15. Performance

`shared_ptr` stores a pointer + control block + reference count — larger than `unique_ptr`.

Reference counting also has overhead.

---

## 16. Common Mistakes

**Creating two `shared_ptr` from same raw pointer — Wrong**

```cpp
int* p = new int(10);

std::shared_ptr<int> p1(p);

std::shared_ptr<int> p2(p);
```

Now two Control Blocks — both delete same object → double delete.

**Correct**

```cpp
auto p1 = std::make_shared<int>(10);

auto p2 = p1;
```

**Using `get()` — Wrong**

```cpp
delete ptr.get();
```

Double delete. Never manually delete memory managed by `shared_ptr`.

**Passing by Value — Wrong**

```cpp
void fun(std::shared_ptr<int> p)
{
}
```

Reference count changes. Preferred:

```cpp
void fun(const std::shared_ptr<int>& p)
{
}
```

---

## 17. `shared_ptr` vs `unique_ptr`

| `unique_ptr` | `shared_ptr` |
| --- | --- |
| Single Owner | Multiple Owners |
| Cannot Copy | Copy Allowed |
| Move Only | Copy + Move |
| Very Fast | Slightly Slower |
| No Reference Count | Reference Count |
| Small | Larger |

---

## 18. Interview Questions

Q1 Why is `shared_ptr` slower?

Because it maintains a reference count (typically with atomic operations), which adds memory and runtime overhead.

Q2 Where is the reference count stored?

Inside the Control Block.

Q3 Why prefer `make_shared()`?

Single allocation, faster, better cache locality, exception safe.

Q4 What happens when count becomes zero?

```
delete object
↓

delete control block
```

Q5 Does copying duplicate the object?

No. Only the pointer is copied. Reference count increases.

Q6 Can `shared_ptr` create memory leaks?

Yes. When

```
A
↓
B
↑
A
```

Both own each other — reference count never reaches 0. Solution: `weak_ptr` (covered next).

---

## Practice Programs

- Create a `shared_ptr<int>`.
- Copy it and print `use_count()`.
- Create three `shared_ptr`s pointing to the same object.
- Pass a `shared_ptr` by value and observe `use_count()`.
- Pass a `shared_ptr` by `const` reference and compare `use_count()`.
- Use `unique()` before and after copying.
- Use `reset()` to release ownership.
- Use `swap()` with two `shared_ptr`s.
- Store a derived object in `shared_ptr<Base>`.
- Demonstrate why creating two `shared_ptr`s from the same raw pointer is dangerous (understand the concept—don't rely on undefined behavior in production code).

## Key Takeaways

- `shared_ptr` enables shared ownership through reference counting.
- The managed object is destroyed only when the last owning `shared_ptr` is destroyed or reset.
- Prefer `std::make_shared()` over `new`.
- Pass `shared_ptr` by `const&` when you don't need to share ownership.
- Never create multiple `shared_ptr`s from the same raw pointer.
- Never manually delete the pointer returned by `get()`.
- Use `shared_ptr` only when shared ownership is genuinely required; otherwise, prefer `unique_ptr`.

The next topic is `std::weak_ptr`, which exists primarily to observe objects managed by `shared_ptr` witho