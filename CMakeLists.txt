cmake_path(APPEND RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ".." ".." "resources")
cmake_path(ABSOLUTE_PATH RESOURCE_DIR NORMALIZE)

add_compile_definitions("RESOURCEPATH=string(\"${RESOURCE_DIR}/\")")
add_executable(pap-demo pap-demo.cpp)
target_link_libraries(pap-demo fsmtest)

add_test(NAME pap-demo COMMAND "pap-demo")
