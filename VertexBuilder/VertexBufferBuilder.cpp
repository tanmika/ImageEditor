//
// Created by 檀木筪 on 2024/6/21.
//

#include "VertexBufferBuilder.h"

VertexBufferBuilder::VertexBufferBuilder()
{
    m_nMinVecSize = UINT16_MAX;
    m_nMaxVecSize = 0;
    m_vecVertex = Vector<Vec3>();
    m_vecUV0 = Vector<Vec2>();
    m_vecUV1 = Vector<Vec2>();
    m_vecUV2 = Vector<Vec2>();
    m_vecUV3 = Vector<Vec2>();
    m_vecColor0 = Vector<Vec4>();
    m_vecColor1 = Vector<Vec4>();
    m_vecColor2 = Vector<Vec4>();
    m_vecColor3 = Vector<Vec4>();
}

bool VertexBufferBuilder::GetVertexValidLength(size_t& length) const
{
    length = m_nMinVecSize * GLVertexAttributeType::Size;
    return m_nMaxVecSize == m_nMinVecSize;
}

void VertexBufferBuilder::Build(float* buffer, GLuint& VAO, GLuint& VBO)
{
    auto originBuffer = buffer;
    size_t length = m_nMinVecSize;
    for (size_t i = 0; i < length; ++i)
    {
        if ( !m_vecVertex.empty())
        {
            buffer[0] = m_vecVertex[i].x;
            buffer[1] = m_vecVertex[i].y;
            buffer[2] = m_vecVertex[i].z;
        }
        buffer += 3;
        if ( !m_vecUV0.empty())
        {
            buffer[0] = m_vecUV0[i].x;
            buffer[1] = m_vecUV0[i].y;
        }
        buffer += 2;
        if ( !m_vecUV1.empty())
        {
            buffer[0] = m_vecUV1[i].x;
            buffer[1] = m_vecUV1[i].y;
        }
        buffer += 2;
        if ( !m_vecUV2.empty())
        {
            buffer[0] = m_vecUV2[i].x;
            buffer[1] = m_vecUV2[i].y;
        }
        buffer += 2;
        if ( !m_vecUV3.empty())
        {
            buffer[0] = m_vecUV3[i].x;
            buffer[1] = m_vecUV3[i].y;
        }
        buffer += 2;
        if ( !m_vecColor0.empty())
        {
            buffer[0] = m_vecColor0[i].x;
            buffer[1] = m_vecColor0[i].y;
            buffer[2] = m_vecColor0[i].z;
            buffer[3] = m_vecColor0[i].w;
        }
        buffer += 4;
        if ( !m_vecColor1.empty())
        {
            buffer[0] = m_vecColor1[i].x;
            buffer[1] = m_vecColor1[i].y;
            buffer[2] = m_vecColor1[i].z;
            buffer[3] = m_vecColor1[i].w;
        }
        buffer += 4;
        if ( !m_vecColor2.empty())
        {
            buffer[0] = m_vecColor2[i].x;
            buffer[1] = m_vecColor2[i].y;
            buffer[2] = m_vecColor2[i].z;
            buffer[3] = m_vecColor2[i].w;
        }
        buffer += 4;
        if ( !m_vecColor3.empty())
        {
            buffer[0] = m_vecColor3[i].x;
            buffer[1] = m_vecColor3[i].y;
            buffer[2] = m_vecColor3[i].z;
            buffer[3] = m_vecColor3[i].w;
        }
        buffer += 4;
    }
    buffer = originBuffer;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, length * GLVertexAttributeType::Size * sizeof(float), buffer, GL_STATIC_DRAW);
    GLVertexAttributeType type[GLVertexAttributeType::Count + 1] =
            {GL_Vertex, GL_UV0, GL_UV1, GL_UV2, GL_UV3,
             GL_Color0, GL_Color1, GL_Color2, GL_Color3, Size};
    for (int i = 0; i < GLVertexAttributeType::Count; ++i)
    {
        int size = type[i + 1] - type[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE,
                              GLVertexAttributeType::Size * sizeof(float),
                              (void*) (type[i] * sizeof(float)));
    }
}
