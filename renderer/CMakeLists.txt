include_directories(${CMAKE_SOURCE_DIR}/src)

set(RENDERER_SUBDIRS
    math
    geometry
    light
    shader
    camera
        CACHE INTERNAL "")

add_library(renderer)

foreach(subdir ${RENDERER_SUBDIRS})
    add_subdirectory(${subdir})
    include_directories(${subdir})
endforeach(subdir)

target_sources(renderer
    PRIVATE
        renderer.cpp renderer.hpp
        Framebuffer.cpp Framebuffer.hpp
        SceneContainer.cpp SceneContainer.hpp)

target_link_libraries(renderer sive-util)