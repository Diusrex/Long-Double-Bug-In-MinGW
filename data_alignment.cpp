#include <iostream>
#include <cstdint>
#include <iomanip>

// This program requires c++11
// Use --std=c++11 if you have c++11 compatible compiler

struct EightBytes
{
    int32_t x, y;
};

// Adds padding after the char b
struct TenBytes
{
    int32_t x, y;
    char a, b; // char padding[2]
};

// Adds padding after the char a, and the char b
struct TenBytesReordered
{
    int32_t x;
    char a; // char padding[3]
    int32_t y;
    char b; // char padding[3]
};

struct LongDoubleAndChar
{
    long double x;
    char y;
};

int main()
{
    std::cout << "Size of int: " << sizeof(int32_t) << ".\n";
    std::cout << "Size of EightBytes: " << sizeof(EightBytes) << ".\n";
    std::cout << "Size of TenBytes: " << sizeof(TenBytes) << ".\n";
    std::cout << "Size of TenBytesReordered: " << sizeof(TenBytesReordered) << ".\n";
    std::cout << "Size of LongDoubleAndChar: " << sizeof(LongDoubleAndChar) << ".\n\n";
    
    int32_t number = 1234;
    
    // A little hack to move by one byte
    int32_t *warpedAddress = (int32_t *)(1 + (char *) &number);
    std::cout << "Address of number: " << &number << ".\n";
    std::cout << "Address of warped: " << warpedAddress << ".\n";
    
    std::cout << "Warped value: " << *warpedAddress << ".\n\n";
    
    TenBytes tenBytes;
    uintptr_t tenBytesAddr = (uintptr_t) (void *) &tenBytes;
    std::cout << "Address of tenBytes: " << &tenBytes << ".\n";
    std::cout << "Values of addrval: " << std::hex <<  tenBytesAddr << ".\n";
    std::cout << "Moddable by largest member size (4): " << ((tenBytesAddr % 4 == 0) ? "yes" : "no") << ".\n";
}