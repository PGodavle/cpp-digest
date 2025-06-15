#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() {
        cout << "Base class show function called." << endl;
    }
    // Virtual destructor ensures proper cleanup of derived objects
    virtual ~Base() {}
};

class Derived : public Base {
public:
    // The override keyword ensures this function correctly overrides Base::show
    void show() override {
        cout << "Derived class show function called." << endl;
    }
};

int main() {
    Base* b = new Derived();
    b->show();    // Dynamically calls Derived::show
    delete b;
    return 0;
}
