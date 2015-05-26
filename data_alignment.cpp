#include <iostream>
#include <cstdint>
#include <iomanip>

// This program shows how your compiler may add padding into your own structs to make alignment easier
// Some of the padding comments may not be correct, depending on what your compiler does

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
}