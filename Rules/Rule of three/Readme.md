If your class defines any one of these, it probably needs all three:

Destructor
Copy constructor
Copy assignment operator

~Class();

Class(const Class&);

Class& operator=(const Class&);

Why do these rules exist?

class String {
    char* data;

public:
    String() {
        data = new char[100];
    }

    ~String() {
        delete[] data;
    }
};

The compiler automatically generates:

Copy constructor
Copy assignment operator

These generated functions perform a shallow copy.

String s1;
String s2 = s1;

After copying:

s1.data ----+
            |
            v
         Heap Memory
            ^
            |
s2.data ----+

Now both objects point to the same memory.

When both destructors execute:

delete[] data;
delete[] data;   // Double delete (Undefined Behavior)

This is exactly what the Rule of Three addresses.
