#include "CreateAssetDialog.h"
#include "ui_CreateAssetDialog.h"

#include "wallet.h"
#include "dialog/TransactionResultDialog.h"
#include "dialog/ErrorResultDialog.h"

CreateAssetDialog::CreateAssetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAssetDialog)
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

    QRegExp rx1("[a-zA-Z0-9]{0,8}");
    QRegExpValidator *pReg1 = new QRegExpValidator(rx1, this);
    ui->assetNameLineEdit->setValidator(pReg1);

    setSupplyValidator();

    init();
}

CreateAssetDialog::~CreateAssetDialog()
{
    delete ui;
}

void CreateAssetDialog::pop()
{
    move(0,0);
    exec();
}

void CreateAssetDialog::init()
{
    ui->accountComboBox->clear();
    QStringList accounts = HXChain::getInstance()->getMyFormalGuards();
    if(accounts.size() > 0)
    {
        ui->accountComboBox->addItems(accounts);
    }

    ui->accountComboBox->setCurrentText(HXChain::getInstance()->currentAccount);

    checkOkBtnEnabled();
}


void CreateAssetDialog::jsonDataUpdated(QString id)
{
    if( id == "CreateAssetDialog-wallet_create_asset")
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

void CreateAssetDialog::on_okBtn_clicked()
{
    QString maxSupply = ui->maxAmountLineEdit->text();
    QString precision  = ui->precisionSpinBox->text();

    if(maxSupply.toULongLong() <= 0 || ui->assetNameLineEdit->text().isEmpty())     return;

    HXChain::getInstance()->postRPC( "CreateAssetDialog-wallet_create_asset", toJsonFormat( "wallet_create_asset",
                                     QJsonArray() << ui->accountComboBox->currentText()
                                     << ui->assetNameLineEdit->text() << precision
                                     << maxSupply
                                     << true ));
}

void CreateAssetDialog::on_cancelBtn_clicked()
{
    close();
}

void CreateAssetDialog::on_closeBtn_clicked()
{
    close();
}

void CreateAssetDialog::setSupplyValidator()
{
    int precisionNum = ui->precisionSpinBox->text().toInt();

    QRegExp rx(QString("^([1-9][0-9]{0,%1})?$|(^\\t?$)").arg(17 - precisionNum));
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->maxAmountLineEdit->setValidator(validator);
}

void CreateAssetDialog::checkOkBtnEnabled()
{
    if(ui->maxAmountLineEdit->text().toULongLong() > 0 && ui->assetNameLineEdit->text().size() > 0 && !ui->accountComboBox->currentText().isEmpty())
    {
        ui->okBtn->setEnabled(true);
    }
    else
    {
        ui->okBtn->setEnabled(false);
    }
}

void CreateAssetDialog::on_precisionSpinBox_valueChanged(int arg1)
{
    ui->maxAmountLineEdit->clear();
    setSupplyValidator();
}

void CreateAssetDialog::on_assetNameLineEdit_textChanged(const QString &arg1)
{
    checkOkBtnEnabled();
}

void CreateAssetDialog::on_maxAmountLineEdit_textChanged(const QString &arg1)
{
    checkOkBtnEnabled();
}
