include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/renderer)

foreach(subdir ${RENDERER_SUBDIRS})
    include_directories(${CMAKE_SOURCE_DIR}/renderer/${subdir})
endforeach(subdir)

add_executable(RayTracer
    RayTracer.cpp RayTracer.hpp)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARY})

add_executable(RayTracerGUI
    RayTracer.cpp RayTracer.hpp
    RayTracerGUI.cpp)

target_link_libraries(RayTracer ${Boost_LIBRARIES})
target_link_libraries(RayTracer sive-util)
target_link_libraries(RayTracer renderer)

target_link_libraries(RayTracerGUI ${GLEW_LIBRARIES})
target_link_libraries(RayTracerGUI glfw ${GLFW_STATIC_LIBRARIES})
target_link_libraries(RayTracerGUI ${Boost_LIBRARIES})
target_link_libraries(RayTracerGUI sive-util)
target_link_libraries(RayTracerGUI renderer)