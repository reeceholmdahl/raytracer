include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/renderer)

foreach(renderer_subdir ${RENDERER_SUBDIRS})
  include_directories(${CMAKE_SOURCE_DIR}/renderer/${renderer_subdir})
endforeach(renderer_subdir)

SET(TESTS
    test_Framebuffer
    test_Cameras
    test_Miscellaneous
    test_RayDirectionColor
    test_LambertianShading
    test_SphereNormal)

foreach(exec ${TESTS})
  add_executable(${exec} ${BUNDLEOPTS} ${exec}.cpp)
  target_link_libraries(${exec} sive-util)
  target_link_libraries(${exec} renderer)
  target_link_libraries(${exec} ${Boost_PROGRAM_OPTIONS_LIBRARIES})
  target_link_libraries(${exec} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  target_link_libraries(${exec} ${Boost_LIBRARIES})
  target_link_libraries(${exec} ${PNG_LIBRARY})
  target_link_libraries(${exec} ${ZLIB_LIBRARY})

  # add test
  ADD_TEST(${exec} ${CMAKE_BINARY_DIR}/tests/${exec} -w ${CTEST_WINDOW_WIDTH} -h ${CTEST_WINDOW_HEIGHT} -f ${CTEST_OUTPUT_DIR})
  set_property(TEST ${exec} PROPERTY LABELS a)
endforeach(exec)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARY})

add_executable(test_Window test_Window.cpp)

target_link_libraries(test_Window sive-util)
target_link_libraries(test_Window renderer)
target_link_libraries(test_Window ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_Window ${Boost_LIBRARIES})
target_link_libraries(test_Window ${PNG_LIBRARY})
target_link_libraries(test_Window ${ZLIB_LIBRARY})
target_link_libraries(test_Window ${GLEW_LIBRARIES})
target_link_libraries(test_Window glfw ${GLFW_STATIC_LIBRARIES})