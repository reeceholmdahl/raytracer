target_sources(renderer
    PRIVATE
        HitStruct.hpp
        Shader.cpp Shader.hpp
        DiffuseShader.cpp DiffuseShader.hpp
        NormalShader.cpp NormalShader.hpp
        LambertShader.cpp LambertShader.hpp
        BlinnPhongShader.cpp BlinnPhongShader.hpp)