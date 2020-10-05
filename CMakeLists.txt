cmake_minimum_required(VERSION 3.13.4)

project(LLVMADT)

find_package(LLVM REQUIRED CONFIG)
find_package(Z3 REQUIRED CONFIG)


include_directories(
    ${LLVM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include_directories
    ${PROJECT_SOURCE_DIR}/include/converter
    ${PROJECT_SOURCE_DIR}/include/cfa
    ${PROJECT_SOURCE_DIR}/include/dfa
    ${PROJECT_SOURCE_DIR}/include/abstract
    /usr/local/include
    /usr/include
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
ADD_SUBDIRECTORY(src)