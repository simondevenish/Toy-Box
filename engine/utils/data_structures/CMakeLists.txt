# Collect all header files
set(DATA_STRUCTURES_HEADERS
    dynamicarray.h
    dynamicarray.inl
    dynamicstring.h
    dynamicstring.inl
    hashmap.h
    hashmap.inl
)

# Create a library for the data structures
add_library(DataStructures INTERFACE)

# Add include directories for the headers
target_include_directories(DataStructures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
