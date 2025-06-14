# Downcasting (Base → Derived)

# What It Is: 
Downcasting is converting a pointer or reference of a base class to a pointer or reference of a derived class.

# The Challenge: 
Because the base pointer might not actually point to an object of the derived class, this conversion is risky.

# Types of Downcasting:
 ## Using static_cast:
  - Assumes that you know the actual object type.
  - No runtime type safety check is performed. If the conversion is incorrect, you may invoke undefined behavior.

 ## Using dynamic_cast:
  - Performs a runtime check to ensure the cast is valid.
  - Returns nullptr (for pointers) or throws an exception (for references) if the cast fails.
