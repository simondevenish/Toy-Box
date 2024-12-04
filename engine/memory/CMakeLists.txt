add_library(MemoryModule memory_integration.cpp)

# Link Phyzzy
target_link_libraries(MemoryModule PUBLIC AllocX)
