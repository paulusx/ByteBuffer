#include<iostream>
#include<vector>
#include <string>

#include "byte_buffer.hh"

#include <memory>


struct sx
{
    unsigned int a;
    unsigned int b;
    char c[120];
};

    


int main(int argc, char *argv[])
{
    int a[60] = {6};
    unsigned long long b = 33322;
    sx s = {0xffffffff,0x00,{'9'}};

    std::vector<char> buffer;
    
    byte_buffer::Accumulator acc;
    acc.push(s).push(b).push(a);        

    buffer.resize( acc.size());
    acc.fillMemory(&(buffer[0]));

    std::cout << "Size: " << buffer.size() << std::endl;
    
    return 0;
}


















