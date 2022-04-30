#include_directories(${CMAKE_SOURCE_DIR}/renderer)

target_sources(renderer
    PRIVATE
        Shape.cpp Shape.hpp
        BBox.cpp BBox.hpp
        Triangle.cpp Triangle.hpp
        Sphere.cpp Sphere.hpp
        Box.cpp Box.hpp)