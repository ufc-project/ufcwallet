#include "FunctionAdvanceWidget.h"
#include "ui_FunctionAdvanceWidget.h"

#include "extra/style.h"
#include <QPainter>

FunctionAdvanceWidget::FunctionAdvanceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionAdvanceWidget)
{
    ui->setupUi(this);
    InitWidget();
}

FunctionAdvanceWidget::~FunctionAdvanceWidget()
{
    delete ui;
}
void FunctionAdvanceWidget::retranslator()
{
    ui->retranslateUi(this);
}
void FunctionAdvanceWidget::DefaultShow()
{
//    PoundageShowSlots();
    MultiSigShowSlots();
}

void FunctionAdvanceWidget::PoundageShowSlots()
{
    ui->pushButton_poundage->setChecked(true);
    ui->pushButton_multiSig->setChecked(false);
    emit showPoundageSignal();
}

void FunctionAdvanceWidget::MultiSigShowSlots()
{
    ui->pushButton_poundage->setChecked(false);
    ui->pushButton_multiSig->setChecked(true);
    emit showMultiSigSignal();
}

void FunctionAdvanceWidget::InitWidget()
{
    InitStyle();
    ui->pushButton_poundage->setCheckable(true);
    ui->pushButton_multiSig->setCheckable(true);
    connect(ui->pushButton_poundage,&QPushButton::clicked,this,&FunctionAdvanceWidget::PoundageShowSlots);
    connect(ui->pushButton_multiSig,&QPushButton::clicked,this,&FunctionAdvanceWidget::MultiSigShowSlots);

    ui->pushButton_poundage->hide();
}

void FunctionAdvanceWidget::InitStyle()
{
    setStyleSheet(FUNCTIONBAR_PUSHBUTTON_STYLE);
}

void FunctionAdvanceWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QColor(19,32,80));
    painter.drawRect(QRect(0,0,130,480));

    painter.setPen(QColor(105,124,255));
    painter.drawLine(20,62,110,62);
}
