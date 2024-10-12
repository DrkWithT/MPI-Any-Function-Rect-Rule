add_executable(TestLexer)
target_include_directories(TestLexer PUBLIC "${MY_INCLUDES}")
target_sources(TestLexer PRIVATE TestLexer.cpp)
target_link_libraries(TestLexer PRIVATE Frontend)

add_test(NAME Lexer COMMAND "$<TARGET_FILE:TestLexer>")
