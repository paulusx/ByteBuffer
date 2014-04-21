#ifndef _VECTOR_STORAGE_HH_
#define _VECTOR_STORAGE_HH_

namespace byte_buffer
{
    template<size_t S>
    class VectorStorage
    {
    public:
        VectorStorage(): m_storage(S,'\0'){}
        size_t size() {return m_storage.size();}
        size_t resize(size_t new_size) {return m_storage.resize(new_size);}
        void*  memory() {return &m_storage[0];}

    private:       
        std::vector<char> m_storage;
    };
}

#endif /* _VECTOR_STORAGE_HH_ */
