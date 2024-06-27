//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_TEXTURE_H
#define QT_PRJ_IMAGE_EDITOR_TEXTURE_H

#include "TextureData.h"
#include <qopengl.h>
class Texture
{
public:
    Texture() = default;
    virtual ~Texture() =default;
    virtual void Init(SharedPtr<TextureData> data);
    virtual void Use();
    virtual void TextureError();

    inline unsigned int GetWidth() const{
        return m_data->GetWidth();
    }
    inline unsigned int GetHeight() const{
        return m_data->GetHeight();
    }
private:
    SharedPtr<TextureData> m_data{};
    GLuint m_nTexture{};
    bool m_bInit{false};
};

#endif //QT_PRJ_IMAGE_EDITOR_TEXTURE_H
