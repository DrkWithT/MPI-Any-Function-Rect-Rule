add_library(MpiWraps "")

target_include_directories(MpiWraps PUBLIC "${MY_INCLUDES}")
target_sources(MpiWraps PRIVATE Wrappers.cpp)
