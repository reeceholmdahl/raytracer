target_sources(renderer
    PRIVATE
        Camera.cpp Camera.hpp
        OrthographicCamera.cpp OrthographicCamera.hpp
        PerspectiveCamera.cpp PerspectiveCamera.hpp)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/renderer/camera)