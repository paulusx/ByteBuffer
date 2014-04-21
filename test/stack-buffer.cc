#include<byte-buffer.hh>
#include<stack-allocator.hh>
#include<vector-storage.hh>
#include<simple-storage.hh>


#include<vector>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif //__GNUC__

#include <boost/test/unit_test.hpp>

#ifdef __GNUC__
#pragma GCC diagnostic warning "-Wunused-local-typedefs"
#endif //__GNUC__


#define BOOST_TEST_MODULE StackBuffer

namespace bb = byte_buffer;

struct sx
{
    unsigned int a;
    unsigned int b;
    char c[12];
};



BOOST_AUTO_TEST_CASE( Base )
{                                               
    const size_t capacity = 126;
    bb::ByteBuffer<capacity, bb::VectorStorage, bb::StackAllocator> bytes;

    
    // Test data set 1
    int a = 6;
    unsigned long long b = 33322;
    sx s = {0xffffffff,0x00,{1,2,3,4,5,6,7,8,9,10,11,12}};
    bb::Accumulator acc;
    acc.push(s).push(b).push(a);

    const size_t sizeSet1 = (sizeof(a) + sizeof(b) + sizeof(s));
    bytes.push(acc);

    // Test data set 2
    const char* cstr1 = "HelloWorld!!!";
    const size_t sizeSet2 = sizeof("HelloWorld!!!");
    bytes.push(cstr1, sizeSet2);

    // Test data set 3
    const char* cstr2 = "***DEADBEEF***";
    const size_t sizeSet3 = sizeof("***DEADBEEF***");
    bytes.push(cstr2, sizeSet3);

    // Test data set 4 (based 1)
    a = 89;
    b = 11;
    const size_t sizeSet4 = (sizeof(a) + sizeof(b) + sizeof(s));
    bytes.push(acc);


    

    BOOST_REQUIRE(bytes.freeSpace() + sizeSet1 + sizeSet2 + sizeSet3 + sizeSet4 + sizeof(size_t)*4 == capacity);

    //checker set 4
    BOOST_REQUIRE( (static_cast<sx*>(bytes.getData()))->a == s.a );
    BOOST_REQUIRE( (static_cast<sx*>(bytes.getData()))->b == s.b );
    BOOST_REQUIRE( *(reinterpret_cast<unsigned long long*>(static_cast<char*>(bytes.getData()) + sizeof(sx))) == 11 );
    BOOST_REQUIRE( *(reinterpret_cast<int*>(static_cast<char*>(bytes.getData()) + sizeof(sx) + sizeof(unsigned long long) )) == 89 );       
    bytes.free();

    //checker set 3
    BOOST_REQUIRE( std::string(static_cast<const char*>(bytes.getData())) == std::string(cstr2) );
    bytes.free();
    
    //checker set 2
    BOOST_REQUIRE( std::string(static_cast<const char*>(bytes.getData())) == std::string(cstr1) );
    bytes.free();
    
    //checker set 1
    BOOST_REQUIRE( (static_cast<sx*>(bytes.getData()))->a == s.a );
    BOOST_REQUIRE( (static_cast<sx*>(bytes.getData()))->b == s.b );
    BOOST_REQUIRE( *(reinterpret_cast<unsigned long long*>(static_cast<char*>(bytes.getData()) + sizeof(sx))) == 33322 );
    BOOST_REQUIRE( *(reinterpret_cast<int*>(static_cast<char*>(bytes.getData()) + sizeof(sx) + sizeof(unsigned long long) )) == 6 );       
    bytes.free();

    BOOST_REQUIRE(bytes.empty());

    bytes.push(cstr1, sizeSet2);
    bytes.push(cstr2, sizeSet3);

    BOOST_REQUIRE(bytes.empty() == false);

    //checker set 3
    BOOST_REQUIRE( std::string(static_cast<const char*>(bytes.getData())) == std::string(cstr2) );
    bytes.free();

    //checker set 2
    BOOST_REQUIRE( std::string(static_cast<const char*>(bytes.getData())) == std::string(cstr1) );
    bytes.free();

    BOOST_REQUIRE(bytes.empty());

    
}


















