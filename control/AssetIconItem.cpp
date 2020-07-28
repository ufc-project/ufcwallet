#include "AssetIconItem.h"
#include "ui_AssetIconItem.h"

#include "wallet.h"

//QMap<QString,QString> AssetIconItem::assetColorMap.insert("BTC","#F5A623");
QMap<QString,QString> AssetIconItem::assetColorMap = {{ASSET_NAME,"#4c5eda"}, {"BTC","#F5A623"}, {"LTC","#4A4A4A"}, {"ETH","#4f7795"}, {"UB","#38BDE9"},
                                                      {"HC","#5c4d93"},{"ERCPAX","#005120"},{"ERCELF","#2055b7"},{"USDT","#259F7A"},{"BCH",{"#f08a16"}}};

AssetIconItem::AssetIconItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssetIconItem)
{
    ui->setupUi(this);

    setBackgroundColor("white");
}

AssetIconItem::~AssetIconItem()
{
    delete ui;
}

void AssetIconItem::setAsset(QString assetSymbol)
{
//    QString assetColor = assetColorMap.value(assetSymbol);
//    ui->barLabel->setStyleSheet(QString("border-top-right-radius:3px;border-bottom-right-radius:3px;"
//                                        "background-color: %1;").arg(assetColor));

    ui->barLabel->setStyleSheet(QString("border-top-right-radius:3px;border-bottom-right-radius:3px;"
                                        "background-color: rgb(225,140,0);"));

    if(assetSymbol == ASSET_NAME)
    {
        ui->iconLabel->setStyleSheet(QString("border-image: url(:/ui/wallet_ui/coin_%1.png);").arg(assetSymbol));
    }
    else
    {
        ui->iconLabel->setStyleSheet(QString("background-image: url(:/ui/wallet_ui/coin_other.png);background-repeat: no-repeat;background-position: center;border-style: flat;"));
    }
    ui->assetLabel->setStyleSheet("QLabel{font: 11px \"Microsoft YaHei UI Light\";color:rgb(19,32,80);}");
    ui->assetLabel->setText(revertERCSymbol(assetSymbol));
}

void AssetIconItem::setBackgroundColor(QString color)
{
    setStyleSheet(QString("#widget{background-color:%1;}").arg(color));
}
