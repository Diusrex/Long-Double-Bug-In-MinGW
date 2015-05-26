#include <iostream>

// This program will allow you to test the endianness of your computer

int main()
{
    int val = 1;
    if (*(char *) &val)
        std::cout << "Is little endian\n";
    
    else
        std::cout << "Is big endian\n";
}