#include "IssueAssetDialog.h"
#include "ui_IssueAssetDialog.h"

#include "wallet.h"
#include "dialog/TransactionResultDialog.h"
#include "dialog/ErrorResultDialog.h"

IssueAssetDialog::IssueAssetDialog(QString _symbol, QWidget *parent) :
    QDialog(parent),
    symbol(_symbol),
    ui(new Ui::IssueAssetDialog)
{
    ui->setupUi(this);

    connect( HXChain::getInstance(), SIGNAL(jsonDataUpdated(QString)), this, SLOT(jsonDataUpdated(QString)));

    setParent(HXChain::getInstance()->mainFrame);

    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->widget->setObjectName("widget");
    ui->widget->setStyleSheet(BACKGROUNDWIDGET_STYLE);
    ui->containerWidget->setObjectName("containerwidget");
    ui->containerWidget->setStyleSheet(CONTAINERWIDGET_STYLE);

    ui->okBtn->setStyleSheet(OKBTN_STYLE);
    ui->cancelBtn->setStyleSheet(CANCELBTN_STYLE);
    ui->closeBtn->setStyleSheet(CLOSEBTN_STYLE);

    init();
}

IssueAssetDialog::~IssueAssetDialog()
{
    delete ui;
}

void IssueAssetDialog::pop()
{
    move(0,0);
    exec();
}

void IssueAssetDialog::init()
{
    AssetInfo info = HXChain::getInstance()->assetInfoMap.value(HXChain::getInstance()->getAssetId(symbol));
    QString availableStr = getBigNumberString( info.maxSupply - info.currentSupply, info.precision);
    ui->availableLabel->setText(availableStr + " " + info.symbol);

    QRegExp rx(QString("^([1-9][0-9]{0,%1})?$|(^\\t?$)").arg(17 - info.precision));
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->amountLineEdit->setValidator(validator);


//    ui->toAccountLineEdit->setReadOnly(true);
    ui->toAccountLineEdit->setText(HXChain::getInstance()->guardAccountIdToName(info.issuer));
}

void IssueAssetDialog::jsonDataUpdated(QString id)
{
    if( id == "IssueAssetDialog-issue_asset")
    {
        QString result = HXChain::getInstance()->jsonDataValue(id);
        qDebug() << id << result;

        if(result.startsWith("\"result\":"))
        {
            HXChain::getInstance()->postRPC( "id-list_assets", toJsonFormat( "list_assets", QJsonArray() << "A" << "100"));

            TransactionResultDialog transactionResultDialog;
            transactionResultDialog.setInfoText(tr("Transaction of issuing asset has been sent out!"));
            transactionResultDialog.setDetailText(result);
            transactionResultDialog.pop();

            close();
        }
        else if(result.startsWith("\"error\":"))
        {
            ErrorResultDialog errorResultDialog;
            errorResultDialog.setInfoText(tr("Issuing asset failed!"));
            errorResultDialog.setDetailText(result);
            errorResultDialog.pop();
        }
        return;
    }
}

void IssueAssetDialog::on_okBtn_clicked()
{
    if(ui->amountLineEdit->text().toDouble() <= 0 || ui->toAccountLineEdit->text().isEmpty())     return;

    HXChain::getInstance()->postRPC( "IssueAssetDialog-issue_asset", toJsonFormat( "issue_asset",
                                     QJsonArray() << ui->toAccountLineEdit->text()
                                     << ui->amountLineEdit->text() << symbol
                                     << ""
                                     << true ));
}

void IssueAssetDialog::on_cancelBtn_clicked()
{
    close();
}

void IssueAssetDialog::on_closeBtn_clicked()
{
    close();
}

