//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_BGSHAPE_H
#define QT_PRJ_IMAGE_EDITOR_BGSHAPE_H


#include "RenderablePart.h"
#include "Transform.h"
#include "Shader.h"
#include <qopengl.h>
class BGShape final : public RenderablePart
{
public:
    BGShape();
    ~BGShape() override;
    void SetShader(SharedPtr<Shader> shader);
    void SetVisible(bool bVisible) ;
    void SetColor(Vec4 color);
    void Resize(double width, double height);
    void Init() override;
    void Render(Mat4 projection, Mat4 view) override;
    bool GetVisible() override;
    [[nodiscard]] inline GLuint GetVAO() const{ return m_VAO; }
    inline SharedPtr<Transform> GetTransform() override { return m_transform; }
    inline double GetWidth() const { return m_nWidth; }
    inline double GetHeight() const { return m_nHeight; }
private:
    double m_nWidth;
    double m_nHeight;
    Vec4 m_defaultColor;

    SharedPtr<Transform> m_transform;
    SharedPtr<Shader> m_shader;

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    bool m_bVisible;
};

#endif //QT_PRJ_IMAGE_EDITOR_BGSHAPE_H
