#include <iostream>
using namespace std;

//const_cast is used to add or remove the const qualifier from a variable. 
//It’s the only cast that can do this conversion and is useful when interfacing with legacy code or APIs that were not designed with const-correctness in mind.

//Example: Removing const

void printAndModify(char* str) {
    cout << "Original string: " << str << endl;
    str[0] = 'H';  // Modifying the string
}

int main() {
    const char* text = "hello";
    
    // Remove constness to pass to function (use with caution)
    printAndModify(const_cast<char*>(text));
    
    // Warning: Modifying a string literal is undefined behavior in C++;
    // In a real program, the data should be stored in a non-const array.
    return 0;
}
