MESSAGE(STATUS "execution-tree This is SOURCE dir " ${PROJECT_SOURCE_DIR})


ADD_LIBRARY(execution_tree ExecState.cpp ExecutionTree.cpp ../../include/execution-tree/ExecutionTree.h ExecutionNode.cpp ../../include/execution-tree/ExecutionNode.h InstructionParser.cpp ../../include/execution-tree/InstructionParser.h AbstractSymbolicTable.cpp AbstractSymbolicTable.h TableBuilder.cpp TableBuilder.h ErrorManager.cpp ErrorManager.h)