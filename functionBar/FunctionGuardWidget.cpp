#include "FunctionGuardWidget.h"
#include "ui_FunctionGuardWidget.h"

#include "extra/style.h"
#include <QPainter>

FunctionGuardWidget::FunctionGuardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionGuardWidget)
{
    ui->setupUi(this);

    InitWidget();
}

FunctionGuardWidget::~FunctionGuardWidget()
{
    delete ui;
}

void FunctionGuardWidget::retranslator()
{
    ui->retranslateUi(this);
}

void FunctionGuardWidget::DefaultShow()
{
    on_accountInfoBtn_clicked();
}

void FunctionGuardWidget::InitWidget()
{
    InitStyle();
    ui->accountInfoBtn->setCheckable(true);
    ui->myIncomeBtn->setCheckable(true);
    ui->issueAssetBtn->setCheckable(true);
    ui->proposalBtn->setCheckable(true);
    ui->feedPriceBtn->setCheckable(true);

}

void FunctionGuardWidget::InitStyle()
{
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(84,116,235));
    setPalette(palette);

    setStyleSheet(FUNCTIONBAR_PUSHBUTTON_STYLE);
}

void FunctionGuardWidget::on_accountInfoBtn_clicked()
{
    ui->accountInfoBtn->setChecked(true);
    ui->myIncomeBtn->setChecked(false);
    ui->issueAssetBtn->setChecked(false);
    ui->proposalBtn->setChecked(false);
    ui->feedPriceBtn->setChecked(false);
    showGuardAccountSignal();
}


void FunctionGuardWidget::on_myIncomeBtn_clicked()
{
    ui->accountInfoBtn->setChecked(false);
    ui->myIncomeBtn->setChecked(true);
    ui->issueAssetBtn->setChecked(false);
    ui->proposalBtn->setChecked(false);
    ui->feedPriceBtn->setChecked(false);
    showGuardIncomeSignal();
}


void FunctionGuardWidget::on_issueAssetBtn_clicked()
{
    ui->accountInfoBtn->setChecked(false);
    ui->myIncomeBtn->setChecked(false);
    ui->issueAssetBtn->setChecked(true);
    ui->proposalBtn->setChecked(false);
    ui->feedPriceBtn->setChecked(false);
    showIssueAssetSignal();
}

void FunctionGuardWidget::on_proposalBtn_clicked()
{
    ui->accountInfoBtn->setChecked(false);
    ui->myIncomeBtn->setChecked(false);
    ui->issueAssetBtn->setChecked(false);
    ui->proposalBtn->setChecked(true);
    ui->feedPriceBtn->setChecked(false);
    showProposalSignal();
}


void FunctionGuardWidget::on_feedPriceBtn_clicked()
{
    ui->accountInfoBtn->setChecked(false);
    ui->myIncomeBtn->setChecked(false);
    ui->issueAssetBtn->setChecked(false);
    ui->proposalBtn->setChecked(false);
    ui->feedPriceBtn->setChecked(true);
    showFeedPriceSignal();
}


void FunctionGuardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QColor(19,32,80));
    painter.drawRect(QRect(0,0,130,480));

    painter.setPen(QColor(105,124,255));
    painter.drawLine(20,62,110,62);
    painter.drawLine(20,222,110,222);
}





