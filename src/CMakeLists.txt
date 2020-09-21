MESSAGE(STATUS "src This is SOURCE dir " ${PROJECT_SOURCE_DIR})

MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM-10 support core irreader)

ADD_SUBDIRECTORY(cfa)
ADD_SUBDIRECTORY(converter)
ADD_SUBDIRECTORY(automata)
ADD_EXECUTABLE(exec Main.cpp)

TARGET_LINK_LIBRARIES(exec cfa converter automata LLVM-10)
