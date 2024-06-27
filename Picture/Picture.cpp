//
// Created by 檀木筪 on 2024/6/21.
//

#include "Picture.h"


#include "Picture.h"
#include "Tools.h"
#include "Define.h"

Picture::~Picture()
{
    if (m_bPictureInit)
    {
        m_loader.ReleasePicture();
    }
}

void Picture::Init(const char* path)
{
    m_loader.LoadPicture(path);
    m_pData = m_loader.m_pData;
    m_nWidth = m_loader.m_nWidth;
    m_nHeight = m_loader.m_nHeight;
    m_nChannels = m_loader.m_nNrChannels;
    m_bPictureInit = m_loader.m_bPictureInit;
}

unsigned int Picture::GetWidth() const
{
    return m_nWidth;
}

unsigned int Picture::GetHeight() const
{
    return m_nHeight;
}

unsigned int Picture::GetChannels() const
{
    return m_nChannels;
}

unsigned char* Picture::GetData() const
{
    return m_pData;
}

void Picture::InitPictureResource(const char* file)
{
    using namespace Tools;
    Init(SpliceString(LocalPath(PICTURE_PATH), "/", file));
}
