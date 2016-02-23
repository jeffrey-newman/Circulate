cmake_minimum_required(VERSION 2.8.12)

PROJECT(CirculateCommon)

cmake_policy(SET CMP0042 NEW)

include("${CMAKE_BINARY_DIR}/../cmake_defs.txt")

FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

SET	(CirculateCommon_HDRS
#		Common.hpp
#		Debug.hpp
		Constants.hpp
		Record.hpp
		Recorder.hpp
		Time.hpp
		Component.hpp
		Link.hpp
		Node.hpp
		Portal.hpp
        Error.hpp
	)
		

SET (CirculateCommon_SRCS
		Recorder.cpp
        Record.cpp
		Time.cpp
		Portal.cpp
    )
    
ADD_LIBRARY(CirculateCommon SHARED ${CirculateCommon_HDRS} ${CirculateCommon_SRCS})

                     
# ADD_SUBDIRECTORY(test)