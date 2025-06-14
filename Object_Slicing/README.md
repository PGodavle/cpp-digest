# What Is Object Slicing?
When you copy or assign a derived class object to a base class object (by value), object slicing occurs. During this process, the portion of the derived object that extends beyond the base part is "sliced off" or lost. In other words, 
only the base class subobject is copied, and any additional data or behavior defined in the derived class is discarded.

# When Can Object Slicing Occur?
# Function Arguments:
When a function expects a base class parameter by value and you pass a derived object.

# Assignment:
When you assign a derived object to an existing base class object by value.

# STL Containers:
Storing derived objects in containers of base objects (by value) inadvertently causes slicing. Instead, storing pointers (or references, or smart pointers) maintains the full object.

# Implications of Object Slicing
## Loss of Derived Class Data:
Any additional members or state in the derived class are lost once slicing occurs.

## Loss of Polymorphism:
Virtual function calls on a sliced object will resolve to the base class version because the object no longer carries the derived class’s information.

## Potential Bugs:
If the sliced-off portion contains vital behavior or state, object slicing can lead to bugs that are subtle and difficult to diagnose.

# How to Avoid Object Slicing
   ## Pass Objects by Reference or Pointer: 
   Instead of passing objects by value, pass by reference (or pointer) to ensure the full object is used.

    cpp
    // Pass by reference to avoid slicing:
    void displayByRef(const Base& b) {  
        b.print();  // Calls the correct overridden function in Derived if applicable.
    }
   ## Use Smart Pointers:
   Modern C++ encourages using smart pointers (like std::unique_ptr or std::shared_ptr) to manage polymorphic objects in containers and function interfaces.
   ## Design Considerations:
   Evaluate whether object slicing is acceptable in your design. Sometimes, it might be a desirable behavior, but often it’s an unintended side effect.

# Real-World Analogy
Imagine you have a multi-layered cake where the bottom layer represents the base class, and the top layers represent additional features of the derived class.
If you cut a slice of only the bottom layer from the cake (copying by value), you lose all the extra flavors and decorations from the top layers. 
This slice (analogous to the object after slicing) represents only the base, missing the complete, enriched experience of the full cake (the derived object).
