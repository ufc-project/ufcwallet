#include "FunctionAccountWidget.h"
#include "ui_FunctionAccountWidget.h"

#include "extra/style.h"
#include <QPainter>
#include <QDebug>

FunctionAccountWidget::FunctionAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionAccountWidget)
{
    ui->setupUi(this);
    InitWidget();
}

FunctionAccountWidget::~FunctionAccountWidget()
{
    delete ui;
}
void FunctionAccountWidget::retranslator()
{
    ui->retranslateUi(this);
}
void FunctionAccountWidget::DefaultShow()
{
    AssetShowSlots();
}

void FunctionAccountWidget::AssetShowSlots()
{
    ui->pushButton_miner->setChecked(false);
    ui->pushButton_asset->setChecked(true);
    ui->pushButton_bonus->setChecked(false);

    emit showAccountSignal();
}

void FunctionAccountWidget::MinerShowSlots()
{
    ui->pushButton_miner->setChecked(true);
    ui->pushButton_asset->setChecked(false);
    ui->pushButton_bonus->setChecked(false);

    emit showMinerSignal();
}

void FunctionAccountWidget::BonusShowSlots()
{
    ui->pushButton_miner->setChecked(false);
    ui->pushButton_asset->setChecked(false);
    ui->pushButton_bonus->setChecked(true);

    emit showBonusSignal();
}

void FunctionAccountWidget::InitWidget()
{
    InitStyle();
    ui->pushButton_asset->setCheckable(true);
    ui->pushButton_miner->setCheckable(true);
    ui->pushButton_bonus->setCheckable(true);

    connect(ui->pushButton_asset,&QPushButton::clicked,this,&FunctionAccountWidget::AssetShowSlots);
    connect(ui->pushButton_miner,&QPushButton::clicked,this,&FunctionAccountWidget::MinerShowSlots);
    connect(ui->pushButton_bonus,&QPushButton::clicked,this,&FunctionAccountWidget::BonusShowSlots);
}

void FunctionAccountWidget::InitStyle()
{
    setStyleSheet(FUNCTIONBAR_PUSHBUTTON_STYLE );
}

void FunctionAccountWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QColor(19,32,80));
    painter.drawRect(QRect(0,0,130,480));

    painter.setPen(QColor(105,124,255));
    painter.drawLine(20,62,110,62);
}
