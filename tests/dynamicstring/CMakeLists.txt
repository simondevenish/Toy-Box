# Define the test sources
set(DYNAMICSTRING_TEST_SOURCES
    test_dynamicstring.cpp
)

# Create the executable for the tests
add_executable(DynamicStringTests ${DYNAMICSTRING_TEST_SOURCES})

# Include directories for the DynamicString library
target_include_directories(DynamicStringTests PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/utils/data_structures
)

# Link the necessary libraries
target_link_libraries(DynamicStringTests PRIVATE
    gtest
    gtest_main
    ToyBoxEngine
)

# Add the test to CTest
add_test(NAME DynamicStringTests COMMAND DynamicStringTests)

# Ensure the test executable is built in the correct directory
set_target_properties(DynamicStringTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/dynamicstring
)
