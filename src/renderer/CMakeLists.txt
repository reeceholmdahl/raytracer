include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(renderer
    Vector3.hpp
    Framebuffer.cpp Framebuffer.hpp
    Light.cpp Light.hpp
    Shape.cpp Shape.hpp
    Shader.cpp Shader.hpp
    Triangle.cpp Triangle.hpp
    Sphere.cpp Sphere.hpp
    Ray.cpp Ray.hpp
    CoordinateSys.cpp CoordinateSys.hpp
    PointLight.cpp PointLight.hpp
    SceneContainer.cpp SceneContainer.hpp
    Camera.cpp Camera.hpp
    OrthographicCamera.cpp OrthographicCamera.hpp
    PerspectiveCamera.cpp PerspectiveCamera.hpp)

target_link_libraries(renderer sive-util)