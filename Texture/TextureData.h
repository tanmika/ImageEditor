//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_TEXTUREDATA_H
#define QT_PRJ_IMAGE_EDITOR_TEXTUREDATA_H

#include "Define.h"

class TextureDefaultData;

class TextureData
{
public:
    TextureData() = default;
    virtual ~TextureData() = default;

    [[nodiscard]] virtual unsigned int GetWidth() const = 0;
    [[nodiscard]] virtual unsigned int GetHeight() const = 0;
    [[nodiscard]] virtual unsigned int GetChannels() const = 0;
    [[nodiscard]] virtual unsigned char* GetData() const = 0;

    inline static SharedPtr<TextureData> GetDefaultTextureData();
};

class TextureDefaultData : public TextureData
{
public:
    TextureDefaultData():
            m_width(1),
            m_height(1),
            m_channels(3),
            m_data(nullptr)
    {
        m_data = new unsigned char[3];
        m_data[0] = 242;
        m_data[1] = 70;
        m_data[2] = 166;
    }
    ~TextureDefaultData() override
    {
        delete[] m_data;
    }

    inline unsigned int GetWidth() const override
    {
        return m_width;
    }

    inline unsigned int GetHeight() const override
    {
        return m_height;
    }

    inline unsigned int GetChannels() const override
    {
        return m_channels;
    }

    inline unsigned char* GetData() const override
    {
        return m_data;
    }
private:
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_channels;
    unsigned char* m_data;
};

SharedPtr<TextureData> TextureData::GetDefaultTextureData()
{
    static auto t = SharedPtr<TextureDefaultData>();
    return t;
}

#endif //QT_PRJ_IMAGE_EDITOR_TEXTUREDATA_H
