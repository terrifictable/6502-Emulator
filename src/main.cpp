#include <iostream>

#define unused [[maybe_unused]]


int main (unused int argc, unused char *argv[]) {
    std::cout << "Hello World!" << std::endl;

    return 0;
}

