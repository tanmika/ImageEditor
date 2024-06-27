//
// Created by 檀木筪 on 2024/6/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TanmiWidget.h" resolved

#include "TanmiWidget.h"
#include "EditablePicture.h"
#include <QTimer>
#include "Tools.h"


TanmiWidget::TanmiWidget(QWidget* parent) :
        QOpenGLWidget(parent)
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(16); // 每16毫秒刷新一次，约60帧每秒
    m_view = Mat4(1.0f);
    m_projection = Mat4(1.0f);
    m_renderableParts = {};
}

TanmiWidget::~TanmiWidget()= default;

void TanmiWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    G_WND_WIDTH = width();
    G_WND_HEIGHT = height();
    m_projection = glm::ortho(0.0f, G_WND_WIDTH, 0.0f, G_WND_HEIGHT, -1.0f, 1.0f);
    glViewport(0, 0, G_WND_WIDTH, G_WND_HEIGHT);

    auto object = std::make_shared<RenderableObject>();
    object->Init();
    object->Resize(400, 400);
    // m_renderableParts.push_back(object);

    auto picture = std::make_shared<EditablePicture>();
    picture->Init();
    picture->LoadPicture(Tools::TexturePath("04.jpg"));
    picture->FitToScreen();
    // m_renderableParts.push_back(picture);
    m_picture = picture;
}

void TanmiWidget::resizeGL(int w, int h)
{
    G_WND_WIDTH = w;
    G_WND_HEIGHT = h;
    m_projection = glm::ortho(0.0f, G_WND_WIDTH, 0.0f, G_WND_HEIGHT, -1.0f, 1.0f);
    glViewport(0, 0, w, h);
    QOpenGLWidget::resizeGL(w, h);
}

void TanmiWidget::paintGL()
{
    glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // for(auto& part : m_renderableParts)
    // {
    //     part->Render(m_projection, m_view);
    // }
    m_picture->Render(m_projection, m_view);
}

void TanmiWidget::SetValue(int value)
{
    m_picture->Blur(value);
}

void TanmiWidget::SetValue2(int value)
{
    m_picture->Sharpen(value);
}

void TanmiWidget::SetValue3(int value)
{
    m_picture->Monochrome(value);
}

void TanmiWidget::SetValue4(int value)
{

}

void TanmiWidget::SetValue5(int value)
{

}

void TanmiWidget::SetValue6(int value)
{

}

void TanmiWidget::SetString(const QString& str)
{

}

int TanmiWidget::FinishValue()
{
    return m_picture->FinishBlur();
}

int TanmiWidget::FinishValue2()
{
    return m_picture->FinishSharpen();
}

int TanmiWidget::FinishValue3()
{
    return m_picture->FinishMonochrome();
}
