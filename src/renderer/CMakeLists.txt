include_directories(${CMAKE_SOURCE_DIR}/src)

list(APPEND RENDERER_SUBDIRS
    math
    geometry
    light
    shader
    camera)

set(RENDERER_SUBDIRS "${RENDERER_SUBDIRS}" CACHE INTERNAL "")

add_library(renderer)

foreach(subdir ${RENDERER_SUBDIRS})
    add_subdirectory(${subdir})
    include_directories(${subdir})
endforeach(subdir)

target_sources(renderer
    PRIVATE
        Framebuffer.cpp Framebuffer.hpp
        SceneContainer.cpp SceneContainer.hpp)

target_link_libraries(renderer sive-util)