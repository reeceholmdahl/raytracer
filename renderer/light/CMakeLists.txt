target_sources(renderer
    PRIVATE
        Light.cpp Light.hpp
        PointLight.cpp PointLight.hpp)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/renderer/light)