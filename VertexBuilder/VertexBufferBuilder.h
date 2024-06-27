//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_VERTEXBUFFERBUILDER_H
#define QT_PRJ_IMAGE_EDITOR_VERTEXBUFFERBUILDER_H


/*
 * 顶点属性类型
 * vertex: 顶点坐标
 * uv0 - 3: 纹理坐标
 * color0 - 3: 颜色
 * 顶点属性类型的顺序必须与GLSL中的顺序一致
 glsl定义 :
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec2 aTexCoords1;
layout(location = 3) in vec2 aTexCoords2;
layout(location = 4) in vec2 aTexCoords3;
layout(location = 5) in vec4 aColor;
layout(location = 6) in vec4 aColor1;
layout(location = 7) in vec4 aColor2;
layout(location = 8) in vec4 aColor3;
 */

enum GLVertexAttributeType
{
    GL_Vertex = 0,
    GL_UV0 = 3,
    GL_UV1 = 5,
    GL_UV2 = 7,
    GL_UV3 = 9,
    GL_Color0 = 11,
    GL_Color1 = 15,
    GL_Color2 = 19,
    GL_Color3 = 23,
    Size = 27,
    Count = 9
};

#include "Define.h"
#include <qopengl.h>

class VertexBufferBuilder final
{
public:
    VertexBufferBuilder();

    ~VertexBufferBuilder() = default;

    //--------------------------------------------------------------------------------
    template<typename T>
    void AppendVector(Vector<T>& vec, GLVertexAttributeType type);

    bool GetVertexValidLength(size_t& length) const;

    void Build(float* buffer, GLuint& VAO, GLuint& VBO);
    //--------------------------------------------------------------------------------
private:
    Vector<Vec3> m_vecVertex;
    Vector<Vec2> m_vecUV0;
    Vector<Vec2> m_vecUV1;
    Vector<Vec2> m_vecUV2;
    Vector<Vec2> m_vecUV3;
    Vector<Vec4> m_vecColor0;
    Vector<Vec4> m_vecColor1;
    Vector<Vec4> m_vecColor2;
    Vector<Vec4> m_vecColor3;

    size_t m_nMinVecSize;
    size_t m_nMaxVecSize;
};


#include "VertexBufferBuilder.inl"

#endif //QT_PRJ_IMAGE_EDITOR_VERTEXBUFFERBUILDER_H
