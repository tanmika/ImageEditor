#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_operations = OperationStack::Instance();
    for(int i=0; i<3; i++){
        m_sliderSpinBoxes.push_back(std::make_shared<QtSliderSpinBox>(this));
    }
    m_sliderSpinBoxes[0]->Init(ui->label, ui->horizontalSlider, ui->spinBox, [this](int value){
        ui->tanmiWidgwt->SetValue(value);
    }, [this](int value){
        auto record = ui->tanmiWidgwt->FinishValue();
        QString str;
        if(value > record)
            str = "模糊 +" + QString::number(value - record);
        else
            str = "模糊 -" + QString::number(record - value);
        OperationPtr op = std::make_shared<OperationData>(str, [=](){
            ui->tanmiWidgwt->SetValue(record);
            ui->horizontalSlider->setValue(record);
            ui->spinBox->setValue(record);
        }, [=](){
            ui->tanmiWidgwt->SetValue(value);
            ui->horizontalSlider->setValue(value);
            ui->spinBox->setValue(value);
        });
        m_operations->PushStack(op);
        ui->label_his->setText(m_operations->GetStack());
    });
    m_sliderSpinBoxes[0]->Set("模糊", 0, 0, 100);
    m_sliderSpinBoxes[1]->Init(ui->label_2, ui->horizontalSlider_2, ui->spinBox_2, [this](int value){
        ui->tanmiWidgwt->SetValue2(value);
    }, [this](int value){
        auto record = ui->tanmiWidgwt->FinishValue2();
        QString str;
        if(value > record)
            str = "锐化 +" + QString::number(value - record);
        else
            str = "锐化 -" + QString::number(record - value);
        OperationPtr op = std::make_shared<OperationData>(str ,[=](){
            ui->tanmiWidgwt->SetValue2(record);
            ui->horizontalSlider_2->setValue(record);
            ui->spinBox_2->setValue(record);
        }, [=](){
            ui->tanmiWidgwt->SetValue2(value);
            ui->horizontalSlider_2->setValue(value);
            ui->spinBox_2->setValue(value);
        });
        m_operations->PushStack(op);
        ui->label_his->setText(m_operations->GetStack());
    });
    m_sliderSpinBoxes[1]->Set("锐化", 0, 0, 100);
    m_sliderSpinBoxes[2]->Init(ui->label_3, ui->horizontalSlider_3, ui->spinBox_3, [this](int value){
        ui->tanmiWidgwt->SetValue3(value);
    }, [this](int value){
        auto record = ui->tanmiWidgwt->FinishValue3();
        QString str;
        if(value > record)
            str = "黑白 +" + QString::number(value - record);
        else
            str = "黑白 -" + QString::number(record - value);
        OperationPtr op = std::make_shared<OperationData>(str, [=](){
            ui->tanmiWidgwt->SetValue3(record);
            ui->horizontalSlider_3->setValue(record);
            ui->spinBox_3->setValue(record);
        }, [=](){
            ui->tanmiWidgwt->SetValue3(value);
            ui->horizontalSlider_3->setValue(value);
            ui->spinBox_3->setValue(value);
        });
        m_operations->PushStack(op);
        ui->label_his->setText(m_operations->GetStack());
    });
    m_sliderSpinBoxes[2]->Set("黑白", 0, 0, 100);

    ui->label_his->setText("");
    ui->label_5->setText("历史记录");
    ui->pushButton->setText("撤销");
    connect(ui->pushButton, &QPushButton::clicked, [this](){
        m_operations->Undo();
        ui->label_his->setText(m_operations->GetStack());
    });
    ui->pushButton_2->setText("重做");
    connect(ui->pushButton_2, &QPushButton::clicked, [this](){
        m_operations->Redo();
        ui->label_his->setText(m_operations->GetStack());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
