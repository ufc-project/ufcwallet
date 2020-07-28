#include "FunctionExchangeWidget.h"
#include "ui_FunctionExchangeWidget.h"

#include "extra/style.h"
#include <QPainter>

FunctionExchangeWidget::FunctionExchangeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionExchangeWidget)
{
    ui->setupUi(this);
    InitWidget();
}

FunctionExchangeWidget::~FunctionExchangeWidget()
{
    delete ui;
}

void FunctionExchangeWidget::retranslator()
{
    ui->retranslateUi(this);
}

void FunctionExchangeWidget::DefaultShow()
{
    on_exchangeBtn_clicked();
}

void FunctionExchangeWidget::InitWidget()
{
    InitStyle();
    ui->exchangeBtn->setCheckable(true);
    ui->onchainOrderBtn->setCheckable(true);
    ui->contractTokenBtn->setCheckable(true);
}

void FunctionExchangeWidget::InitStyle()
{
    setStyleSheet(FUNCTIONBAR_PUSHBUTTON_STYLE);
}


void FunctionExchangeWidget::on_exchangeBtn_clicked()
{
    ui->exchangeBtn->setChecked(true);
    ui->onchainOrderBtn->setChecked(false);
    ui->contractTokenBtn->setChecked(false);
    Q_EMIT showExchangeModeSignal();
}


void FunctionExchangeWidget::on_onchainOrderBtn_clicked()
{
    ui->exchangeBtn->setChecked(false);
    ui->onchainOrderBtn->setChecked(true);
    ui->contractTokenBtn->setChecked(false);
    Q_EMIT showOnchainOrderSignal();
}

void FunctionExchangeWidget::on_contractTokenBtn_clicked()
{
    ui->exchangeBtn->setChecked(false);
    ui->onchainOrderBtn->setChecked(false);
    ui->contractTokenBtn->setChecked(true);
    Q_EMIT showContractTokenSignal();
}


void FunctionExchangeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QColor(19,32,80));
    painter.drawRect(QRect(0,0,130,480));

    painter.setPen(QColor(105,124,255));
    painter.drawLine(20,62,110,62);
}

