//
// Created by 檀木筪 on 2024/6/21.
//
#include "Tools.h"
#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader()
{
    m_bShaderInit = false;
    m_nShaderProgram = 0;
}
Shader::~Shader()
{
    if(m_bShaderInit)
        glDeleteProgram(m_nShaderProgram);
}
bool Shader::InitShader(const char* vertexShader, const char* fragShader)
{
    using namespace std;
    if ( m_bShaderInit )
    {
        cout << ("Shader has been initialized!\n");
        return false;
    }
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
    glCompileShader(vertexShaderID);
    GLint success;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if ( !success )
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
        cerr << "Vertex shader compile failed: " << infoLog << endl;
        return false;
    }

    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderID, 1, &fragShader, nullptr);
    glCompileShader(fragShaderID);
    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
    if ( !success )
    {
        char infoLog[512];
        glGetShaderInfoLog(fragShaderID, 512, nullptr, infoLog);
        cerr << "Fragment shader compile failed: " << infoLog << endl;
        return false;
    }

    m_nShaderProgram = glCreateProgram();
    glAttachShader(m_nShaderProgram, vertexShaderID);
    glAttachShader(m_nShaderProgram, fragShaderID);
    glLinkProgram(m_nShaderProgram);
    glGetProgramiv(m_nShaderProgram, GL_LINK_STATUS, &success);
    if ( !success )
    {
        char infoLog[512];
        glGetProgramInfoLog(m_nShaderProgram, 512, nullptr, infoLog);
        cerr << "Shader Program compile failed: " << infoLog << endl;
        return false;
    }
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragShaderID);
    m_bShaderInit = true;
    return true;
}

bool Shader::InitShaderFromFile(const char* vertexShaderPath, const char* fragShaderPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragShaderPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "read shader file failed." << std::endl;
        return false;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    return InitShader(vShaderCode, fShaderCode);
}

bool Shader::InitShaderFromShaderFile(const char* vertexShaderPath, const char* fragShaderPath)
{
    using namespace Tools;
    return InitShaderFromFile(ShaderPath(vertexShaderPath), ShaderPath(fragShaderPath));
}

void Shader::Use() const
{
    using namespace std;
    if ( !m_bShaderInit )
    {
        cerr << ("Shader has not been initialized!\n");
        Tools::GetDefaultShapeShader()->Use();
        return;
    }
    glUseProgram(m_nShaderProgram);
}

void Shader::UniformFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(m_nShaderProgram, name), value);
}

void Shader::UniformInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(m_nShaderProgram, name), value);
}

void Shader::UniformVec2(const char* name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_nShaderProgram, name), x, y);
}

void Shader::UniformVec3(const char* name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_nShaderProgram, name), x, y, z);
}

void Shader::UniformVec4(const char* name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(m_nShaderProgram, name), x, y, z, w);
}

void Shader::UniformMat4(const char* name, float* value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_nShaderProgram, name), 1, GL_FALSE, value);
}

void Shader::UniformVec2(const char* name, glm::vec2 vec) const
{
    glUniform2f(glGetUniformLocation(m_nShaderProgram, name), vec.x, vec.y);
}

void Shader::UniformVec3(const char* name, glm::vec3 vec) const
{
    glUniform3f(glGetUniformLocation(m_nShaderProgram, name), vec.x, vec.y, vec.z);
}

void Shader::UniformVec4(const char* name, glm::vec4 vec) const
{
    glUniform4f(glGetUniformLocation(m_nShaderProgram, name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::UniformMat4(const char* name, glm::mat4 mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_nShaderProgram, name), 1, GL_FALSE, &mat[0][0]);
}
