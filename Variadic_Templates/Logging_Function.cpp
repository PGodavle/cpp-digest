#include <iostream>

//Variadic templates are useful for implementing flexible logging systems that accept multiple arguments.

template<typename... Args>
void logMessage(const std::string& level, Args... args) {
    std::cout << "[" << level << "] ";
    (std::cout << ... << args) << std::endl; // Fold expression (C++17)
}

int main() {
    logMessage("INFO", "User ", "logged in with ID: ", 1234);
    logMessage("ERROR", "File not found: ", "config.txt");
    return 0;
}
