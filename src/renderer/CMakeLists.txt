add_library(renderer
    Framebuffer.cpp Framebuffer.hpp
    Light.cpp Light.hpp
    Camera.cpp Camera.hpp
    Shape.cpp Shape.hpp
    Shader.cpp Shader.hpp
    Triangle.cpp Triangle.hpp
    CoordinateSys.cpp CoordinateSys.hpp
    OrthographicCamera.cpp OrthographicCamera.hpp
    PointLight.cpp PointLight.hpp)

include_directories(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(renderer sive-util)