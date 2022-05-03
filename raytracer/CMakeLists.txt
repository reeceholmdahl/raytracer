include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/renderer)
include_directories(${OPENGL_INCLUDE_DIR})

foreach(subdir ${RENDERER_SUBDIRS})
    include_directories(${CMAKE_SOURCE_DIR}/renderer/${subdir})
endforeach(subdir)

add_executable(RayTracer
    RayTracer.cpp RayTracer.hpp)

target_link_libraries(RayTracer renderer)
target_link_libraries(RayTracer ${Boost_LIBRARIES})
target_link_libraries(RayTracer ${OPENGL_LIBRARY})
target_link_libraries(RayTracer ${GLEW_LIBRARIES})
target_link_libraries(RayTracer glfw ${GLFW_STATIC_LIBRARIES})

# add_executable(RayTracerGUI
#     RayTracer.cpp RayTracer.hpp
#     RayTracerGUI.cpp)

# target_link_libraries(RayTracer ${Boost_PROGRAM_OPTIONS_LIBRARIES})
#target_link_libraries(RayTracer ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# target_link_libraries(RayTracerGUI renderer)
#target_link_libraries(RayTracerGUI ${Boost_PROGRAM_OPTIONS_LIBRARIES})
#target_link_libraries(RayTracerGUI ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
# target_link_libraries(RayTracerGUI ${Boost_LIBRARIES})