MESSAGE(STATUS "converter This is SOURCE dir " ${PROJECT_SOURCE_DIR})


SET(cfa_dir
    ../cfa/CFA.cpp
    ../cfa/CFAEdge.cpp
    ../cfa/CFAInstruction.cpp
    ../cfa/CFAState.cpp
    ../cfa/Guard.cpp
    ../cfa/Z3Test.cpp
)

ADD_LIBRARY(converter Converter.cpp myTranslate.cpp ${cfa_dir})