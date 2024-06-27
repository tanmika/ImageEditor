//
// Created by 檀木筪 on 2024/6/21.
//

#include "Transform.h"
#include <algorithm>

Transform::Transform():
        m_vecSize(Vec2{1.0f, 1.0f}),
        m_vecPos(Vec3{0.0f, 0.0f, 0.0f}),
        m_vecScale(Vec3{1.0f, 1.0f, 1.0f}),
        m_fAnglePart(0.0f),
        m_matModel(Mat4{1.0f}),
        m_matActModel(Mat4{1.0f}),
        m_bIsDirty(true),
        m_bSizeDirty(true),
        m_pParent({})
{
}

Transform::Transform(Vec3 pos, Vec3 scale, float angle):
        m_vecSize(Vec2(1.0f, 1.0f)),
        m_vecPos(pos),
        m_vecScale(scale),
        m_fAnglePart(angle),
        m_matModel(Mat4(1.0f)),
        m_matActModel(Mat4(1.0f)),
        m_bIsDirty(true),
        m_bSizeDirty(true),
        m_pParent({})
{
    TranslateMatrix(m_vecPos);
    RotateMatrix(angle);
    ScaleMatrix(m_vecScale);
}

Transform Transform::Copy()
{
    Transform temp{m_vecPos, m_vecScale, m_fAnglePart};
    temp.SetParent(m_pParent);
    return temp;
}

void Transform::Update()
{
    TranslateMatrix(m_vecPos);
    RotateMatrix(m_fAnglePart);
    ScaleMatrix(m_vecScale);
}

void Transform::SetSize(Vec2 size)
{
    m_vecSize = size;
    m_bSizeDirty = true;
}

void Transform::SetPos(Vec3 pos)
{
    auto temp = pos - m_vecPos;
    TranslateMatrix(temp);
    m_vecPos = pos;
    m_bIsDirty = true;
}

void Transform::Translate(Vec3 pos)
{
    TranslateMatrix(pos);
    m_vecPos += pos;
    m_bIsDirty = true;
}

void Transform::SetAngle(float angle)
{
    RotateMatrix(angle - m_fAnglePart);
    m_fAnglePart = angle;
    m_bIsDirty = true;
}

void Transform::Rotate(float angle)
{
    RotateMatrix(angle);
    m_fAnglePart += angle;
    m_bIsDirty = true;
}

void Transform::SetScale(Vec3 scale)
{
    Vec3 scale_temp;
    scale.x = std::max(0.01f, scale.x);
    scale.y = std::max(0.01f, scale.y);
    scale.z = std::max(0.01f, scale.z);
    scale_temp.x = scale.x / m_vecScale.x;
    scale_temp.y = scale.y / m_vecScale.y;
    scale_temp.z = scale.z / m_vecScale.z;
    ScaleMatrix(scale_temp);
    m_vecScale = scale;
    m_bIsDirty = true;
}

void Transform::Scale(Vec3 scale)
{
    ScaleMatrix(scale);
    m_vecScale *= scale;
    m_bIsDirty = true;
}


void Transform::Transforming(Transform& transform)
{
    SetPos(transform.GetPos());
    SetScale(transform.GetScale());
    SetAngle(transform.GetAngle());
    m_bIsDirty = true;
}


void Transform::Clear()
{
    SetPos(Vec3(0.0f, 0.0f, 0.0f));
    SetScale(Vec3(1.0f, 1.0f, 1.0f));
    SetAngle(0.0f);
    m_bIsDirty = true;
}

Mat4& Transform::GetModelMatrix()
{
    if (IsDirty())
    {
        m_matModel = Mat4(1.0f);
        if (m_pParent)
        {
            m_matModel = m_pParent->GetModelMatrix();
        }
        Update();
        m_bIsDirty = false;
    }
    return m_matModel;
}

Mat4& Transform::GetActMatrix()
{
    if(m_bSizeDirty || IsDirty())
    {
        m_matActModel = GetModelMatrix() * glm::scale(Mat4(1.0f), Vec3(m_vecSize.x, m_vecSize.y, 1.0f));
        m_bSizeDirty = false;
    }
    return m_matActModel;
}

void Transform::TranslateMatrix(Vec3& pos)
{
    m_matModel = glm::translate(m_matModel, pos);
}

void Transform::RotateMatrix(float angle)
{
    m_matModel = glm::rotate(m_matModel, angle, Vec3(0.0f, 0.0f, 1.0f));
}

void Transform::ScaleMatrix(Vec3& scale)
{
    m_matModel = glm::scale(m_matModel, scale);
}

bool Transform::IsDirty() const
{
    return m_bIsDirty || (m_pParent && m_pParent->IsDirty());
}
