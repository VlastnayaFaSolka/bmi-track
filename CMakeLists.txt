cmake_minimum_required(VERSION 4.4.3)

set(PROJECT_NAME bmi-track)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)