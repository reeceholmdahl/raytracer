include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/renderer)

add_executable(HardwareRenderer
                HardwareRenderer.cpp
                GLSL.cpp GLSL.h)

target_link_libraries(HardwareRenderer renderer)
target_link_libraries(HardwareRenderer ${PNG_LIBRARY})
target_link_libraries(HardwareRenderer ${ZLIB_LIBRARY})
target_link_libraries(HardwareRenderer ${OPENGL_LIBRARY})
target_link_libraries(HardwareRenderer ${GLEW_LIBRARIES})
target_link_libraries(HardwareRenderer glfw ${GLFW_STATIC_LIBRARIES})