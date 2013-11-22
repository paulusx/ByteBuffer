#ifndef _BYTE_BUFFER_H_
#define _BYTE_BUFFER_H_

#include "accumulator.hh"

#include <vector>
#include <iostream>
//#include <>

namespace byte_buffer
{
    
    class FullStorage {};
    
    template<size_t S>
    class VectorStorage
    {
    public:
        VectorStorage(): m_storage(S,'\0'){}
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

    
    template<size_t S, template<size_t> class Storage >
    class StackAllocator: public Storage <S>
    {
    public:
        StackAllocator(): head(0), bottom(Storage<S>::operator&()) {};
        void* allocate(size_t size)
            {
                void* ret = &(static_cast<char*>(bottom)[head]) ;//[head];
                if(head + size < Storage<S>::size())
                {
                    head = static_cast<char*>(bottom)[head] + size;
                    return ret;
                }
                return NULL;
            }

        size_t freeSpace() {return Storage<S>::size() - head ;}
            
    private:
        size_t head;
        void* bottom;
        
    };

        
    template< size_t S,
              template<size_t> class Storage,
              template<size_t, template<size_t> class> class Allocator >
    class ByteBuffer: public Allocator<S, Storage>
    {
    public:
        void push(void* buffer, size_t size)
            {
                void* v = Allocator<S, Storage>::allocate(size);
                if(!v) throw FullStorage();
                memcpy(v, buffer, size);
            }

        const void*  operator& () {return Storage<S>::operator& () ;}        
    private:

        
    };

    
    
}

#endif /* _BYTE_BUFFER_H_ */










