include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/renderer)

foreach(subdir ${RENDERER_SUBDIRS})
    include_directories(${CMAKE_SOURCE_DIR}/renderer/${subdir})
endforeach(subdir)

add_executable(renderer_app
    renderer_app.cpp renderer_app.hpp
    renderer_gui.cpp)

target_link_libraries(renderer_app sive-util)
target_link_libraries(renderer_app renderer)
target_link_libraries(renderer_app ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(renderer_app ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(renderer_app ${Boost_LIBRARIES})