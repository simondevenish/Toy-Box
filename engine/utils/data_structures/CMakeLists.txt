# Collect all header files
set(DATA_STRUCTURES_HEADERS
    dynamicarray.h
    dynamicarray.inl
    dynamicstring.h
    hashmap.h
    hashmap.inl
)

# Collect all source files
set(DATA_STRUCTURES_SOURCES
    dynamicstring.cpp
)

# Create a STATIC library for the data structures
add_library(DataStructures STATIC ${DATA_STRUCTURES_SOURCES})

# Add include directories for the headers
target_include_directories(DataStructures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
