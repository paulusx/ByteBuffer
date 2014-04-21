#ifndef _STACK_ALLOCATOR_HH_
#define _STACK_ALLOCATOR_HH_

namespace byte_buffer
{
    template<size_t S, template<size_t> class Storage >
    class StackAllocator: public Storage <S>
    {
    public:
        StackAllocator(): head(0), bottom(Storage<S>::memory()) {};
        void* allocate(size_t size)
            {
                void* ret = &(static_cast<char*>(bottom)[head]);
                if(head + size + sizeof(size_t) < Storage<S>::size())
                {
                    head += static_cast<char*>(bottom)[head] + size + sizeof(size_t);
                    size_t* psize = reinterpret_cast<size_t*>(static_cast<char*>(ret) + size);
                    *psize  = size;
                    return ret;
                }
                return NULL;
            }

        size_t getSize() const
            {
                if(head >= sizeof(size_t))
                {
                    return *(reinterpret_cast<size_t*>
                             (static_cast<char*>(bottom) + (head - sizeof(size_t))));
                }
                throw ContainerIsEmpty();
            }

        void * getData() const
            {
                if(head >= sizeof(size_t))
                {
                    return static_cast<char*>(bottom) + (head - getSize() - sizeof(size_t));
                }
                throw ContainerIsEmpty();
            }

        size_t free()
            {
                if(head >= sizeof(size_t))
                {
                    size_t size = getSize();
                    head -= (sizeof(size_t) + size);
                    return size;
                }
                throw ContainerIsEmpty();
            }

        size_t freeSpace() {return Storage<S>::size() - head ;}
        bool empty() const {return head == 0;}

    private:
        size_t head;
        void* bottom;
    };
} // namespace byte_buffer

#endif /* _STACK_ALLOCATOR_HH_ */










