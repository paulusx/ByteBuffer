#include<iostream>
#include<vector>
#include <string>

#include "byte_buffer.hh"

#include <memory>


struct sx
{
    unsigned int a;
    unsigned int b;
    char c[12];
};

    


int main(int argc, char *argv[])
{
    // int a = 6;
    // unsigned long long b = 33322;
    // sx s = {0xffffffff,0x00,{1,2,3,4,5,6,7,8,9,10,11,12}};

    // std::vector<char> buffer;
    
    // byte_buffer::Accumulator acc;
    // acc.push(s).push(b).push(a);        

    // buffer.resize( acc.size() );
    // acc.dump(&(buffer[0]));

    byte_buffer::ByteBuffer<32, byte_buffer::VectorStorage> vs;
    
    
    std::cout << "Size: " << &vs << std::endl;
    
    return 0;
}


















//test repo
