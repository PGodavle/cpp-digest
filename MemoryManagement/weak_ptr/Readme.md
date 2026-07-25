std::weak_ptr
Learning Objectives

After completing this topic, you should be able to:

Understand why weak_ptr exists.
Explain the difference between ownership and observation.
Understand circular references.
Use lock(), expired(), and use_count().
Explain weak_ptr in interviews.
Know when to use weak_ptr instead of shared_ptr.
1. Why do we need weak_ptr?

Suppose we already have

std::shared_ptr<int> ptr =
    std::make_shared<int>(100);

Now another object wants to observe this object.

Should it own it?

Not necessarily.

Sometimes it only wants to access it if it still exists.

That's exactly why weak_ptr exists.

2. What is weak_ptr?

A weak_ptr is a non-owning smart pointer.

It does NOT increase the reference count.

Think of it as

"I know this object exists, but I don't own it."

Ownership Diagram
shared_ptr
shared_ptr

↓

Object

Owns the object.

weak_ptr
shared_ptr

↓

Object

↑

weak_ptr

Observes the object.

Does NOT own it.

3. Creating weak_ptr
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(100);

    std::weak_ptr<int> wp = sp;
}

Notice

wp = sp;

No std::move().

No copy of object.

Just observing.

4. Does weak_ptr increase reference count?

Example

#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(50);

    std::cout << sp.use_count() << std::endl;

    std::weak_ptr<int> wp = sp;

    std::cout << sp.use_count() << std::endl;
}

Output

1
1

Reference count

Never changes.

Memory
shared_ptr

↓

Object

Count = 1

↑

weak_ptr

Weak pointer is

NOT counted.

5. Can we dereference weak_ptr?

Wrong

std::weak_ptr<int> wp;

*wp;

Compile Error.

Reason

A weak pointer

May point to

Nothing.

6. lock()

To use a weak pointer

Convert it into

shared_ptr

using

lock()

Example

#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(500);

    std::weak_ptr<int> wp = sp;

    if(auto temp = wp.lock())
    {
        std::cout << *temp;
    }
}

Output

500

Memory

shared_ptr

↓

Object

↑

weak_ptr

↓

lock()

↓

temporary shared_ptr
7. What happens internally?

Suppose

auto temp = wp.lock();

Temporary

shared_ptr

is created.

Reference Count

Before

1

↓

After lock()

2

After temp is destroyed

Count

↓

1
8. expired()

Checks

Is object already deleted?

Example

#include <iostream>
#include <memory>

int main()
{
    std::weak_ptr<int> wp;

    {
        auto sp = std::make_shared<int>(100);

        wp = sp;

        std::cout << wp.expired() << std::endl;
    }

    std::cout << wp.expired() << std::endl;
}

Output

0
1

Meaning

false

true
9. use_count()

Returns

Number of

shared_ptr

owners.

Example

#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(100);

    std::weak_ptr<int> wp = sp;

    std::cout << wp.use_count();
}

Output

1

Copy

auto sp2 = sp;

Output

2

Again

Weak pointer

Never increases it.

10. reset()

Break observation.

auto sp = std::make_shared<int>(100);

std::weak_ptr<int> wp = sp;

wp.reset();

Now

wp

↓

Empty
11. swap()
std::weak_ptr<int> w1;
std::weak_ptr<int> w2;

w1.swap(w2);

Swaps

Observed objects.

12. Circular Reference Problem

This is

THE

Most Important Interview Question.

Suppose

Employee owns Company.

Employee

↓

Company

Company owns Employee.

Company

↓

Employee

Using

shared_ptr

Both

Reference Counts

Become

1

Even after main ends

Still

1

Memory

Never deleted.

Example
#include <iostream>
#include <memory>

class Company;

class Employee
{
public:

    std::shared_ptr<Company> company;

    ~Employee()
    {
        std::cout << "Employee Destroyed\n";
    }
};

class Company
{
public:

    std::shared_ptr<Employee> employee;

    ~Company()
    {
        std::cout << "Company Destroyed\n";
    }
};

int main()
{
    auto e = std::make_shared<Employee>();

    auto c = std::make_shared<Company>();

    e->company = c;

    c->employee = e;
}

Output

Nothing Printed

Destructors

Never called.

Memory Leak.

Memory
Employee

↓

Company

↑

shared_ptr

↓

shared_ptr

Both keep each other alive forever.

Solution

One side

Must become

weak_ptr

Correct

class Company
{
public:

    std::weak_ptr<Employee> employee;
};

Now

Employee

↓

Company

↑

weak_ptr

Reference Count

Can become

0

Everything destroyed correctly.

Output
Company Destroyed

Employee Destroyed

No leak.

13. Internal Working

shared_ptr

Stores

Pointer

↓

Control Block

Control Block

Contains

Reference Count

Weak Count

Custom Deleter

Allocator

weak_ptr

Points to

Same

Control Block.

It does NOT

Own the object.

Memory Diagram
shared_ptr

↓

+--------------------+
| Control Block      |
|--------------------|
| Strong Count = 1   |
| Weak Count = 1     |
+--------------------+

↓

Actual Object
14. Performance

weak_ptr

Stores

Pointer

+

Control Block Pointer

Very lightweight.

No ownership.

No object copy.

15. Common Mistakes
Dereferencing directly

Wrong

*wp;

Must use

wp.lock();
Assuming weak_ptr keeps object alive

Wrong.

Example

std::weak_ptr<int> wp;

{
    auto sp = std::make_shared<int>(10);

    wp = sp;
}

Object

Already destroyed.

Forgetting to check lock()

Wrong

auto sp = wp.lock();

std::cout << *sp;

Correct

if(auto sp = wp.lock())
{
    std::cout << *sp;
}

Always verify that lock() succeeded before using the returned shared_ptr.

16. shared_ptr vs weak_ptr
shared_ptr	weak_ptr
Owns Object	Doesn't Own
Increases Reference Count	Doesn't Increase
Can Dereference	Cannot Dereference Directly
Deletes Object	Never Deletes
Shared Ownership	Observation
17. Interview Questions
Q1 Why was weak_ptr introduced?

To observe objects managed by shared_ptr without increasing the reference count, and to break circular ownership.

Q2 Does weak_ptr increase reference count?

No.

Only

shared_ptr

changes

Reference Count.

Q3 Why can't weak_ptr be dereferenced?

Because the object

May already

Be destroyed.

Q4 Why use lock()?

lock() safely creates a temporary shared_ptr only if the object still exists.

Q5 What does expired() do?

Checks

Whether

Managed object

Already destroyed.

Q6 What causes memory leak in shared_ptr?

Circular reference.

Example

A

↓

B

↑

A

Solution

weak_ptr
Q7 Can weak_ptr become shared_ptr?

Yes.

auto sp = wp.lock();
Practice Programs
Create a weak_ptr from a shared_ptr.
Verify that use_count() does not change after creating a weak_ptr.
Use lock() to access the object safely.
Use expired() before and after the owning shared_ptr goes out of scope.
Use reset() on a weak_ptr.
Swap two weak_ptr objects.
Build an Employee ↔ Company example with a circular reference using shared_ptr.
Fix the circular reference by replacing one shared_ptr with a weak_ptr.
Print constructor and destructor messages to observe object lifetimes.
Create multiple weak_ptrs observing the same object and verify that they don't affect the shared_ptr count.
Key Takeaways
weak_ptr is a non-owning observer of an object managed by shared_ptr.
It does not increase the shared ownership count.
You cannot dereference a weak_ptr directly.
Use lock() to safely obtain a temporary shared_ptr.
Use expired() to check whether the object has already been destroyed.
The most common use of weak_ptr is to break circular references between objects using shared_ptr.
weak_ptr works by referring to the same control block as the corresponding shared_ptr, but without contributing to the strong reference count.
Smart Pointer Summary
Feature	unique_ptr	shared_ptr	weak_ptr
Ownership	Exclusive	Shared	None (Observer)
Copy Allowed	❌ No	✅ Yes	✅ Yes
Move Allowed	✅ Yes	✅ Yes	✅ Yes
Reference Count	❌	✅ Strong Count	❌ Doesn't Increase Strong Count
Can Dereference	✅	✅	❌ (Use lock())
Best Use Case	Single owner	Multiple owners	Observing shared objects / breaking cycles
