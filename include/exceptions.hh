#include <stdexcept>

#ifndef _EXCEPTIONS_HH_
#define _EXCEPTIONS_HH_

namespace byte_buffer
{
    class BadAlloc: public std::runtime_error
    {
    public:
        BadAlloc() throw() : runtime_error("Error while alloc") {}
        virtual ~BadAlloc() throw() {}
    };


    class ContainerIsEmpty: public std::runtime_error
    {
    public:
        ContainerIsEmpty() throw() : runtime_error("Container is empty") {}
        virtual ~ContainerIsEmpty() throw() {}
    };



}

#endif /* _EXCEPTIONS_HH_ */
