//
// Created by 檀木筪 on 2024/6/21.
//

#include "BGShape.h"

#include <utility>
#include "VertexBufferBuilder.h"
#include "Tools.h"

BGShape::BGShape()
{
    m_nWidth = 10;
    m_nHeight = 10;
    m_transform = std::make_shared<Transform>();
    m_bVisible = true;
    m_defaultColor = Vec4(0.95f, 0.275f, 0.65f, 1.0f);
}

void BGShape::Resize(double width, double height)
{
    m_nWidth = width;
    m_nHeight = height;
    m_transform->SetSize(Vec2(width, height));
}
void BGShape::Init()
{
    m_shader = Tools::GetDefaultShapeShader();
    static Vector<Vec3> vertices = {
            Vec3(1.0f, 1.0f, 0.0f),  // 右上角
            Vec3(1.0f, 0.0f, 0.0f), // 右下角
            Vec3(0.0f, 1.0f, 0.0f), // 左上角
            Vec3(0.0f, 0.0f, 0.0f) // 左下角
    };
    static Vector<Vec2> uv = {
            Vec2(1.0f, 0.0f),
            Vec2(1.0f, 1.0f),
            Vec2(0.0f, 0.0f),
            Vec2(0.0f, 1.0f),
    };
    static Vector<GLuint> indexes = {0, 1, 3,
                                     0, 2, 3};
    VertexBufferBuilder builder;
    builder.AppendVector(vertices, GL_Vertex);
    builder.AppendVector(uv, GL_UV0);
    size_t bufferSize;
    if ( !builder.GetVertexValidLength(bufferSize))
    {
        std::cerr << "VBO size error!" << std::endl;
        return;
    }
    auto buffer = new float[bufferSize];
    builder.Build(buffer, m_VAO, m_VBO);
    delete[] buffer;
    Tools::GLBindBufferEBO(m_EBO, indexes);
}

void BGShape::Render(Mat4 projection, Mat4 view)
{
    if ( m_bVisible)
    {
        m_shader->Use();
        m_shader->UniformMat4("projection", projection);
        m_shader->UniformMat4("view", view);
        m_shader->UniformMat4("model", m_transform->GetActMatrix());
        m_shader->UniformVec4("color", m_defaultColor);
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void BGShape::SetShader(SharedPtr<Shader> shader)
{
    m_shader = std::move(shader);
}

void BGShape::SetVisible(bool bVisible)
{
    m_bVisible = bVisible;
}

void BGShape::SetColor(Vec4 color)
{
    m_defaultColor = color;
}

bool BGShape::GetVisible()
{
    return m_bVisible;
}

BGShape::~BGShape()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    m_bVisible = false;
}
