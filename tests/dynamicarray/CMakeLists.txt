# Define the test sources
set(DYNAMICARRAY_TEST_SOURCES
    test_dynamicarray.cpp
)

# Create the executable for the tests
add_executable(DynamicArrayTests ${DYNAMICARRAY_TEST_SOURCES})

# Include directories for the DynamicArray library
target_include_directories(DynamicArrayTests PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/utils/data_structures
)

# Link the necessary libraries
target_link_libraries(DynamicArrayTests PRIVATE
    gtest
    gtest_main
    ToyBoxEngine
)

# Add the test to CTest
add_test(NAME DynamicArrayTests COMMAND DynamicArrayTests)

# Ensure the test executable is built in the correct directory
set_target_properties(DynamicArrayTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/dynamicarray
)
