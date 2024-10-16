function(make_tester)
    set(FN_OPTIONS "")
    set(SINGLE_ARGS TITLE SRC INCLUDE_DIR)
    set(MULTI_ARGS LIBS)
    cmake_parse_arguments(ARG "" "${SINGLE_ARGS}" "${MULTI_ARGS}" "${ARGN}")

    message(NOTICE "ARG_TITLE=${ARG_TITLE}, ARG_SRC=${ARG_SRC}, ARG_INCLUDE_DIR=${ARG_INCLUDE_DIR}, ARG_LIBS=${ARG_LIBS}")

    add_executable("${ARG_TITLE}")
    target_include_directories("${ARG_TITLE}" PUBLIC "${ARG_INCLUDE_DIR}")
    target_sources("${ARG_TITLE}" PRIVATE "${ARG_SRC}")

    foreach(LIB_ITEM "${ARG_LIBS}")
        target_link_libraries("${ARG_TITLE}" PRIVATE "${LIB_ITEM}")
    endforeach()

    add_test(NAME "${ARG_TITLE}" COMMAND "$<TARGET_FILE:${ARG_TITLE}>")
endfunction()

make_tester(TITLE TestLexer SRC TestLexer.cpp INCLUDE_DIR "${MY_INCLUDES}" LIBS Frontend)
make_tester(TITLE TestParser SRC TestParser.cpp INCLUDE_DIR "${MY_INCLUDES}" LIBS Frontend Syntax)
make_tester(TITLE TestEmitter SRC TestEmitter.cpp INCLUDE_DIR "${MY_INCLUDES}" LIBS Frontend Syntax Backend Models)
