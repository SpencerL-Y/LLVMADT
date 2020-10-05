MESSAGE(STATUS "converter This is SOURCE dir " ${PROJECT_SOURCE_DIR})


SET(cfa_dir
    ../cfa/CFA.cpp
    ../cfa/CFAEdge.cpp
    ../cfa/CFAInstruction.cpp
    ../cfa/CFAState.cpp
    ../cfa/Guard.cpp
    ../cfa/Z3Test.cpp
)

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


ADD_LIBRARY(converter Converter.cpp myTranslate.cpp ${cfa_dir} ${abstract_dir}  ${dfa_dir} ${alphabet_dir} )