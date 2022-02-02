# 
# Adds the src directory to the include search
# path. ${CMAKE_SOURCE_DIR} is prefixed to allow the files in the
# utest directory to correctly include the relative reference to the
# src files.
#
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/renderer)

foreach(renderer_subdir ${RENDERER_SUBDIRS})
  include_directories(${CMAKE_SOURCE_DIR}/src/renderer/${renderer_subdir})
endforeach(renderer_subdir)

# 
# This is a simple way to set the names of the executables used for
# the unit tests. Note that we are setting a variable, called
# ${UTESTS} to be the set of unit test executables. Then, in the next
# step, we iterate over all the elements within the ${UTESTS} set to
# compile into an executable.
# 
set(UTESTS 
  utest_Vector3D
  utest_Framebuffer
  utest_Vector3
  utest_Cameras
  utest_Miscellaneous
  utest_RayDirectionColor
  utest_LambertianShading)

# 
# For each of the executables named in ${UTESTS}, compile them into a
# boost unit test for use by the CMake CTest system.
# 
foreach(uexec ${UTESTS})
  add_executable(${uexec} ${BUNDLEOPTS} ${uexec}.cpp)
  target_link_libraries(${uexec} sive-util)
  target_link_libraries(${uexec} renderer)
  target_link_libraries(${uexec} ${Boost_PROGRAM_OPTIONS_LIBRARIES})
  target_link_libraries(${uexec} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  target_link_libraries(${uexec} ${Boost_LIBRARIES})
  target_link_libraries(${uexec} ${PNG_LIBRARY})
  target_link_libraries(${uexec} ${ZLIB_LIBRARY})
endforeach(uexec)

#
# Add these exectuables to the CMake Testing system. Executables added
# here in the ADD_TEST macro will be executed when make test is
# called.
#
foreach(uexec ${UTESTS})
  ADD_TEST(${uexec} ${CMAKE_BINARY_DIR}/utests/${uexec})
endforeach(uexec)