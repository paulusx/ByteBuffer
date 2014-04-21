#ifndef _ACCUMULATOR_H_
#define _ACCUMULATOR_H_

#include <cstddef>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/bind.hpp>

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
        
        
        void dump(void* mem) const
            {                
#if __cplusplus <= 199711L
                namespace bl = boost::lambda;                
                char* cmem = static_cast<char*>(mem);
                foreach((bl::bind( memcpy, bl::var(cmem),
                                   bl::bind(&Item::offset, bl::_1), bl::bind(&Item::size, bl::_1)),
                         bl::var(cmem) += bl::bind(&Item::size, bl::_1)) );
#else
                #error Hello
                foreach( [&mem](Item const& e)
                         {memcpy (mem, e.offset, e.size);
                             mem = (static_cast<char*>(mem) + e.size);}  ) ;
#endif
            }

        
    private:
        typedef boost::function<void (Item&)> ItemVisiter;       
        typedef boost::function<void (Item const&)> ConstItemVisiter;
        
        boost::scoped_ptr<Item> m_chain_head;      
        
        void foreach(ConstItemVisiter v) const
            {
                if(this->m_chain_head)
                {
                    Item* prev = m_chain_head.get();
                    do
                    {                        
                        v(boost::ref(*prev));
                    }while( (prev = prev->next.get()) );
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


#endif /* _ACCUMULATOR_H_ */
