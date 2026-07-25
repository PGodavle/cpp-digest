#include <iostream>

class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n = "", int a = 0) : name(n), age(a) {}

    // Friend function for '<<'
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "Name: " << p.name << ", Age: " << p.age;
        return os;
    }

    // Friend function for '>>'
    friend std::istream& operator>>(std::istream& is, Person& p) {
        std::cout << "Enter name and age: ";
        is >> p.name >> p.age;
        return is;
    }
};

int main() {
    Person p;
    std::cin >> p;  // Reads directly into object
    std::cout << p; // Prints object directly
}