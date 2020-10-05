MESSAGE(STATUS "Automaton This is SOURCE dir " ${PROJECT_SOURCE_DIR})
SET(dfa_dir
    dfa/DFA.cpp
    dfa/DFAState.cpp
    dfa/DFATrans.cpp
)
SET(alphabet_dir
    alphabet/Alphabet.cpp
    alphabet/Letter.cpp
    alphabet/LetterType.cpp
    alphabet/LetterTypeInt.cpp
    alphabet/LetterTypeZ3Expr.cpp
)
SET(abstract_dir
    abstract/Automaton.cpp
    abstract/Path.cpp
    abstract/State.cpp
    abstract/Transition.cpp
    abstract/Word.cpp
)

SET(buchi_dir
    buchi/BA.cpp)

SET(util_dir
    util/PathSampler.cpp)

ADD_LIBRARY(automata_lib ${dfa_dir} ${alphabet_dir} ${abstract_dir} ${buchi_dir} ${util_dir})