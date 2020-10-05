MESSAGE(STATUS "converter This is SOURCE dir " ${PROJECT_SOURCE_DIR})


SET(dfa_dir
    ../automata/dfa/DFA.cpp
    ../automata/dfa/DFAState.cpp
    ../automata/dfa/DFATrans.cpp
)
SET(alphabet_dir
    ../automata/alphabet/Alphabet.cpp
    ../automata/alphabet/Letter.cpp
    ../automata/alphabet/LetterType.cpp
    ../automata/alphabet/LetterTypeInt.cpp
    ../automata/alphabet/LetterTypeZ3Expr.cpp
)
SET(abstract_dir
    ../automata/abstract/Automaton.cpp
    ../automata/abstract/Path.cpp
    ../automata/abstract/State.cpp
    ../automata/abstract/Transition.cpp
    ../automata/abstract/Word.cpp
)

SET(buchi_dir
    ../automata/buchi/BA.cpp)

SET(util_dir
    ../automata/util/PathSampler.cpp)


ADD_LIBRARY(converter Converter.cpp myTranslate.cpp)
TARGET_LINK_LIBRARIES(converter automata_lib cfa)