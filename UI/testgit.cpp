#include <iostream>
#include "gitVersion.hpp"

int main() {
    try {
        std::string git_version = get_git_version();
        std::cout << "Git version: " << git_version << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}