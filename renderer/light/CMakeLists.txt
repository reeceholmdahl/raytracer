target_sources(renderer
    PRIVATE
        Light.hpp
        PointLight.hpp)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/renderer/light)