# Add subdirectory for data structures
add_subdirectory(data_structures)

# Create a library target for utils
add_library(Utils INTERFACE)

# Link the data structures library
target_link_libraries(Utils INTERFACE DataStructures)
