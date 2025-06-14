#include <iostream>
using namespace std;

//In the above example, dynamic_cast checks at runtime whether b actually points to a Derived object. If it does, the cast succeeds; otherwise, you get a nullptr and can handle the error gracefully.
class Base {
public:
    virtual void display() { cout << "Display Base" << endl; }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void display() override { cout << "Display Derived" << endl; }
    void derivedOnly() { cout << "Function only in Derived" << endl; }
};

int main() {
    Base* b = new Derived;   // b actually points to a Derived object.
    
    // Safe downcasting using dynamic_cast:
    Derived* d = dynamic_cast<Derived*>(b);
    if (d) {
        d->derivedOnly();  // Safe to call because the object is really Derived.
    } else {
        cout << "Downcasting failed!" << endl;
    }
    
    delete b;
    return 0;
}
