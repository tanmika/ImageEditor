//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_VERTEXBUFFERBUILDER_INL
#define QT_PRJ_IMAGE_EDITOR_VERTEXBUFFERBUILDER_INL


#include "VertexBufferBuilder.h"

template<typename T>
void VertexBufferBuilder::AppendVector(std::vector<T>& v, GLVertexAttributeType type)
{
    bool validType = true;

    auto vec = v;

    switch (type)
    {
        case GL_Vertex:
            if constexpr (std::is_same_v<T, Vec3>)
            {
                m_vecVertex = vec;
            }
            else validType = false;
            break;
        case GL_UV0:
            if constexpr (std::is_same_v<T, Vec2>)
            {
                m_vecUV0 = vec;
            }
            else validType = false;
            break;
        case GL_UV1:
            if constexpr (std::is_same_v<T, Vec2>)
            {
                m_vecUV1 = vec;
            }
            else validType = false;
            break;
        case GL_UV2:
            if constexpr (std::is_same_v<T, Vec2>)
            {
                m_vecUV2 = vec;
            }
            else validType = false;
            break;
        case GL_UV3:
            if constexpr (std::is_same_v<T, Vec2>)
            {
                m_vecUV3 = vec;
            }
            else validType = false;
            break;
        case GL_Color0:
            if constexpr (std::is_same_v<T, Vec4>)
            {
                m_vecColor0 = vec;
            }
            else validType = false;
            break;
        case GL_Color1:
            if constexpr (std::is_same_v<T, Vec4>)
            {
                m_vecColor1 = vec;
            }
            else validType = false;
            break;
        case GL_Color2:
            if constexpr (std::is_same_v<T, Vec4>)
            {
                m_vecColor2 = vec;
            }
            else validType = false;
            break;
        case GL_Color3:
            if constexpr (std::is_same_v<T, Vec4>)
            {
                m_vecColor3 = vec;
            }
            else validType = false;
            break;
        default:
            std::cerr << "AppendVector: type error!";
            validType = false;
            break;
    }

    if (validType)
    {
        m_nMaxVecSize = std::max(m_nMaxVecSize, vec.size());
        m_nMinVecSize = std::min(m_nMinVecSize, vec.size());
    }
    else
    {
        std::cerr << "AppendVector: incorrect type for the given attribute type!";
    }
}


#endif //QT_PRJ_IMAGE_EDITOR_VERTEXBUFFERBUILDER_INL
