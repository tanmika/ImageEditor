//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_RENDERABLEOBJECT_H
#define QT_PRJ_IMAGE_EDITOR_RENDERABLEOBJECT_H

#include "RenderablePart.h"
#include "Shader.h"
#include "Texture.h"
#include "BGShape.h"
#include <functional>

class RenderableObject: public RenderablePart
{
public:
    RenderableObject() = default;
    ~RenderableObject() override = default;
    void Init() override;
    void Render(Mat4 projection, Mat4 view) override;
    bool GetVisible() override;
    void Resize(double width = 0, double height = 0);
    void SetShader(SharedPtr<Shader> shader);
    void SetTexture(SharedPtr<Texture> texture);
    void SetColor(Vec4 color);
    inline void RenderDelegate(std::function<void(SharedPtr<Shader>)> func) { m_renderFunc = func; }
    inline SharedPtr<Transform> GetTransform() override { return m_BGShape->GetTransform(); }
    inline BGShape& GetBaseShape() { return *m_BGShape; }
private:
    SharedPtr<Shader> m_Shader;
    SharedPtr<Texture> m_Texture;
    SharedPtr<BGShape> m_BGShape;
    Vec4 m_vec4Color{1.0f, 1.0f, 1.0f, 1.0f};
    std::function<void(SharedPtr<Shader>)> m_renderFunc;
};

#endif //QT_PRJ_IMAGE_EDITOR_RENDERABLEOBJECT_H
