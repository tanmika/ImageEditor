//
// Created by 檀木筪 on 2024/6/25.
//

#ifndef QT_PRJ_IMAGE_EDITOR_QTSLIDERSPINBOX_H
#define QT_PRJ_IMAGE_EDITOR_QTSLIDERSPINBOX_H

#include "Define.h"
#include "ui_mainwindow.h"
#include <functional>

class QtSliderSpinBox final: public QObject
{
Q_OBJECT
public:
    explicit QtSliderSpinBox(QObject *parent = nullptr);
    void Init(QLabel* label, QSlider* slider, QSpinBox* spinBox, std::function<void(int)> valueChanged,
              std::function<void(int)> editingFinished = nullptr);
    void Set(String name, int value, int min, int max);
    void SetEditingFinished(std::function<void(int)> editingFinished);
    ~QtSliderSpinBox() override = default;
private slots:
    void OnValueChanged();
private:
    QLabel* m_label;
    QSlider* m_slider;
    QSpinBox* m_spinBox;
    std::function<void(int)> m_funcValueChanged;
    std::function<void(int)> m_funcEditingFinished;
    bool m_bUpdate;
};

#endif //QT_PRJ_IMAGE_EDITOR_QTSLIDERSPINBOX_H
