MESSAGE(STATUS "converter This is SOURCE dir " ${PROJECT_SOURCE_DIR})


SET(cfa_dir
    ../cfa/CFA.cpp
    ../cfa/CFAEdge.cpp
    ../cfa/CFAInstruction.cpp
    ../cfa/CFAState.cpp
    ../cfa/Guard.cpp
)

ADD_LIBRARY(converter Converter.cpp ${cfa_dir})