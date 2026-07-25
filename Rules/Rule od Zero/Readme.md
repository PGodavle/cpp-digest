Rule of Zero (Modern C++)

The best rule is often:

Don't write any of them.

Instead, use standard library classes that manage resources for you.

Instead of:

char* data;

Use:

std::string data;

Instead of:

int* arr;

Use:

std::vector<int> arr;

Instead of:

new
delete

Use:

std::unique_ptr
std::shared_ptr

Example:

class Employee {
    std::string name;
    std::vector<int> salaryHistory;
};

You don't need to write:

Destructor
Copy constructor
Copy assignment
Move constructor
Move assignment

The compiler-generated versions work correctly because std::string and std::vector already manage their own resources.
