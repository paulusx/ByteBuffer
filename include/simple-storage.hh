#ifndef _SIMPLE_STORAGE_HH_
#define _SIMPLE_STORAGE_HH_

namespace byte_buffer
{

    template<size_t S>
    class SimpleStorage
    {
    public:
        void*  memory() {return m_storage;}
        size_t size() {return S;}
    private:
        char m_storage[S];
    };

}   

#endif /* _SIMPLE_STORAGE_HH_ */
