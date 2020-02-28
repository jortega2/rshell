CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set (CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
ADD_SUBDIRECTORY(googletest)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS regex)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(rshell 
	src/main.cpp 
	src/Tokenizer.cpp 
	src/cmdToken.cpp
	src/Executor.cpp
	src/andToken.cpp
	src/orToken.cpp
	src/semiToken.cpp
	src/testToken.cpp)
	target_link_libraries(rshell ${Boost_LIBRARIES})
	add_executable(test 
	unit_tests/unit_tests.cpp
	integration_tests/single_command_tests.cpp



	src/Tokenizer.cpp
	src/cmdToken.cpp
	src/Executor.cpp
	src/andToken.cpp
	src/orToken.cpp
	src/semiToken.cpp
	src/testToken.cpp)
	target_link_libraries(test ${Boost_LIBRARIES})
endif()

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
