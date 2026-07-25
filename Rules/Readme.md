Comparison
Rule	C++ Version	Special Member Functions	When to Use
Rule of Three	C++98	Destructor, Copy Constructor, Copy Assignment	Class manually manages resources
Rule of Five	C++11	Rule of Three + Move Constructor + Move Assignment	Class manually manages resources and should support efficient moves
Rule of Zero	Modern C++	None	Prefer RAII types (std::string, std::vector, smart pointers)
Interview Questions
1. Why do we need the Rule of Three?

Because a class that owns resources needs a deep copy. The compiler-generated copy operations perform shallow copies, which can lead to double deletion or resource corruption.

2. Why was the Rule of Five introduced?

To take advantage of move semantics, which avoid unnecessary allocations and copies by transferring ownership of resources.

3. Which rule should you follow in modern C++?

The Rule of Zero whenever possible. Prefer standard library containers and smart pointers so you don't need to implement special member functions yourself.

4. When is the Rule of Five necessary?

When your class directly owns a resource, such as:

Dynamically allocated memory (new)
File handles
Sockets
Mutexes
Other OS or library resources
5. Can you have only a destructor?

Technically yes, but if your class owns a resource, that's usually a warning sign. A user-defined destructor often means you should also think about copy and move operations, because the compiler's defaults may not be correct.

Easy way to remember
Rule of Three = "If I manage a resource, I must define how to destroy, copy-construct, and copy-assign it."
Rule of Five = "Also define how to move-construct and move-assign it efficiently."
Rule of Zero = "Avoid manual resource management by using RAII types, so I define none of these functions."
