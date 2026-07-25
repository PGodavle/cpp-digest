#include <iostream>

class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // Unary '-' (Negation)
    Point operator-() const {
        return Point(-x, -y);
    }

    // Unary '!' (Checks if at origin: 0,0)
    bool operator!() const {
        return (x == 0 && y == 0);
    }

    void display() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

int main() {
    Point p1(5, -3);
    Point p2 = -p1; // Output: (-5, 3)
    p2.display();

    Point origin(0, 0);
    if (!origin) {
        std::cout << "Point is at the origin!\n";
    }
}