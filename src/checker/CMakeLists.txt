MESSAGE(STATUS "CFA This is SOURCE dir " ${PROJECT_SOURCE_DIR})

SET(parser_dir
    parser/SVCompParser.cpp

)

ADD_LIBRARY(checker CheckerSampleBased.cpp PathChecker.cpp ReachErrCheckerSampleBased.cpp ${parser_dir})