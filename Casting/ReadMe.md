# CASTING
Casting in C++ is the process of converting a variable from one data type to another.
Unlike some languages where such conversions can be implicit or loose, C++ provides precise and expressive tools for this conversion to ensure type safety, readability.

## Why Use Casting in C++?
- Type Conversion: Often, you need to convert data from one type to another(e.g converting an int to a char for ASCII representation).
- Polymorphism: In object-oriented programming, safe downcasting with dynamic_cast allows you to work with dervied class safety.
- Interoperbility: When interfacing with C libraries or hardware-level operations, casts like reinterpret_cast offer the flexibility required.
- Const-Correctness: Sometimes you need to interface with APIs that don't follow const-correct guidlines; const_cast provides a workaround.

# Summary Table of Casts

| Cast Type        | Use Case                                                 | Safety Check    | Pros                               | Cons                                                            |
|------------------|----------------------------------------------------------|-----------------|------------------------------------|-----------------------------------------------------------------|
| C-style Cast     | General purpose conversion                               | No              | Concise                            | Ambiguous, unsafe, and hard to debug                            |
| static_cast      | Conversions between related types, numeric conversion    | Compile-time    | Clear intent, no overhead          | Limited to simple conversions                                   |
| dynamic_cast     | Safe downcasting in polymorphic hierarchies              | Run-time        | Ensures valid conversion           | Requires polymorphic types, runtime overhead                    |
| reinterpret_cast | Low-level converting of pointer types or unrelated types | None            | Powerful for low-level operations  | Not type-safe, potential for undefined behavior                 |
| const_cast       | Adding or removing const qualifiers                      | No (just const) | Allows modification when necessary | Can break const-correct design, undefined behavior when misused |
