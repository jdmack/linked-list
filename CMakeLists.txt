cmake_minimum_required(VERSION 3.10)

project(LinkedList CXX)

## Set C++ standard/compile-time options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

set(CMAKE_BUILD_TYPE Debug)

## Add the src to the build
add_subdirectory(src)

## Enable/Disable Testing
option(ENABLE_TEST "Turn on to enable tests" ON)

if (ENABLE_TEST)                           
   enable_testing() 
                                                                           
#    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/import/downloads/catch2/catch.hpp)          
                 
#       file(DOWNLOAD https://raw.githubusercontent.com/catchorg /Catch2 /master/single_include/catch2/catch.hpp                          ${CMAKE_CURRENT_SOURCE_DIR}/import/catch2/catch.hpp)

#       set(CATCH2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/import/downloads)                           

#    endif()

   # add_library(Catch INTERFACE)
   # target_include_directories(Catch INTERFACE ${CATCH2_INCLUDE_DIR})
   add_subdirectory(test)                       

endif()