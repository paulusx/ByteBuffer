#ifndef _BYTE_BUFFER_H_
#define _BYTE_BUFFER_H_

#include "accumulator.hh"

#include <vector>
#include <iostream>


namespace byte_buffer
{
    
    template<size_t S>
    class VectorStorage
    {
    public:
        VectorStorage(): m_storage(S,'\0'){ std::cout << "st "<< &m_storage << std::endl;}
        size_t size() {m_storage.size();}
        size_t resize(size_t new_size) {m_storage.resize(new_size);}
        void*  operator& () {return &m_storage[0];}
    private:       
        std::vector<char> m_storage;
    };

    template<size_t S>
    class SimpleStorage
    {
    public:
        void*  operator& () {return m_storage;}
        size_t size() {return S;}
    private:
        char m_storage[S];
    };
    


    template<size_t S, template<size_t> class Storage>
    class ByteBuffer : public Storage <S>
    {
        
        
    };

    
    
}

#endif /* _BYTE_BUFFER_H_ */

