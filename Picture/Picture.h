//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_PICTURE_H
#define QT_PRJ_IMAGE_EDITOR_PICTURE_H

#include "Texture.h"
#include "PictureLoader.h"

class Picture: public TextureData
{
public:
    Picture() = default;
    ~Picture() override;
    void Init(const char* path);
    void InitPictureResource(const char* file);
    [[nodiscard]] unsigned int GetWidth() const override;
    [[nodiscard]] unsigned int GetHeight() const override;
    [[nodiscard]] unsigned int GetChannels() const override;
    [[nodiscard]] unsigned char* GetData() const override;
private:
    PictureLoader m_loader;
    unsigned char* m_pData{};
    unsigned int m_nWidth{};
    unsigned int m_nHeight{};
    unsigned int m_nChannels{};
    bool m_bPictureInit = false;
};


#endif //QT_PRJ_IMAGE_EDITOR_PICTURE_H
