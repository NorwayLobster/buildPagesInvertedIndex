cmake_minimum_required(VERSION 3.5)
project(pugixml)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

# # try conditional compilation
# include(CheckCXXCompilerFlag)
# CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
# CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
# CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# # check results and add flag
# if(COMPILER_SUPPORTS_CXX17)#
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# elseif(COMPILER_SUPPORTS_CXX11)#
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# elseif(COMPILER_SUPPORTS_CXX0X)#
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
# else()
#     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
# endif()

add_library(${PROJECT_NAME} 
    SHARED 
        pugixml.cpp
)
add_library(sub::pugixml ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME}
  PUBLIC 
    ${CMAKE_SOURCE_DIR}/include #   CMAKE_SOURCE_DIR v.s.  PROJECT_SOURCE_DIR 的 区别
    # ${PROJECT_SOURCE_DIR}/include
    # ${Boost_INCLUDE_DIRS}
)

if( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
  message(STATUS "Setting default CMAKE_INSTALL_PREFIX path to ${CMAKE_BINARY_DIR}/install")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "The path to use for make install" FORCE)
endif()

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib) 
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION include) 