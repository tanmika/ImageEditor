//
// Created by 檀木筪 on 2024/6/21.
//

#include "EditablePicture.h"
#include <QString>
#include "Tools.h"

SharedPtr<Shader> EditablePicture::GetShader()
{
    static bool isInit = false;
    static SharedPtr<Shader> shader;
    if (!isInit)
    {
        using namespace Tools;
        shader = std::make_shared<Shader>();
        shader->InitShaderFromFile(ShaderPath("EditablePictureShaderVert.glsl"),
                                   ShaderPath("EditablePictureShaderFrag.glsl"));
        isInit = true;
    }
    return shader;
}

EditablePicture::EditablePicture():
        m_renderableObject(),
        m_transform(std::make_shared<Transform>()),
        m_picture(std::make_shared<Picture>()),
        m_texture(std::make_shared<Texture>())
{
}

void EditablePicture::Init()
{
    m_renderableObject.Init();
    m_renderableObject.SetShader(GetShader());
    m_renderableObject.GetTransform()->SetParent(m_transform);
    m_renderableObject.RenderDelegate([this](SharedPtr<Shader> shader)
    {
        shader->UniformVec3("prams", Vec3(m_nBlurValue, m_nSharpenValue, m_nMonochromeValue));
        shader->UniformVec2("TextureSize", Vec2(m_rect.width, m_rect.height));
    });
}

void EditablePicture::Render(Mat4 projection, Mat4 view)
{
    m_renderableObject.Render(projection, view);
}

bool EditablePicture::GetVisible()
{
    return b_isVisible;
}

SharedPtr<Transform> EditablePicture::GetTransform()
{
    return m_transform;
}

void EditablePicture::Resize(double width, double height)
{
    m_rect.width = width;
    m_rect.height = height;
    m_renderableObject.Resize(width, height);
}

void EditablePicture::LoadPicture(const QString& path)
{
    m_picture->Init(path.toStdString().c_str());
    m_texture->Init(m_picture);
    m_renderableObject.SetTexture(m_texture);
    Resize(m_picture->GetWidth(), m_picture->GetHeight());
}

void EditablePicture::ClearPicture()
{
    m_picture.reset();
    m_texture.reset();
    m_renderableObject.SetTexture(nullptr);
}


void EditablePicture::FitToScreen()
{
    auto ScaleRadio = 1.0f;
    auto widthRadio = m_rect.width / G_WND_WIDTH;
    auto heightRadio = m_rect.height / G_WND_HEIGHT;
    assertMsg(widthRadio > 0 && heightRadio > 0, "Invalid width or height!");
    ScaleRadio = std::max(widthRadio, heightRadio);
    m_renderableObject.GetTransform()->SetScale(Vec3(1.0f/ScaleRadio, 1.0f/ScaleRadio, 1.0f));
    if(widthRadio > heightRadio)
    {
        m_transform->SetPos(Vec3(0.0f, (G_WND_HEIGHT - m_rect.height / ScaleRadio) / 2, 0.0f));
    }
    else
    {
        m_transform->SetPos(Vec3((G_WND_WIDTH - m_rect.width / ScaleRadio) / 2, 0.0f, 0.0f));
    }
}

void EditablePicture::FitToOriginal()
{
    m_renderableObject.GetTransform()->SetScale(Vec3(1.0f, 1.0f, 1.0f));
}

void EditablePicture::SetRectX(const int width)
{

}

void EditablePicture::SetRectY(const int height)
{

}

void EditablePicture::Rotate(const int angle)
{

}

void EditablePicture::Blur(int value)
{
    m_nBlurValue = value;
}

void EditablePicture::Sharpen(int value)
{
    m_nSharpenValue = value;
}

void EditablePicture::Monochrome(int value)
{
    m_nMonochromeValue = value;
}

int EditablePicture::FinishBlur()
{
    auto r = m_nBlurRecord;
    m_nBlurRecord = m_nBlurValue;
    return r;
}

int EditablePicture::FinishSharpen()
{
    auto r = m_nSharpenRecord;
    m_nSharpenRecord = m_nSharpenValue;
    return r;
}

int EditablePicture::FinishMonochrome()
{
    auto r = m_nMonochromeRecord;
    m_nMonochromeRecord = m_nMonochromeValue;
    return r;
}
