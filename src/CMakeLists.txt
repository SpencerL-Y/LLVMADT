MESSAGE(STATUS "src This is SOURCE dir " ${PROJECT_SOURCE_DIR})

MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

MESSAGE(STATUS "Z3_FOUND: ${Z3_FOUND}" )
MESSAGE(STATUS "Found Z3: ${Z3_VERSION_STRING}")
MESSAGE(STATUS "Z3_DIR: ${Z3_DIR}")
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM-10 support core irreader)


ADD_SUBDIRECTORY(automata)
ADD_SUBDIRECTORY(cfa)
ADD_SUBDIRECTORY(converter)
ADD_SUBDIRECTORY(logic)
ADD_SUBDIRECTORY(checker)
ADD_SUBDIRECTORY(execution-tree)


ADD_EXECUTABLE(exec Main.cpp)
ADD_EXECUTABLE(sym_exc sym_exc.cpp)

TARGET_INCLUDE_DIRECTORIES(exec PRIVATE ${Z3_CXX_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(sym_exc PRIVATE ${Z3_CXX_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(exec converter  checker automata_lib  cfa logic_lib  LLVM-10 ${Z3_LIBRARIES} "/usr/local/lib/libspot.so" yaml-cpp)
TARGET_LINK_LIBRARIES(sym_exc LLVM-10 ${Z3_LIBRARIES}  execution_tree)
