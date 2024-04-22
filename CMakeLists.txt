cmake_minimum_required(VERSION 3.10)
project(learning_opengl VERSION 0.1.0 LANGUAGES C CXX)

cmake_policy(SET CMP0072 NEW)

# find_package(OpengGL REQUIRED)

add_executable(learning_opengl 
    src/glad/glad.h
    src/glad/glad.c 
    src/main.cpp 
)

target_link_libraries(learning_opengl 
    glfw
    # OpengGL::GL
)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
