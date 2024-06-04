# Add executables for the tests
add_executable(testgen testgen.cpp)
add_executable(testscript testscript.cpp)

# Link the library with the test executables
target_link_libraries(testgen libeed)
target_link_libraries(testscript libeed)