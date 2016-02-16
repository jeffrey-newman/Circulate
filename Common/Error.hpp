//
//  Error.hpp
//  CirculateCommon
//
//  Created by a1091793 on 16/02/2016.
//
//

#ifndef Error_hpp
#define Error_hpp

#include <stdio.h>
#include <string>
#include <exception>



class UndefinedCodeException: public std::exception
{
public:
    /** Constructor (C strings).
     *  @param message C-style string error message.
     *                 The string contents are copied upon construction.
     *                 Hence, responsibility for deleting the \c char* lies
     *                 with the caller.
     */
    explicit UndefinedCodeException(const char* message):
    msg_(message)
    {
    }
    
    /** Constructor (C++ STL strings).
     *  @param message The error message.
     */
    explicit UndefinedCodeException(const std::string & message):
    msg_(message)
    {}
    
    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~UndefinedCodeException() throw (){}
    
    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a \c const \c char*. The underlying memory
     *          is in posession of the \c Exception object. Callers \a must
     *          not attempt to free the memory.
     */
    virtual const char* what() const throw (){
        return msg_.c_str();
    }
    
protected:
    /** Error message.
     */
    std::string msg_;
};


#endif //Error_hpp