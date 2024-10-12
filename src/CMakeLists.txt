# find_package(MPI REQUIRED)
set(MY_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/Include")
# set(MPI_INCLUDE_DIR "${MPI_INCLUDE_PATH}")

add_subdirectory(Frontend)
add_subdirectory(Syntax)
# add_subdirectory(Models)
add_subdirectory(Tests)

add_executable(MPIRectRule)
# todo: add PUBLIC "${MPI_INCLUDE_DIR}" to include dirs...
target_include_directories(MPIRectRule PUBLIC "${MY_INCLUDES}")
target_sources(MPIRectRule PRIVATE Main.cpp)
# todo: link libraries Syntax & Models when they're done!
target_link_libraries(MPIRectRule PRIVATE Frontend)
