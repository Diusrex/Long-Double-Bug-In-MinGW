#include <iostream>

int main()
{
    int val = 1;
    if (*(char *) &val)
        std::cout << "Is little endian\n";
    
    else
        std::cout << "Is big endian\n";
}