target_sources(renderer
    PRIVATE
        Shape.hpp
        BBox.cpp BBox.hpp
        Triangle.cpp Triangle.hpp
        Sphere.cpp Sphere.hpp
        Box.cpp Box.hpp)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/renderer/geometry)