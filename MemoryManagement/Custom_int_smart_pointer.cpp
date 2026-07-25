#include <iostream>

class MyPointer
{
private:
    int* ptr;

public:

    MyPointer(int value)
    {
        ptr = new int(value);
    }

    ~MyPointer()
    {
        delete ptr;
        std::cout << "Memory released\n";
    }


    int getValue()
    {
        return *ptr;
    }


    void setValue(int value)
    {
        *ptr = value;
    }
};


int main()
{
    MyPointer p(10);

    std::cout << p.getValue() << std::endl;

    p.setValue(20);

    std::cout << p.getValue() << std::endl;

    return 0;
}
