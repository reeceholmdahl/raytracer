include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/renderer)

foreach(renderer_subdir ${RENDERER_SUBDIRS})
  include_directories(${CMAKE_SOURCE_DIR}/src/renderer/${renderer_subdir})
endforeach(renderer_subdir)

SET(TESTS
    test_Framebuffer
    test_Cameras
    test_Miscellaneous
    test_RayDirectionColor
    test_LambertianShading)

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