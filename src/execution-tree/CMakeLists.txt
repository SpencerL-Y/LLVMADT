MESSAGE(STATUS "execution-tree This is SOURCE dir " ${PROJECT_SOURCE_DIR})


ADD_LIBRARY(execution_tree ExecState.cpp ExecutionTree.cpp ../../include/execution-tree/ExecutionTree.h ExecutionNode.cpp ../../include/execution-tree/ExecutionNode.h)