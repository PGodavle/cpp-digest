#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int factor = 3;
    std::vector<int> numbers = {1, 2, 3, 4};
    
    // Capture 'factor' by value (copy) or by reference if you want to modify it.
    std::for_each(numbers.begin(), numbers.end(), [factor](int &n) {
        n *= factor;
    });
    
    for (int n : numbers)
        std::cout << n << " ";  // Output: 3 6 9 12
    return 0;
}
