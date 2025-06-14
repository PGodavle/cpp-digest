#include <iostream>
using namespace std;
//In displayByValue(): When passing an object by value, a copy is created. If you pass a Derived object as a Base parameter, only the Base part is copied. 
//The derivedData member is lost, and the print() method called is the one of the copied object. Although the base class declares print() as virtual, the object that was copied is purely of type Base—thus, it calls Base::print().

//Using a Reference: Passing by reference or pointer avoids slicing because the full object is accessed, preserving polymorphism (i.e., calling Derived::print() when appropriate).

class Base {
public:
    int baseData;
    Base() : baseData(0) {}
    virtual void print() const { 
        cout << "Base: " << baseData << endl; 
    }
};

class Derived : public Base {
public:
    int derivedData;
    Derived() : Base(), derivedData(0) {}
    void print() const override {
        cout << "Derived: " << baseData << ", " << derivedData << endl;
    }
};

void displayByValue(Base b) {  // Parameter is passed by value.
    b.print();  // Will call Base::print(), not Derived::print()
}

int main() {
    Derived d;
    d.baseData = 5;
    d.derivedData = 10;

    // Object slicing occurs here:
    displayByValue(d);

    // If we did this instead, no slicing occurs:
    Base& ref = d;
    ref.print();  // Calls Derived::print() due to polymorphism

    return 0;
}
