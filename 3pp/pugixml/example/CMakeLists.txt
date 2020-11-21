cmake_minimum_required(VERSION 3.6)
# project(pugixml)
# project(pugixml_example_bin)


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

find_package(Boost 1.46.1 REQUIRED COMPONENTS regex system filesystem)

# check if boost was found
if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()


add_executable(example_bin main.cc)
target_link_libraries( example_bin
  PUBLIC
  # PRIVATE
    sub::pugixml
    # ${Boost_REGEX_LIBRARY}
)
target_link_libraries(example_bin
  PRIVATE
  # ${Boost_LIBRARIES}// link all library
  ${Boost_REGEX_LIBRARY}
  # ${Boost_SYSTEM_LIBRARY}// link specific library
  # ${Boost_FILESYSTEM_LIBRARY}
    # Boost::regex
    # Boost::system
    # Boost::filesystem
)

target_include_directories(example_bin
  PUBLIC
    # ${CMAKE_SOURCE_DIR}/include 
    ${PROJECT_SOURCE_DIR}/include 
    ${Boost_INCLUDE_DIRS}
)
#note:
# 1. project()
# 2. set()
# set(HTTPS_INCLUDE ${PROJECT_SOURCE_DIR}/include)
# set(HTTPS_INCLUDE ${HTTPS_INCLUDE} PARENT_SCOPE)
# 3. message()
message("PROJECT_SOURCE_DIR:       ${PROJECT_SOURCE_DIR}") #print PROJECT_SOURCE_DIR 
message("CMAKE_SOURCE_DIR:         ${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

message("PROJECT_BINARY_DIR:       ${PROJECT_BINARY_DIR}")
message("CMAKE_BINARY_DIR:         ${CMAKE_BINARY_DIR}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

message("CMAKE_CURRENT_LIST_DIR:   ${CMAKE_CURRENT_LIST_DIR}")
message("CMAKE_CURRENT_LIST_FILE:  ${CMAKE_CURRENT_LIST_FILE}")
message("CMAKE_CURRENT_LIST_LINE:  ${CMAKE_CURRENT_LIST_LINE}")

message("CMAKE_MODULE_PATH:        ${CMAKE_MODULE_PATH}")
message("CMAKE_INCLUDE_PATH:       ${CMAKE_INCLUDE_PATH}")
message("CMAKE_LIBRARY_PATH:       ${CMAKE_LIBRARY_PATH}")
message("CMAKE_INCLUDE_CURRENT_DIR:${CMAKE_INCLUDE_CURRENT_DIR}")







if( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
  message(STATUS "Setting default CMAKE_INSTALL_PREFIX path to ${CMAKE_BINARY_DIR}/install")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "The path to use for make install" FORCE)
endif()

install(TARGETS example_bin DESTINATION bin) 
# how to install sub library, install(TARGETS ${} DESTINATION bin) 
# install(TARGETS sub::helloworld LIBRARY DESTINATION lib) 

# install(FILES ${CMAKE_SOURCE_DIR}/coolshell.xml DESTINATION etc)//error
install(FILES ${PROJECT_SOURCE_DIR}/coolshell.xml DESTINATION etc)