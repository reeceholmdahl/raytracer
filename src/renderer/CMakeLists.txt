add_library(renderer
    Framebuffer.cpp Framebuffer.h)

include_directories(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(renderer sive-util)