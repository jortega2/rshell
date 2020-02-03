CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_EXECUTABLE(commands_exec
	prototype/commands.cpp
)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS regex)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(rshell src/main.cpp)
	target_link_libraries(rshell ${Boost_LIBRARIES})
endif()
