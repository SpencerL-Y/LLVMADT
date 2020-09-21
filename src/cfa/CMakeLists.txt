MESSAGE(STATUS "CFA This is SOURCE dir " ${PROJECT_SOURCE_DIR})


ADD_LIBRARY(cfa Guard.cpp CFAInstruction.cpp CFAState.cpp CFAEdge.cpp CFA.cpp)