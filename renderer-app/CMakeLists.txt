include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/renderer)

foreach(subdir ${RENDERER_SUBDIRS})
    include_directories(${CMAKE_SOURCE_DIR}/renderer/${subdir})
endforeach(subdir)

add_executable(renderer-app
    renderer_app.cpp renderer_app.hpp)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARY})

add_executable(renderer-gui
    renderer_app.cpp renderer_app.hpp
    renderer_gui.cpp)

target_link_libraries(renderer-app ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(renderer-app ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(renderer-app ${Boost_LIBRARIES})
target_link_libraries(renderer-app sive-util)
target_link_libraries(renderer-app renderer)

target_link_libraries(renderer-gui ${GLEW_LIBRARIES})
target_link_libraries(renderer-gui glfw ${GLFW_STATIC_LIBRARIES})
target_link_libraries(renderer-gui ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(renderer-gui ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(renderer-gui ${Boost_LIBRARIES})
target_link_libraries(renderer-gui sive-util)
target_link_libraries(renderer-gui renderer)