

PROJECT	(CirculateCore)
cmake_minimum_required(VERSION 2.8.12)
cmake_policy(SET CMP0042 NEW)

include("${CMAKE_BINARY_DIR}/../cmake_defs.txt")

FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options system regex filesystem timer random)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

FIND_PACKAGE(GSL REQUIRED)
INCLUDE_DIRECTORIES(${GSL_INCLUDE_DIRS} ${GSLCBLAS_INCLUDE_DIRS})

FIND_PACKAGE(HDF5 COMPONENTS CXX HL)
INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIRS})

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtCore library
find_package(Qt5Core)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


SET (CirculateEngineSources
	Component.cpp
	GraphCalculationOrder.cpp
	CirculateSolver.cpp
#	Main.cpp
	CirculateGraph.cpp
)

SET (CirculateEngineHeaders
	Component.hpp
	DepthFirstSearchVisitor.hpp
	GraphCalculationOrder.hpp
	CirculateSolver.hpp
	Circulate.hpp
	Link.hpp
	Node.hpp
	Progress.hpp
	CirculateGraph.hpp
	TruncatedDepthFirstSearch.hpp
)

# Group source files for IDE source explorers (e.g. Visual Studio)
#source_group("Header Files" FILES ${CirculateEngineHeaders})
#source_group("Source Files" FILES ${CirculateEngineSources})
#source_group("CMake Files" FILES CMakeLists.txt)

ADD_LIBRARY(CirculateCore SHARED ${CirculateEngineSources} ${CirculateEngineHeaders})
TARGET_LINK_LIBRARIES(CirculateCore hdf5 hdf5_cpp hdf5_hl ${Boost_LIBRARIES} Qt5::Core)

#ADD_SUBDIRECTORY(tests)