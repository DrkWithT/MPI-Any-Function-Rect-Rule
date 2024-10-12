add_library(Syntax "")

target_include_directories(Syntax PUBLIC "${MY_INCLUDES}")
target_sources(Syntax PRIVATE AstNodes.cpp)
