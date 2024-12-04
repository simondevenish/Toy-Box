add_library(PhysicsModule physics_integration.cpp)

# Link Phyzzy
target_link_libraries(PhysicsModule PUBLIC Phyzzy)