//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_EDITABLEPICTURE_H
#define QT_PRJ_IMAGE_EDITOR_EDITABLEPICTURE_H

#include "RenderableObject.h"
#include "Picture.h"

class EditablePicture: public RenderablePart
{
public:
    EditablePicture();
    ~EditablePicture() override = default;
    void Init() override;
    void Render(Mat4 projection, Mat4 view) override;
    bool GetVisible() override;
    SharedPtr<Transform> GetTransform() override;
    void Resize(double width = 0, double height = 0);

    void LoadPicture(const QString& path);
    void ClearPicture();

    void FitToScreen();
    void FitToOriginal();
    void SetRectX(const int width);
    void SetRectY(const int height);
    void Rotate(const int angle);

    void Blur(int value);
    void Sharpen(int value);
    void Monochrome(int value);
    int FinishBlur();
    int FinishSharpen();
    int FinishMonochrome();

private:
    static SharedPtr<Shader> GetShader();
    RenderableObject m_renderableObject;
    SharedPtr<Transform> m_transform;
    SharedPtr<Picture> m_picture;
    SharedPtr<Texture> m_texture;
    int m_nBlurValue{0};
    int m_nBlurRecord{0};
    int m_nSharpenValue{0};
    int m_nSharpenRecord{0};
    int m_nMonochromeValue{0};
    int m_nMonochromeRecord{0};
    struct Rect{
        unsigned int width{0};
        unsigned int height{0};
    } m_rect;
    bool b_isVisible{true};
};

#endif //QT_PRJ_IMAGE_EDITOR_EDITABLEPICTURE_H
