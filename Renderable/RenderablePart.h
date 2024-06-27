//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_RENDERABLEPART_H
#define QT_PRJ_IMAGE_EDITOR_RENDERABLEPART_H

#include "Define.h"
#include "Transform.h"

class RenderablePart{
public:
    RenderablePart() = default;
    virtual ~RenderablePart() = default;
    virtual void Init() = 0;
    virtual void Render(Mat4 projection, Mat4 view) = 0;
    virtual bool GetVisible() = 0;
    virtual SharedPtr<Transform> GetTransform() = 0;
};

#endif //QT_PRJ_IMAGE_EDITOR_RENDERABLEPART_H
