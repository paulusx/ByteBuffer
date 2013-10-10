#ifndef _BYTE_BUFFER_H_
#define _BYTE_BUFFER_H_

#include <cstddef>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <cstring>

namespace{
    void test(const void* p1, const void* p2, size_t cnt){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
}

namespace byte_buffer
{
    class Accumulator
    {
        struct Item
        {
            Item(const void* o, size_t s): offset(o), size(s) {}
            const void* offset;
            const size_t size;
            boost::scoped_ptr<Item> next;
        };

    public:
        
        template<typename T> Accumulator& push(T const& t)
            {                
                this->insert( new Item(&t, sizeof(T)) );
                return *this;
            }
        
        template<size_t A, class T[A]> Accumulator&  push(T t[])
            {                
                this->insert( new Item(t, sizeof(T[A])) );
                return *this;
            }
            
        Accumulator& push(void* t, size_t s)
            {
                insert( new Item(t, s) );
                return *this;
            }

        size_t size()
            {
                namespace bl = boost::lambda;              
                size_t result = 0;
                foreach( result += bl::bind(&Item::size,  bl::_1) );
                return result;               
            }

        void fillMemory(void* mem)
            {
                namespace bl = boost::lambda;
                memcpy(0, 0, 10);
                foreach(bl::bind(
                            test,
                            bl::bind(&Item::offset, _1),
                            bl::bind(&Item::offset, _1),
                            bl::bind(&Item::size, _1)
                            )
                    );
                
                // foreach( [&mem](Item const& e)
                //          {memcpy (mem, e.offset, e.size);
                //              std::cout << e.offset << ": " << e.size << " " << mem << std::endl;
                //              mem = (static_cast<char*>(mem) + e.size);}  ) ;
            }
        
        
    private:
        typedef boost::function<void (Item const&)> ItemVisiter;       
        
        boost::scoped_ptr<Item> m_chain_head;
        size_t m_size_data;
        
        
        void foreach(ItemVisiter v)
            {
                if(this->m_chain_head)
                {
                    Item* prev = m_chain_head.get();
                    do
                    {
                        Item itemt(NULL,0);
                        v(boost::ref(*prev));
                    }while(prev = prev->next.get());
                }

            }
        
        void insert(Item* item)
            {                
                if(this->m_chain_head)
                {
                    Item* prev = m_chain_head.get();
                    while(prev->next) prev = prev->next.get();
                    prev->next.reset(item);
                }
                else
                {
                    this->m_chain_head.reset(item);
                }
            }
        
        
    };

}

#endif /* _BYTE_BUFFER_H_ */

