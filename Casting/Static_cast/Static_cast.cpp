#include <iostream>
using namespace std;

//static_cast is used for conversions that are checked at compile time. It is suitable for well-defined conversions such as from numeric types, pointer upcasting (from derived to base),
//or even between related pointer types when you are confident of their relationship.

//Example: Converting an int to a char
int main() {
    int num = 66;
    char letter = static_cast<char>(num);  // letter becomes 'B'
    cout << "Letter: " << letter << endl;
    return 0;
}
