#include <iostream>
#include <iomanip>
#include <float.h>

// This program will allow you to see a long double number is stored in your computer, as well as what changes when it is wrongly interpreted

// The code for this program is fairly implementation specific.
// The biggest part is how I assume that there are two bytes of padding at the end of a long double which depends on the compiler that you use. It should be correct for g++.

long double value = 123.456789L;

// Change these to choose which formats are outputted
const bool ShowInHex = true;
const bool ShowInBinary = true;

// Would use int8_t, but it is in c++11
typedef unsigned char BYTE;

bool IsBigEndian();

// The end is exclusive
void PrintOutAsStored(BYTE *bytes, int end, int start = 0, int inc = 1);

void PrintOutAsInterpreted(BYTE * bytes, int size);

void PrintOutByteInHex(BYTE byte);
void PrintOutByteInBinary(BYTE byte);

int main()
{
    std::cout << "Size of long double: " << sizeof(long double) << "\n";
    std::cout << "Size of double: " << sizeof(double) << "\n\n";
    
    BYTE * bytes = (BYTE *) &value;
    
    std::cout << "When printed as long double: " << value << '\n';
    std::cout << "When interpreting bits as double: " << *(double *) &value << ". This is NOT a cast\n";
    std::cout << "When casted to double: " << (double) value << '\n';
    
    std::cout << "Stored as:\n";
    PrintOutAsStored(bytes, sizeof(long double));
    
    std::cout << "Properly interpreted as:\n";
    std::cout << "Note, assumes your computer uses 2 extra bytes for padding (or stores in 96 bits)\n";
    PrintOutAsInterpreted(bytes, sizeof(long double) - 2);
    
    std::cout << "Interpreted incorrectly as:\n";
    PrintOutAsInterpreted(bytes, sizeof(double));
    
    std::cout << "Should be interpreted as:\n";
    double valAsDouble = (double) value;
    bytes = (BYTE *) &valAsDouble;
    
    PrintOutAsInterpreted(bytes, sizeof(double));
}

void PrintOutAsStored(BYTE *bytes, int end, int start, int inc)
{
    if (ShowInHex)
    {
        for (int i = start; i != end; i += inc)
            PrintOutByteInHex(bytes[i]);
        
        std::cout << "\n\n";
    }
    
    if (ShowInBinary)
    {
        for (int i = start; i != end; i += inc)
            PrintOutByteInBinary(bytes[i]);
        
        std::cout << "\n\n";
    }
}

void PrintOutAsInterpreted(BYTE *bytes, int size)
{
    if (IsBigEndian())
        PrintOutAsStored(bytes, size);
    
    // Need to go in reverse through bits in little-endian
    else
        PrintOutAsStored(bytes, -1, size - 1, -1);
}

void PrintOutByteInHex(BYTE byte)
{
    // Explicity show it as being a full byte
    std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(byte) << " ";
}

void PrintOutByteInBinary(BYTE byte)
{
    for (int cBit = (1 << 7); cBit; cBit >>= 1)
    {
        std::cout << ((byte & cBit) ? '1' : '0');
    }
    std::cout << ' ';
}

bool IsBigEndian()
{
    int num = 1;
    return *((char *) &num) == 0;
}