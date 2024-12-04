add_library(ScriptingModule scripting_integration.cpp)

# Link EmberScript
target_link_libraries(ScriptingModule PUBLIC EmberScriptLib)