cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS)

project(GLECS)

add_library(${PROJECT_NAME} STATIC)

add_subdirectory(src)
add_subdirectory(libs)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} IMGUI GLAD glm::glm)

add_executable(${PROJECT_NAME}-Tests main.cpp)
target_link_libraries(${PROJECT_NAME}-Tests ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E create_symlink
${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)