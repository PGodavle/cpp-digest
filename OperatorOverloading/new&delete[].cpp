#include <iostream>
#include <cstdlib>
#include <new>

// Track total memory allocated globally
static size_t totalAllocated = 0;

// Global operator new
void* operator new(size_t size) {
    totalAllocated += size;
    std::cout << "[Global New] Allocated " << size << " bytes | Total: " << totalAllocated << " bytes\n";
    
    void* ptr = std::malloc(size);
    if (!ptr) throw std::bad_alloc();
    return ptr;
}

// Global operator delete
void operator delete(void* ptr) noexcept {
    std::cout << "[Global Delete] Deallocated memory\n";
    std::free(ptr);
}

int main() {
    int* a = new int(42);         // Uses global operator new
    double* b = new double(3.14); // Uses global operator new

    delete a; // Uses global operator delete
    delete b; // Uses global operator delete

    return 0;
}