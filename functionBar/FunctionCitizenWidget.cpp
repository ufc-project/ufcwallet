#include "FunctionCitizenWidget.h"
#include "ui_FunctionCitizenWidget.h"

#include "wallet.h"

FunctionCitizenWidget::FunctionCitizenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionCitizenWidget)
{
    ui->setupUi(this);
    InitWidget();
}

FunctionCitizenWidget::~FunctionCitizenWidget()
{
    delete ui;
}

void FunctionCitizenWidget::retranslator()
{
    ui->retranslateUi(this);
}

void FunctionCitizenWidget::DefaultShow()
{
    on_accountInfoBtn_clicked();
}

void FunctionCitizenWidget::InitWidget()
{
    InitStyle();
    ui->accountInfoBtn->setCheckable(true);
    ui->proposalBtn->setCheckable(true);

    ui->proposalBtn->hide();
}

void FunctionCitizenWidget::InitStyle()
{
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(84,116,235));
    setPalette(palette);

    setStyleSheet(FUNCTIONBAR_PUSHBUTTON_STYLE);
}

void FunctionCitizenWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QColor(19,32,80));
    painter.drawRect(QRect(0,0,130,480));

    painter.setPen(QColor(105,124,255));
    painter.drawLine(20,62,110,62);
}


void FunctionCitizenWidget::on_accountInfoBtn_clicked()
{
    ui->accountInfoBtn->setChecked(true);
    ui->proposalBtn->setChecked(false);
    showCitizenAccountSignal();
}

void FunctionCitizenWidget::on_proposalBtn_clicked()
{
    ui->accountInfoBtn->setChecked(false);
    ui->proposalBtn->setChecked(true);
    showCitizenProposalSignal();
}
