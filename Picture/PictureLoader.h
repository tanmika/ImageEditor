//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_PICTURELOADER_H
#define QT_PRJ_IMAGE_EDITOR_PICTURELOADER_H
#include "Define.h"
#include "TextureData.h"

class PictureLoader
{
public:
    PictureLoader() = default;

    ~PictureLoader() = default;

    void LoadPicture(const char* path);

    void ReleasePicture();

    //--------------------------------------------------------------------------------
    unsigned char* m_pData;
    int m_nWidth;
    int m_nHeight;
    int m_nNrChannels;
    bool m_bPictureInit = false;
};
#endif //QT_PRJ_IMAGE_EDITOR_PICTURELOADER_H
