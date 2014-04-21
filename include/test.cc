

    


int main(int argc, char *argv[])
{
    int a = 6;
    unsigned long long b = 33322;
    sx s = {0xffffffff,0x00,{1,2,3,4,5,6,7,8,9,10,11,12}};


    
    

//    byte_buffer::StackAllocator<32, byte_buffer::VectorStorage> vs;

    // std::cout << "free: " << vs.freeSpace() << std::endl;
    // vs.allocate(sizeof(s));
    // std::cout << "free: " << vs.freeSpace() << std::endl;
    // vs.allocate(sizeof(s));
    // std::cout << "free: " << vs.freeSpace() << std::endl;
    
    // std::cout << "vii: " << sizeof(s)  << std::endl;
    

   byte_buffer::ByteBuffer<320, byte_buffer::VectorStorage, byte_buffer::StackAllocator > vs;

   byte_buffer::Accumulator acc;

   std::vector<char> buffer;

   
   acc.push(s).push(b).push(a);        
   buffer.resize( acc.size() );
   acc.dump(&(buffer[0]));

   vs.push(&(buffer[0]), buffer.size());
   
   

    
        
    
    return 0;
}


















//test repo
