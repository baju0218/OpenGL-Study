cmake_minimum_required(VERSION 3.28.1)

set(PROJECT_NAME opengl_study)
set(CMAKE_CXX_STANDARD 23)

set(WINDOW_NAME "Hello, OpenGL!")
set(WINDOW_WIDTH 640)
set(WINDOW_HEIGHT 480)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
    src/buffer.cpp src/buffer.h
    src/context.cpp src/context.h
    src/main.cpp
    src/program.cpp src/program.h
    src/shader.cpp src/shader.h
    src/util.cpp src/util.h
    src/vertex_layout.cpp src/vertex_layout.h
)

include(Dependency.cmake)

add_dependencies(${PROJECT_NAME} ${DEP_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
)