add_library(renderer
    Framebuffer.cpp Framebuffer.h
    Light.cpp Light.hpp
    Camera.cpp Camera.hpp
    Shape.cpp Shape.hpp
    Shader.cpp Shader.hpp)

include_directories(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(renderer sive-util)