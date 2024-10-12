add_library(Models "")
target_include_directories(Models PUBLIC "${MY_INCLUDES}")
target_sources(Models PRIVATE XFunction.cpp)
