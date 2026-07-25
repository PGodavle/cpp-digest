Rule of Five (C++11)

C++11 introduced move semantics.

Besides the previous three, two new special member functions were added:

Move constructor
Move assignment operator

So now there are five:

Destructor

Copy Constructor

Copy Assignment

Move Constructor

Move Assignment
Move constructor

Instead of copying memory:

MyString s2 = std::move(s1);

Transfer ownership.

Before

s1 ----> Heap

After move

s2 ----> Heap

s1 ----> nullptr

Example:

MyString(MyString&& other)
{
    data = other.data;
    other.data = nullptr;
}

No allocation.

No copying.

Very fast.

Move assignment
obj2 = std::move(obj1);

Example:

MyString& operator=(MyString&& other)
{
    if(this != &other)
    {
        delete[] data;

        data = other.data;
        other.data = nullptr;
    }

    return *this;
}

Again,

Ownership is transferred.

Rule of Five Summary

If you define one of these, you should usually consider defining all five:

~Class()

Class(const Class&)

Class& operator=(const Class&)

Class(Class&&)

Class& operator=(Class&&)

Use:
