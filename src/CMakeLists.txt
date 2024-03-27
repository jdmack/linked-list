
add_executable(runner main.cpp LinkedList.h LinkedList.cpp)
set_target_properties(runner PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}
)
target_include_directories(runner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(runner PRIVATE project_options)