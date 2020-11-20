cmake_minimum_required(VERSION 3.6)
project(buildPagesInvertedIndex)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

# try conditional compilation
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# check results and add flag
if(COMPILER_SUPPORTS_CXX17)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX11)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# find_package(Boost  1.66.0 REQUIRED COMPONENTS noncopyable)

# check if boost was found
# if(Boost_FOUND)
#     message ("boost found")
# else()
#     message (FATAL_ERROR "Cannot find Boost")
# endif()





add_executable(${PROJECT_NAME} 
    main.cc
    configure.cc
    PageLib.cc
    WebPage.cc
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    sub::cppjieba
    sub::simhash
    sub::pugixml
  # ${Boost_NONCOPYABLE_LIBRARY}// can not not find
  # ${Boost_LIBRARIES}// link all library
  # ${Boost_SYSTEM_LIBRARY}// link specific library
  # ${Boost_FILESYSTEM_LIBRARY}
    # Boost::regex
    # Boost::system
)

target_include_directories( ${PROJECT_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    # ${Boost_INCLUDE_DIRS}
)