class A {
public:
    void show() { std::cout << "Hello from A" << std::endl; }
};

class B : virtual public A {
    // ...
};

class C : virtual public A {
    // ...
};

class D : public B, public C {
    // ...
};
