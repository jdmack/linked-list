
add_executable(problem main.cpp LinkedList.h LinkedList.cpp)
target_include_directories(problem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(problem PRIVATE project_options)