set(MY_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/Include")

add_subdirectory(Models)
add_subdirectory(Frontend)
add_subdirectory(Syntax)
add_subdirectory(Backend)
add_subdirectory(MpiWraps)
add_subdirectory(Tests)

add_executable(MPIRectRule)
# todo: add PUBLIC "${MPI_INCLUDE_DIR}" to include dirs...
target_include_directories(MPIRectRule PUBLIC "${MY_INCLUDES}")
target_sources(MPIRectRule PRIVATE Main.cpp)
target_link_libraries(MPIRectRule PRIVATE Models PRIVATE Frontend PRIVATE Syntax PRIVATE Backend PRIVATE MpiWraps)
