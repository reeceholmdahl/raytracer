
set(RENDERER_SUBDIRS
    math
    light
    shader
    geometry
    camera
        CACHE INTERNAL "")

add_library(renderer)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/renderer)

target_sources(renderer
    PRIVATE
        Framebuffer.cpp Framebuffer.hpp
        BVH.cpp BVH.hpp
        renderer.cpp
        Scene.cpp Scene.hpp
        jsonSceneParser.cpp)

foreach(subdir ${RENDERER_SUBDIRS})
    include_directories(${subdir})
    add_subdirectory(${subdir})
endforeach(subdir)

target_link_libraries(renderer sive-util)
target_link_libraries(renderer ${PNG_LIBRARY})
target_link_libraries(renderer ${ZLIB_LIBRARY})

#target_compile_options(renderer PRIVATE "")