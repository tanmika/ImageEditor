//
// Created by 檀木筪 on 2024/6/25.
//

#include "QtSliderSpinBox.h"


#include "QtSliderSpinBox.h"


QtSliderSpinBox::QtSliderSpinBox(QObject* parent)
        : QObject(parent), m_label(nullptr), m_slider(nullptr), m_spinBox(nullptr), m_funcValueChanged(nullptr), m_bUpdate(false)
{
}

void QtSliderSpinBox::Init(QLabel* label, QSlider* slider, QSpinBox* spinBox, std::function<void(int)> valueChanged, std::function<void(int)> editingFinished)
{
    m_label = label;
    m_slider = slider;
    m_spinBox = spinBox;
    m_funcValueChanged = valueChanged;
    m_funcEditingFinished = editingFinished ? editingFinished : valueChanged;

    connect(m_slider, &QSlider::valueChanged, this, &QtSliderSpinBox::OnValueChanged);
    connect(m_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtSliderSpinBox::OnValueChanged);
    connect(m_slider, &QSlider::sliderReleased, [this](){
        m_funcEditingFinished(m_slider->value());
    });
    connect(m_spinBox, &QSpinBox::editingFinished, [this](){
        m_funcEditingFinished(m_spinBox->value());
    });
}

void QtSliderSpinBox::OnValueChanged()
{
    if(m_bUpdate)
        return;
    m_bUpdate = true;
    if(sender() == m_slider)
    {
        m_spinBox->setValue(m_slider->value());
    }
    else if(sender() == m_spinBox)
    {
        m_slider->setValue(m_spinBox->value());
    }
    m_funcValueChanged(m_slider->value());
    m_bUpdate = false;
}

void QtSliderSpinBox::Set(String name, int value, int min, int max)
{
    m_bUpdate = true;
    m_label->setText(name.c_str());
    m_slider->setRange(min, max);
    m_spinBox->setRange(min, max);
    m_slider->setValue(value);
    m_spinBox->setValue(value);
    m_bUpdate = false;
}

void QtSliderSpinBox::SetEditingFinished(std::function<void(int)> editingFinished)
{
    disconnect(m_slider, &QSlider::sliderReleased, nullptr, nullptr);
    disconnect(m_spinBox, &QSpinBox::editingFinished, nullptr, nullptr);
    m_funcEditingFinished = editingFinished;
    connect(m_slider, &QSlider::sliderReleased, [this](){
        m_funcEditingFinished(m_slider->value());
    });
    connect(m_spinBox, &QSpinBox::editingFinished, [this](){
        m_funcEditingFinished(m_spinBox->value());
    });
}
