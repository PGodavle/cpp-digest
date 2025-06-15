#include <iostream>
using namespace std;

//In this example, the makeItSpeak function doesn’t need to know the exact type of animal. It relies on virtual functions to perform the right action at runtime.
class Animal {
public:
    virtual void speak() {
        cout << "Some generic animal sound." << endl;
    }
    virtual ~Animal() {}  // Virtual destructor for proper cleanup
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Meow!" << endl;
    }
};

void makeItSpeak(Animal* animal) {
    animal->speak();  // Calls the appropriate function at runtime
}

int main() {
    Animal* myDog = new Dog();
    Animal* myCat = new Cat();

    makeItSpeak(myDog); // Outputs: Woof!
    makeItSpeak(myCat); // Outputs: Meow!

    delete myDog;
    delete myCat;
    return 0;
}
