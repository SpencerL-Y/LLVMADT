MESSAGE(STATUS "CFA This is SOURCE dir " ${PROJECT_SOURCE_DIR})


ADD_LIBRARY(cfa CFA.cpp CFAState.cpp CFAEdge.cpp  Guard.cpp)