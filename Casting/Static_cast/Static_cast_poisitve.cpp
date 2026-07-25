#include <iostream>
using namespace std;

//Base → Derived (Only when you KNOW the object is actually derived)
//Works because the object is actually Derived.
class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void show() { cout << "Derived"; }
};

Base* b = new Derived();
int main() {
Derived* d = static_cast<Derived*>(b);
d->show();
}
