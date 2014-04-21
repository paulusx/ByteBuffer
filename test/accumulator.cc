#include<accumulator.hh>
#include<vector>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif //__GNUC__

#include <boost/test/unit_test.hpp>

#ifdef __GNUC__
#pragma GCC diagnostic warning "-Wunused-local-typedefs"
#endif //__GNUC__


#define BOOST_TEST_MODULE Accumulator


struct sx
{
    unsigned int a;
    unsigned int b;
    char c[12];
};


BOOST_AUTO_TEST_CASE( CheckSize )
{                                               

    int a = 6;
    unsigned long long b = 33322;
    sx s = {0xffffffff,0x00,{1,2,3,4,5,6,7,8,9,10,11,12}};
  
   byte_buffer::Accumulator acc;
   std::vector<char> buffer;
  
   acc.push(s).push(b).push(a);        
   buffer.resize( acc.size() );
   acc.dump(&(buffer[0]));

   BOOST_REQUIRE(buffer.size() == sizeof(a) + sizeof(b) + sizeof(s));

}

