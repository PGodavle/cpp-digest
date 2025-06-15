# Best Practices for Pointers and Memory Management
 - Use Smart Pointers:
   Prefer std::unique_ptr for single ownership and std::shared_ptr for shared ownership. Avoid raw pointers for owning resources.
 - Initialize Pointers:
   Always initialize pointers to nullptr or a valid address to avoid undefined behavior.
 - Avoid Raw new/delete:
   Use std::make_unique and std::make_shared to create smart pointers, which are exception-safe.
 - Match new and delete:
   Use delete for new and delete[] for new[].
 - Check for nullptr:
   Before dereferencing, ensure pointers are not nullptr.
 - Avoid Circular References:
   Use std::weak_ptr to break cycles in shared_ptr scenarios.
 - Profile Memory Usage:
   Use tools like Valgrind or AddressSanitizer to detect leaks and errors.
