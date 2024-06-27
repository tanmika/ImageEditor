//
// Created by 檀木筪 on 2024/6/21.
//

#ifndef QT_PRJ_IMAGE_EDITOR_TANMIWIDGET_H
#define QT_PRJ_IMAGE_EDITOR_TANMIWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include "Define.h"
#include "RenderablePart.h"
#include "EditablePicture.h"

class TanmiWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit TanmiWidget(QWidget* parent = nullptr);

    ~TanmiWidget() override;
public slots:
    void SetValue(int value);
    void SetValue2(int value);
    void SetValue3(int value);
    void SetValue4(int value);
    void SetValue5(int value);
    void SetValue6(int value);
    void SetString(const QString& str);
    int FinishValue();
    int FinishValue2();
    int FinishValue3();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    Mat4 m_projection;
    Mat4 m_view;
    Vector<SharedPtr<RenderablePart> > m_renderableParts;
    SharedPtr<EditablePicture> m_picture;
};


#endif //QT_PRJ_IMAGE_EDITOR_TANMIWIDGET_H
