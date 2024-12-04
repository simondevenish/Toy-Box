# Define the test executable
add_executable(ToyBoxTests
    test_dynamicarray.cpp
    test_hashmap.cpp
    test_dynamicstring.cpp
)

# Include directories for engine and external dependencies
target_include_directories(ToyBoxTests PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/utils/data_structures
    ${CMAKE_SOURCE_DIR}/external
)

# Link Google Test and the engine library
target_link_libraries(ToyBoxTests PRIVATE gtest gtest_main ToyBoxEngine)

# Add the tests to CTest
add_test(NAME ToyBoxTests COMMAND ToyBoxTests)
