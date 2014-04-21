#include<byte-buffer.hh>
#include<stack-allocator.hh>
#include<vector-storage.hh>

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
    const size_t capacity = 620;
    bb::ByteBuffer<capacity, bb::VectorStorage, bb::StackAllocator> bytes;

    // Test data set 1
    int a = 6;
    unsigned long long b = 33322;
    sx s = {0xffffffff,0x00,{1,2,3,4,5,6,7,8,9,10,11,12}};
    bb::Accumulator acc;
    acc.push(s).push(b).push(a);
    size_t sizeSet1 = (sizeof(a) + sizeof(b) + sizeof(s));
    bytes.push(acc);

    // Test data set 2
    const char* cstr1 = "HelloWorld!!!";
    size_t sizeSet2 = sizeof("HelloWorld!!!");
    bytes.push(cstr1, sizeSet2);

    // Test data set 3
    const char* cstr2 = "***DEADBEEF***";
    size_t sizeSet3 = sizeof("***DEADBEEF***");
    bytes.push(cstr2, sizeSet3);

    // Test data set 4 (based 1)
    a = 89;
    b = 11;
    size_t sizeSet4 = (sizeof(a) + sizeof(b) + sizeof(s));
    bytes.push(acc);


    BOOST_REQUIRE(bytes.freeSpace() + sizeSet1 + sizeSet2 + sizeSet3 + sizeSet4 + sizeof(size_t)*4 == capacity);

    //checker set 4
    BOOST_REQUIRE( (static_cast<sx*>(bytes.getData()))->a == s.a );
    BOOST_REQUIRE( (static_cast<sx*>(bytes.getData()))->b == s.b );

    bytes.free();


}


















