cmake_minimum_required(VERSION 3.15.7)

# Project Name
project(cliApp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(SOURCES main.cpp dependencies/argh/argh.h dependencies/curlpp/build/)
# Add SubDirecotry TO build
add_subdirectory(dependencies/curlpp)

#Inlclude Directory for the libraries
include_directories(dependencies/curlpp/include)
add_executable(cliApp main.cpp)

# Link curlpp with cliApp
target_link_libraries(cliApp curlpp)
