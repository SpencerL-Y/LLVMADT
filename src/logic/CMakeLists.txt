MESSAGE(STATUS "converter This is SOURCE dir " ${PROJECT_SOURCE_DIR})


SET(logic_util_dir
    ./util/TLUtil.cpp
)

ADD_LIBRARY(logic_lib ${logic_util_dir})