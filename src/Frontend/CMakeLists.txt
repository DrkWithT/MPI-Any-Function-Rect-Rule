add_library(Frontend "")
target_include_directories(Frontend PUBLIC "${MY_INCLUDES}")
target_sources(Frontend PRIVATE Token.cpp PRIVATE Lexer.cpp PRIVATE Parser.cpp)
