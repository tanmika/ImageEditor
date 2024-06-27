//
// Created by 檀木筪 on 2024/6/21.
//

#include "RenderableObject.h"
#include <qopengl.h>
#include <iostream>

void RenderableObject::Init()
{
    m_BGShape = std::make_shared<BGShape>();
    m_BGShape->Init();
}

void RenderableObject::Render(Mat4 projection, Mat4 view)
{
    if(m_BGShape != nullptr && m_BGShape->GetVisible())
    {
        if(m_Shader == nullptr || m_Texture == nullptr)
            m_BGShape->Render(projection, view);
        else
        {
            m_Shader->Use();
            m_Shader->UniformMat4("projection", projection);
            m_Shader->UniformMat4("view", view);
            m_Shader->UniformMat4("model", m_BGShape->GetTransform()->GetActMatrix());
            m_Shader->UniformVec4("color", m_vec4Color);
            if(m_renderFunc)
                m_renderFunc(m_Shader);
            m_Texture->Use();
            glBindVertexArray(m_BGShape->GetVAO());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}

bool RenderableObject::GetVisible()
{
    if (m_BGShape != nullptr)
        return m_BGShape->GetVisible();
    else
        return false;
}

void RenderableObject::Resize(double width, double height)
{
    if(m_BGShape != nullptr)
    {
        width = width == 0 ? (m_Texture ? m_Texture->GetWidth() : 1) : width;
        height = height == 0 ? (m_Texture ? m_Texture->GetHeight() : 1) : height;
        m_BGShape->Resize(width, height);
    }
}

void RenderableObject::SetShader(SharedPtr<Shader> shader)
{
    m_Shader = shader;
}

void RenderableObject::SetTexture(SharedPtr<Texture> texture)
{
    m_Texture = texture;
}

void RenderableObject::SetColor(Vec4 color)
{
    m_vec4Color = color;
}
