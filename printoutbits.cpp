#include <iostream>
#include <iomanip>
#include <float.h>

// Change these to determine which formats are outputted
const bool ShowInHex = true;
const bool ShowInBinary = true;

// Would use int8_t, but it is in c++11, while this allows more versions
typedef unsigned char BYTE;

bool IsBigEndian();

void PrintOutAsStored(BYTE *bytes, int end, int start = 0, int inc = 1);

void PrintOutAsInterpreted(BYTE * bytes, int size);

void PrintOutByteInHex(BYTE byte);
void PrintOutByteInBinary(BYTE byte);

int main()
{
    std::cout << "Size of long double: " << sizeof(long double) << ".\n";
    std::cout << "Size of double: " << sizeof(double) << ".\n\n";
    
    long double val;
    val = 123.456789L;
    
    BYTE * bytes = (BYTE *) &val;
    
    std::cout << "When printed as long double: " << val << '\n';
    std::cout << "When interpreted as double: " << *(double *) &val << '\n';
    std::cout << "When casted to double (one fix): " << (double ) val << '\n';
    
    std::cout << "Stored as:\n";
    PrintOutAsStored(bytes, sizeof(long double));
    
    std::cout << "Properly interpreted as:\n";
    std::cout << "Note, assumes your computer uses 2 extra bytes for padding\n";
    PrintOutAsInterpreted(bytes, sizeof(long double) - 2);
    
    std::cout << "Interpreted as:\n";
    PrintOutAsInterpreted(bytes, sizeof(double));
    
    std::cout << "Should be interpreted as:\n";
    double valAsDouble = (double) val;
    bytes = (BYTE *) &valAsDouble;
    
    std::cout << "Double output: " << valAsDouble << '\n';
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