target_sources(renderer
    PRIVATE
        DiffuseShader.cpp
        NormalShader.cpp
        LambertShader.cpp
        BlinnPhongShader.cpp)

target_include_directories(renderer PRIVATE ${CMAKE_SOURCE_DIR}/renderer/shader)