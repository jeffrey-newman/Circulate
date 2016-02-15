//
//  Debug.cpp
//  CirculateCommon
//
//  Created by a1091793 on 31/12/2015.
//
//

#include "Debug.hpp"


/*
 * File:   debug_stream.h
 * Author: jnewman
 *
 * Created on February 4, 2010, 1:57 PM
 */

/**
 * @file debug_stream.h
 * @brief This file contains classes/functions useful for debugging.
 *
 * The code was modified from that on http://stackoverflow.com/questions/1389538/cancelling-stdcout-code-lines-using-preprocessor
 */

#ifndef _DEBUG_STREAM_H
#define	_DEBUG_STREAM_H

#include <ostream>
#include <iostream>

/**
 * The first debug stream class
 */
struct debug_stream_1
{
public:
    
    /**
     * @brief the constructor. Tells what stream to use
     */
    debug_stream_1(std::ostream & _stream) : stream(_stream)
    {
    };
    std::ostream & stream;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams
 *
 *   The optimiser whouls see that the operator << function does nothing when DEBUG is not
 *   defined, and so optimise the call.
 */
template< typename T > inline debug_stream_1 &
operator <<(debug_stream_1 & d, const T & t)
{
#ifdef DEBUG
    d.stream << t;
#endif // DEBUG
    return d;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams.
 *
 *  This function is needed for std::endl and the like.
 */
inline debug_stream_1 &
operator<<(debug_stream_1 & d, std::ostream& (*__pf)(std::ostream&))
{
#ifdef DEBUG
    (*__pf)(d.stream);
#endif // DEBUG
    return d;
    
}


/**
 * So we can have multiple debug streams, with different levels of debugging,
 * we define another class, identicle except for the precompilor macro definition
 * used
 */
struct debug_stream_2
{
public:
    
    debug_stream_2(std::ostream & _stream) : stream(_stream)
    {
    };
    std::ostream & stream;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams
 *
 *   The optimiser whouls see that the operator << function does nothing when DEBUG is not
 *   defined, and so optimise the call.
 */
template< typename T > inline debug_stream_2 &
operator <<(debug_stream_2 & d, const T & t)
{
#ifdef DEBUG2
    d.stream << t;
#endif // DEBUG
    return d;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams.
 *
 *  This function is needed for std::endl and the like.
 */
inline debug_stream_2 &
operator<<(debug_stream_2 & d, std::ostream& (*__pf)(std::ostream&))
{
#ifdef DEBUG2
    (*__pf)(d.stream);
#endif // DEBUG
    return d;
    
}

/**
 * So we can have multiple debug streams, with different levels of debugging,
 * we define another class, identicle except for the precompilor macro definition
 * used
 */
struct debug_stream_3
{
public:
    
    debug_stream_3(std::ostream & _stream) : stream(_stream)
    {
    };
    std::ostream & stream;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams
 *
 *   The optimiser whouls see that the operator << function does nothing when DEBUG is not
 *   defined, and so optimise the call.
 */
template< typename T > inline debug_stream_3 &
operator <<(debug_stream_3 & d, const T & t)
{
#ifdef DEBUG3
    d.stream << t;
#endif // DEBUG3
    return d;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams.
 *
 *  This function is needed for std::endl and the like.
 */
inline debug_stream_3 &
operator<<(debug_stream_3 & d, std::ostream& (*__pf)(std::ostream&))
{
#ifdef DEBUG3
    (*__pf)(d.stream);
#endif // DEBUG3
    return d;
    
}

/**
 * So we can have multiple debug streams, with different levels of debugging,
 * we define another class, identicle except for the precompilor macro definition
 * used
 */
struct debug_stream_4
{
public:
    
    debug_stream_4(std::ostream & _stream) : stream(_stream)
    {
    };
    std::ostream & stream;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams
 *
 *   The optimiser whouls see that the operator << function does nothing when DEBUG is not
 *   defined, and so optimise the call.
 */
template< typename T > inline debug_stream_4 &
operator <<(debug_stream_4 & d, const T & t)
{
#ifdef DEBUG4
    d.stream << t;
#endif // DEBUG4
    return d;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams.
 *
 *  This function is needed for std::endl and the like.
 */
inline debug_stream_4 &
operator<<(debug_stream_4 & d, std::ostream& (*__pf)(std::ostream&))
{
#ifdef DEBUG4
    (*__pf)(d.stream);
#endif // DEBUG4
    return d;
    
}

/**
 * So we can have multiple debug streams, with different levels of debugging,
 * we define another class, identicle except for the precompilor macro definition
 * used
 */
struct debug_stream_5
{
public:
    
    debug_stream_5(std::ostream & _stream) : stream(_stream)
    {
    };
    std::ostream & stream;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams
 *
 *   The optimiser whouls see that the operator << function does nothing when DEBUG is not
 *   defined, and so optimise the call.
 */
template< typename T > inline debug_stream_5 &
operator <<(debug_stream_5 & d, const T & t)
{
#ifdef DEBUG5
    d.stream << t;
#endif // DEBUG5
    return d;
};

/**
 * @brief overloaded << operator, so the debug stream operates like iostreams.
 *
 *  This function is needed for std::endl and the like.
 */
inline debug_stream_5 &
operator<<(debug_stream_5 & d, std::ostream& (*__pf)(std::ostream&))
{
#ifdef DEBUG5
    (*__pf)(d.stream);
#endif // DEBUG5
    return d;
    
}

namespace {
    debug_stream_1 debug = debug_stream_1(std::clog); /**< Instance of debug stream 1 */
    debug_stream_2 debug2 = debug_stream_2(std::clog); /**< Instance of debug stream 2 */
    debug_stream_3 debug3 = debug_stream_3(std::clog); /**< Instance of debug stream 3 */
    debug_stream_4 debug4 = debug_stream_4(std::clog); /**< Instance of debug stream 4 */
    debug_stream_5 debug5 = debug_stream_5(std::clog); /**< Instance of debug stream 5 */
}

//extern static debug_stream_2 debug2 = debug_stream_2(std::clog); /**< Instance of debug stream 2 */


#endif	/* _DEBUG_STREAM_H */

