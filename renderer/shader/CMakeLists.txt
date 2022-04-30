target_sources(renderer
    PRIVATE
        Shader.cpp
        HitStruct.hpp
        DiffuseShader.cpp DiffuseShader.hpp
        NormalShader.cpp NormalShader.hpp
        LambertShader.cpp LambertShader.hpp
        BlinnPhongShader.cpp BlinnPhongShader.hpp)