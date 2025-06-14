#include <iostream>
using namespace std;
//reinterpret_cast is used for low-level reinterpreting of the underlying bit patterns of data. It can cast between pointer types and even between integers and pointers. 
//Use it with caution because it bypasses the type system almost entirely.

//Example: Casting a pointer of one type to another
int main() {
    int value = 100;
    // Cast the address of value to a pointer to char
    char* ptr = reinterpret_cast<char*>(&value);
    
    // Print out the first byte of the integer 'value'
    cout << "First byte of value: " << static_cast<int>(*ptr) << endl;
    return 0;
}
