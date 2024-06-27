//
// Created by 檀木筪 on 2024/6/21.
//

#include "Texture.h"

void Texture::Init(SharedPtr<TextureData> data)
{
    m_data = data;
    m_bInit = true;
    glGenTextures(1, &m_nTexture);
    glBindTexture(GL_TEXTURE_2D, m_nTexture);
    auto channels =0;
    switch (m_data->GetChannels())
    {
        case 1:
            channels = GL_RED;
            break;
        case 3:
            channels = GL_RGB;
            break;
        case 4:
            channels = GL_RGBA;
            break;
        default:
            channels = GL_RGB;
            break;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, channels, m_data->GetWidth(), m_data->GetHeight(), 0, channels, GL_UNSIGNED_BYTE, m_data->GetData());
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Use()
{
    if(!m_bInit)
    {
        TextureError();
    }
    glBindTexture(GL_TEXTURE_2D, m_nTexture);
}

void Texture::TextureError()
{
    m_data = TextureData::GetDefaultTextureData();
    glGenTextures(1, &m_nTexture);
    glBindTexture(GL_TEXTURE_2D, m_nTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_data->GetWidth(), m_data->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_data->GetData());
    m_bInit = true;
}
