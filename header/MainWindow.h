#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Define.h"
#include "QtSliderSpinBox.h"
#include "OperationStack.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    Vector<SharedPtr<QtSliderSpinBox>> m_sliderSpinBoxes;
    SharedPtr<OperationStack> m_operations;
};
#endif // MAINWINDOW_H
