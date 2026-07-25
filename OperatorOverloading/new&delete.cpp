#include <iostream>
#include <cstdlib> // For std::malloc and std::free
#include <new>     // For std::bad_alloc

class Player {
private:
    std::string name;
    int level;

public:
    Player(std::string n, int l) : name(n), level(l) {
        std::cout << "[Constructor] Player '" << name << "' created.\n";
    }

    ~Player() {
        std::cout << "[Destructor] Player '" << name << "' destroyed.\n";
    }

    // Overloading operator new for Player class
    static void* operator new(size_t size) {
        std::cout << "\n[Custom Class New] Allocating " << size << " bytes for Player...\n";
        void* ptr = std::malloc(size);
        if (!ptr) {
            throw std::bad_alloc(); // Throw exception on failure
        }
        return ptr;
    }

    // Overloading operator delete for Player class
    static void operator delete(void* ptr) noexcept {
        std::cout << "[Custom Class Delete] Deallocating memory for Player...\n";
        std::free(ptr);
    }
};

int main() {
    // 1. Allocates memory via Player::operator new, then calls Constructor
    Player* p1 = new Player("Hero", 10);

    // 2. Calls Destructor, then frees memory via Player::operator delete
    delete p1;

    return 0;
}