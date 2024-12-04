# Define the test sources
set(HASHMAP_TEST_SOURCES
    test_hashmap.cpp
)

# Create the executable for the tests
add_executable(HashMapTests ${HASHMAP_TEST_SOURCES})

# Include directories for the HashMap library
target_include_directories(HashMapTests PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/utils/data_structures
)

# Link the necessary libraries
target_link_libraries(HashMapTests PRIVATE
    gtest
    gtest_main
    ToyBoxEngine
)

# Add the test to CTest
add_test(NAME HashMapTests COMMAND HashMapTests)

# Ensure the test executable is built in the correct directory
set_target_properties(HashMapTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/hashmap
)
