#ifndef _BYTE_BUFFER_H_
#define _BYTE_BUFFER_H_

#include <accumulator.hh>
#include <exceptions.hh>


namespace byte_buffer
{
    template< size_t S,
              template<size_t> class Storage,
              template<size_t, template<size_t> class> class Allocator >
    class ByteBuffer: public Allocator<S, Storage>
    {
    public:
        void push(const void* buffer, size_t size)
            {
                void* v = Allocator<S, Storage>::allocate(size);
                if(!v) throw BadAlloc();
                memcpy(v, buffer, size);
            }

        void push(Accumulator const& acc )
            {
                void* v = Allocator<S, Storage>::allocate(acc.size());
                if(!v) throw BadAlloc();
                acc.dump(v);

            }

        size_t get(void * const data)
            {
                return Allocator<S, Storage>::get(data);
            }

        void pop()
            {

            }

        const void*  memory() const {return Storage<S>::memory();}
    };
}

#endif /* _BYTE_BUFFER_H_ */










