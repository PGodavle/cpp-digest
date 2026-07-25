What is unique_ptr?

A smart pointer with exclusive ownership.

Only one object owns the resource.

unique_ptr
     |
     ▼
+-----------+
| Heap Obj  |
+-----------+
Creating unique_ptr
Method 1
std::unique_ptr<int> ptr(new int(100));

Works.

Method 2 (Recommended)
auto ptr = std::make_unique<int>(100);

Always prefer make_unique().

Why?

Cleaner
Exception safe
No repeated type
Accessing Data
#include <memory>
#include <iostream>

int main()
{
    auto ptr = std::make_unique<int>(25);

    std::cout << *ptr;
}

Output

25
Access Members
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
    auto ptr = std::make_unique<Student>();

    ptr->print();
}

Output

Hello
Copy is NOT Allowed

Wrong

auto p1 = std::make_unique<int>(10);

auto p2 = p1;

Compiler Error

Reason

Two owners cannot own same memory.
Move is Allowed
auto p1 = std::make_unique<int>(10);

auto p2 = std::move(p1);

Memory

Before

p1

↓

Object

After

p1 ---> nullptr

p2

↓

Object

Example

#include <memory>
#include <iostream>

int main()
{
    auto p1 = std::make_unique<int>(500);

    auto p2 = std::move(p1);

    if(p1 == nullptr)
        std::cout << "Moved\n";

    std::cout << *p2;
}

Output

Moved
500
Passing unique_ptr

Wrong

void fun(std::unique_ptr<int> p)
{
}

int main()
{
    auto ptr = std::make_unique<int>(10);

    fun(ptr);
}

Compiler Error.

Need ownership transfer.

Correct

fun(std::move(ptr));

Read only

void fun(const std::unique_ptr<int>& ptr)
{
    std::cout << *ptr;
}

Ownership remains with caller.

Returning unique_ptr
std::unique_ptr<int> create()
{
    return std::make_unique<int>(100);
}

int main()
{
    auto ptr = create();
}

Move happens automatically (or is elided).

Important Member Functions
get()

Returns raw pointer.

auto ptr = std::make_unique<int>(20);

int* p = ptr.get();

std::cout << *p;

Output

20

Ownership is still with unique_ptr.

release()

Releases ownership.

auto ptr = std::make_unique<int>(10);

int* raw = ptr.release();

delete raw;

Memory

Before

unique_ptr

↓

Object

After

unique_ptr ---> nullptr

raw

↓

Object

You must delete the raw pointer yourself.

reset()

Deletes current object and optionally points to a new one.

auto ptr = std::make_unique<int>(5);

ptr.reset(new int(20));

std::cout << *ptr;

Output

20
swap()
auto p1 = std::make_unique<int>(1);
auto p2 = std::make_unique<int>(2);

p1.swap(p2);

std::cout << *p1 << " " << *p2;

Output

2 1
Arrays

Wrong

std::unique_ptr<int> arr(new int[10]);

Correct

std::unique_ptr<int[]> arr(new int[10]);

arr[0] = 100;

Automatically uses

delete[]
Polymorphism
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
    std::unique_ptr<Base> ptr =
        std::make_unique<Derived>();
}

Perfectly valid.

Performance
Size of unique_ptr

↓

Usually

sizeof(raw pointer)

Very lightweight.

No reference counting.

Common Mistakes
Forgetting std::move()
fun(ptr);

Should be

fun(std::move(ptr));
Calling delete

Wrong

delete ptr.get();

unique_ptr will also delete it.

Double delete.

Using release()
auto raw = ptr.release();

Forgetting

delete raw;

Memory leak.

Interview Questions
Q1 Why can't unique_ptr be copied?

Because it represents exclusive ownership.

Q2 Why does unique_ptr support move semantics?

Ownership can be transferred safely without copying the underlying resource.

Q3 Difference between release() and reset()?
release()	reset()
Releases ownership	Deletes current object
Returns raw pointer	Doesn't return pointer
Caller must delete	Smart pointer handles deletion
Q4 Difference between get() and release()?
get()	release()
Ownership stays	Ownership transferred
Returns raw pointer	Returns raw pointer
Object still managed	Object no longer managed
Q5 Why prefer make_unique?
Exception safe
Cleaner syntax
Recommended by modern C++
Avoids repeating the type
