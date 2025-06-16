#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6};
    // Remove even numbers
    data.erase(
        std::remove_if(data.begin(), data.end(), [](int x) { return x % 2 == 0; }),
        data.end()
    );
    for (int n : data)
        std::cout << n << " ";  // Output: 1 3 5 
    return 0;
}
