When a C or C++ program is executed, the operating system allocates a continuous region of virtual memory for the process. This virtual address space is divided into 5 major memory segments:

---

```text
  +-----------------------------------+ High Memory Addresses
  | Environment & Command Line Args   |
  +-----------------------------------+
  |               STACK               | Stores local variables, function frames
  |                 |                 | (Grows downwards ↓)
  |                 v                 |
  |                                   |
  |                 ^                 |
  |                 |                 | (Grows upwards ↑)
  |               HEAP                | Dynamically allocated memory
  +-----------------------------------+
  |          BSS SEGMENT              | Uninitialized global & static variables
  +-----------------------------------+
  |          DATA SEGMENT             | Initialized global & static variables
  +-----------------------------------+
  |          TEXT SEGMENT             | Executable machine code (Read-only)
  +-----------------------------------+ Low Memory Addresses

```

---

## 1. Text (Code) Segment

* **What it stores:** Compiled executable machine instructions.
* **Characteristics:**
* **Read-only:** Prevents programs from modifying their own code instructions during execution.
* **Shareable:** Multiple instances of the same binary share the same text segment in memory to save RAM.



---

## 2. Initialized Data Segment (`.data`)

* **What it stores:** Global variables, `static` variables, and constants that are **explicitly initialized** in the source code.
* **Characteristics:** Divided into a **Read-Write** section (modifiable globals) and a **Read-Only** section (string literals, `const` globals).

```c
int global_var = 100;     // Stored in Data Segment (Read-Write)
const int max_val = 500;  // Stored in Data Segment (Read-Only)

```

---

## 3. Uninitialized Data Segment (`.bss`)

* **What it stores:** Global and `static` variables that are **not explicitly initialized**.
* **Characteristics:**
* **BSS** stands for *Block Started by Symbol*.
* The operating system automatically initializes all memory in this section to zero/NULL before execution begins.
* Takes up minimal disk space in the binary file because only the size requirement is recorded.



```c
int uninit_global;       // Stored in BSS (auto-initialized to 0)
static float temp;       // Stored in BSS (auto-initialized to 0.0)

```

---

## 4. Heap

* **What it stores:** Dynamically allocated memory created at runtime.
* **Characteristics:**
* Allocated using C functions like `malloc()`, `calloc()`, `realloc()`, or C++ operators like `new`.
* Must be manually freed using `free()` or `delete`/`delete[]`; failure to do so causes **memory leaks**.
* Typically grows **upward** towards higher memory addresses.



```c
int *ptr = (int *)malloc(10 * sizeof(int)); // Memory allocated on Heap
delete[] ptr;                               // C++ deallocation

```

---

## 5. Stack

* **What it stores:** Local variables, function arguments, stack frame pointers, and return addresses.
* **Characteristics:**
* Operates on a **LIFO** (Last In, First Out) principle.
* Automatically allocated and freed as functions are called and returned.
* Grows **downward** toward lower memory addresses.
* If recursion goes too deep or excessive memory is allocated locally, it results in a **Stack Overflow**.



```c
void myFunction(int param) {
    int local_var = 42; // Allocated on Stack
} // Automatically deallocated when function returns

```

---

## Quick Summary Comparison

| Segment | Allocated By | Lifetime | Permissions | Growth Direction |
| --- | --- | --- | --- | --- |
| **Text** | Compiler / OS | Process run | Read-Only | Static size |
| **Data** | Compiler / Startup | Process run | Read / Write | Static size |
| **BSS** | Compiler / Startup | Process run | Read / Write | Static size |
| **Heap** | Developer (Runtime) | Until `free()` / `delete` | Read / Write | Upward ↑ |
| **Stack** | System (Automatic) | Scope of Function | Read / Write | Downward ↓ |
