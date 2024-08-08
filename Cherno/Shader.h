#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};


class Shader{

private:    
    // For debugging purposes
    std::string  m_FilePath;
    unsigned int m_RendererID;
    // caching uniforms
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;


    // Set uniforms
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
    void SetUniform1f(const std::string& name, float f0);

private:
    int GetUniformLocation(const std::string& name);
    uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    uint CompileShader(const std::string& source, uint type);
    ShaderProgramSource ParseShader(const std::string& filepath);

};
