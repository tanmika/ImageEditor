//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_TRANSFORM_H
#define QT_PRJ_IMAGE_EDITOR_TRANSFORM_H

#include <memory>
#include "Define.h"


class Transform final
{
public:
    Transform();
    explicit Transform(Vec3 pos, Vec3 scale = Vec3(1.0f, 1.0f, 1.0f), float angle = 0.0f);
    Transform Copy(); ///< 拷贝

    virtual ~Transform() = default;
    void Update(); ///< 更新, 只有非渲染物件才需要手动更新
    //--------------------------------------------------------------------------------
    void SetSize(Vec2 size); ///< 设置尺寸
    void SetPos(Vec3 pos); ///< 设置位置
    void Translate(Vec3 pos); ///< 平移
    void SetAngle(float angle); ///< 设置角度
    void Rotate(float angle); ///< 旋转
    void SetScale(Vec3 scale); ///< 设置缩放
    void Scale(Vec3 scale); ///< 缩放
    void Transforming(Transform& transform); ///< 转换
    void Clear(); ///< 清空
    //--------------------------------------------------------------------------------
    Mat4& GetModelMatrix(); ///< 获取模型矩阵
    Mat4& GetActMatrix(); ///< 获取实际矩阵(包含尺寸变化)
    inline Vec2 GetSize()const{
        return m_vecSize;
    } ///< 获取尺寸
    inline Vec3 GetPos()const{
        return m_vecPos;
    } ///< 获取位置
    inline Vec3 GetScale()const{
        return m_vecScale;
    } ///< 获取缩放
    inline float GetAngle()const{
        return m_fAnglePart;
    } ///< 获取角度
    //--------------------------------------------------------------------------------
    inline void SetParent(const std::shared_ptr<Transform> newParent) {
        // Check for circular reference
        auto ancestor = newParent;
        while (ancestor) {
            if (ancestor.get() == this) {
                std::cerr << "Transform::SetParent Circular reference detected!" << std::endl;
                return;
            }
            ancestor = ancestor->m_pParent;
        }
        m_pParent = newParent;
    }
    inline std::shared_ptr<Transform> GetParent()const{
        return m_pParent;
    } ///< 获取父节点
    inline void SetDirty(){
        m_bIsDirty = true;
    } ///< 设置脏标记
    [[nodiscard("Dirty Flag")]]
    bool IsDirty() const; ///< 获取脏标记
private:
    void TranslateMatrix(Vec3& pos); ///< 平移矩阵
    void RotateMatrix(float angle); ///< 旋转矩阵
    void ScaleMatrix(Vec3& scale); ///< 缩放矩阵
    Vec2 m_vecSize;
    Vec3 m_vecPos;
    Vec3 m_vecScale;
    float m_fAnglePart;
    Mat4 m_matModel;
    Mat4 m_matActModel;
    bool m_bIsDirty;
    bool m_bSizeDirty;

    std::shared_ptr<Transform> m_pParent; ///< 父节点引用
};
#endif //QT_PRJ_IMAGE_EDITOR_TRANSFORM_H
