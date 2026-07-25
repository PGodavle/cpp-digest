#include <iostream>


template<typename T>
class MyPointer
{
private:

    T* ptr;


public:

    MyPointer(T* value)
        : ptr(value)
    {
    }


    ~MyPointer()
    {
        delete ptr;
    }


    T& operator*()
    {
        return *ptr;
    }


    T* operator->()
    {
        return ptr;
    }
};



class Student
{
public:

    void display()
    {
        std::cout<<"Student Object\n";
    }
};



int main()
{

    MyPointer<int> p(new int(100));

    std::cout << *p << std::endl;


    MyPointer<Student> s(new Student());

    s->display();


    return 0;
}
