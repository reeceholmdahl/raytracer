include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/renderer)

foreach(subdir ${RENDERER_SUBDIRS})
    include_directories(${CMAKE_SOURCE_DIR}/renderer/${subdir})
endforeach(subdir)

add_executable(rasterizer
    rasterizeTriangle.cpp)

target_link_libraries(rasterizer renderer)
