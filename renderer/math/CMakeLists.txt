target_sources(renderer
    PRIVATE
        Vector3.hpp
        Ray.cpp Ray.hpp
        CoordSys.cpp CoordSys.hpp)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/renderer/math)