//
// Created by 檀木筪 on 2024/6/21.
//

#include "PictureLoader.h"
#include "stb_image.h"
void PictureLoader::LoadPicture(const char* path)
{
    if(m_bPictureInit)
    {
        stbi_image_free(m_pData);
    }
    // stbi_set_flip_vertically_on_load(true);
    m_pData = stbi_load(path, &m_nWidth, &m_nHeight, &m_nNrChannels, 0);
    if (m_pData)
    {
        m_bPictureInit = true;
    }
    else
    {
        std::cerr << "Failed to load picture" << std::endl;
    }
}

void PictureLoader::ReleasePicture()
{
    if (m_bPictureInit)
    {
        stbi_image_free(m_pData);
        m_bPictureInit = false;
    }
    else
    {
        std::cerr << "Picture has not been initialized!" << std::endl;
    }
}