void processData(int&& x) { // Accepts only rvalues
    std::cout << "Processing rvalue: " << x << std::endl;
}

int main() {
    int a = 10;
    processData(std::move(a)); // Converts `a` to an rvalue
}
