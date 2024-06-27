//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_SHADER_H
#define QT_PRJ_IMAGE_EDITOR_SHADER_H

#include "Define.h"
#include <qopengl.h>

class Shader final
{
private:
    bool m_bShaderInit; ///< 着色器是否初始化
    GLuint m_nShaderProgram; ///< 着色器程序
public:
    Shader();
    ~Shader();
    //--------------------------------------------------------------------------------
    bool InitShader(const char* vertexShader, const char* fragShader); ///< 初始化着色器
    bool InitShaderFromFile(const char* vertexShaderPath, const char* fragShaderPath); ///< 从文件初始化着色器
    bool InitShaderFromShaderFile(const char* vertexShaderFile, const char* fragShaderFile); ///< 使用文件初始化着色器
    //--------------------------------------------------------------------------------
    void Use() const; ///< 使用着色器
    inline bool IsInit() const{
        return m_bShaderInit; ///< 着色器是否初始化
    }
    //--------------------------------------------------------------------------------
    void UniformFloat(const char* name, float value) const; ///< 设置float类型的uniform
    void UniformInt(const char* name, int value) const; ///< 设置int类型的uniform
    void UniformVec2(const char* name, float x, float y) const; ///< 设置vec2类型的uniform
    void UniformVec2(const char* name, glm::vec2 vec) const; ///< 设置vec2类型的uniform
    void UniformVec3(const char* name, float x, float y, float z) const; ///< 设置vec3类型的uniform
    void UniformVec3(const char* name, glm::vec3 vec) const; ///< 设置vec3类型的uniform
    void UniformVec4(const char* name, float x, float y, float z, float w) const; ///< 设置vec4类型的uniform
    void UniformVec4(const char* name, glm::vec4 vec) const; ///< 设置vec4类型的uniform
    void UniformMat4(const char* name, float* value) const; ///< 设置mat4类型的uniform
    void UniformMat4(const char* name, glm::mat4 mat) const; ///< 设置mat4类型的uniform

};
#endif //QT_PRJ_IMAGE_EDITOR_SHADER_H
