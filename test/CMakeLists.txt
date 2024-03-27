add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC Catch)
target_link_libraries(catch_main PRIVATE project_options)

add_library(project_tests OBJECT ${CMAKE_SOURCE_DIR}/src/LinkedList.h ${CMAKE_SOURCE_DIR}/src/LinkedList.cpp )
target_include_directories(project_tests INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(project_tests PRIVATE project_options)

## Test Executable
add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE project_options catch_main)
target_link_libraries(tests PUBLIC project_tests)
add_test(NAME MyAwesomeTest COMMAND tests)
