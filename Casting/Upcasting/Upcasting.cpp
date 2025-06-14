#include <iostream>
using namespace std;

//Explanation: Here, a Derived object is treated as a Base object. The virtual function display() ensures that the correct override in Derived is called even though the pointer is of type Base*.

class Base {
public:
    virtual void display() { cout << "Display Base" << endl; }
    virtual ~Base() {}  // Ensures polymorphic behavior.
};

class Derived : public Base {
public:
    void display() override { cout << "Display Derived" << endl; }
    void derivedOnly() { cout << "Function only in Derived" << endl; }
};

int main() {
    Derived d;
    Base* b = &d;  // Implicit upcasting.
    b->display();  // Calls Derived::display() due to polymorphism.
    return 0;
}
