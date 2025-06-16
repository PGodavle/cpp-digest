#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> doubled;
    doubled.resize(numbers.size());

    std::transform(numbers.begin(), numbers.end(), doubled.begin(), [](int x) {
        return x * 2;
    });

    for (int n : doubled)
        std::cout << n << " ";  // Output: 2 4 6 8 10
    return 0;
}
