#include <iostream>
using namespace std;

//dynamic_cast is primarily used for safely converting pointers and references within an inheritance hierarchy. 
//It performs runtime checks to ensure that the conversion is valid. It works only with polymorphic classes (classes with at least one virtual function).

//Example: Safely downcasting in an inheritance hierarchy

cpp
class Base {
public:
    virtual ~Base() {} // Ensure polymorphic behavior
};

class Derived : public Base {
public:
    void derivedMethod() { cout << "Derived method called!" << endl; }
};

int main() {
    Base* basePtr = new Derived;
    
    // Attempt to downcast Base* to Derived*
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    
    if (derivedPtr) { // Check if downcast was successful
        derivedPtr->derivedMethod();
    } else {
        cout << "Invalid cast" << endl;
    }
    
    delete basePtr;
    return 0;
}
