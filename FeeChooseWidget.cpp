﻿#include "FeeChooseWidget.h"
#include "ui_FeeChooseWidget.h"

#include <algorithm>
#include <mutex>
#include "poundage/PoundageDataUtil.h"


class FeeChooseWidget::DataPrivate
{
public:
    DataPrivate(double number,const QString &type,const QString &account)
        :feeNumber(number),feeType(type.isEmpty()?ASSET_NAME:type),accountName(account)
    {

    }
public:
    double feeNumber;

    double coinNumber;
    QString feeType;

    QString poundageID;

    QString poundageTip;

    std::mutex mutex;

    QString accountName;
    std::map<QString,double> accountAssets;
};

FeeChooseWidget::FeeChooseWidget(double feeNumber,const QString &coinType,const QString &accountName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeeChooseWidget),
    _p(new DataPrivate(feeNumber,coinType,accountName))
{
    ui->setupUi(this);
    qDebug()<<accountName;
    InitWidget();
}

FeeChooseWidget::~FeeChooseWidget()
{
    delete _p;
    delete ui;
}

const QString &FeeChooseWidget::GetFeeID() const
{
    return _p->poundageID;
}

const QString &FeeChooseWidget::GetFeeType() const
{

    return _p->feeType;
}

QString FeeChooseWidget::GetFeeNumber() const
{
    int pre = 5;
    foreach(AssetInfo asset,HXChain::getInstance()->assetInfoMap){
        if(asset.symbol == _p->feeType)
        {
            pre = asset.precision;
            break;
        }
    }
    return QString::number(_p->coinNumber,'f',pre);
}

bool FeeChooseWidget::isSufficient() const
{
    return !ui->tipLabel->isVisible();
}

void FeeChooseWidget::setBalance(AssetAmountMap _balance)
{
    foreach (AssetAmount aa, _balance)
    {
        AssetInfo assetInfo = HXChain::getInstance()->assetInfoMap.value(aa.assetId);
        _p->accountAssets[assetInfo.symbol] = _balance.value(aa.assetId).amount / pow(10.,assetInfo.precision);
    }

    checkAccountBalance();
}

void FeeChooseWidget::updateFeeNumberSlots(double feeNumber)
{
    _p->feeNumber = std::max<double>(0,feeNumber);
    feeTypeChanged();
}

void FeeChooseWidget::jsonDataUpdated(QString id)
{
    if("feechoose_list_guarantee_order" == id)
    {
        std::lock_guard<std::mutex> lock(_p->mutex);
        //转化为结构体
        QString result = HXChain::getInstance()->jsonDataValue( id);
        result.prepend("{");
        result.append("}");

        std::shared_ptr<PoundageSheet> allPoundageSheet = std::make_shared<PoundageSheet>();
        PoundageDataUtil::convertJsonToPoundage(result,allPoundageSheet);
        std::shared_ptr<PoundageUnit> unit = nullptr;
        if(!allPoundageSheet->poundages.empty())
        {
            allPoundageSheet->sortByRate(false);

            for(auto it = allPoundageSheet->poundages.begin();it != allPoundageSheet->poundages.end();++it)
            {
                if(_p->feeNumber <= (*it)->calSourceLeftNumber())
                {
                    unit = *it;
                    break;
                }
            }
        }
        //解析交易
        ParsePoundage(unit);
        refreshUI();
    }

}


void FeeChooseWidget::feeTypeChanged()
{

    _p->poundageID = "";
    _p->coinNumber = _p->feeNumber;
    _p->feeType = ASSET_NAME;
    refreshUI();
}

void FeeChooseWidget::QueryPoundage(const QString &type)
{
    HXChain::getInstance()->postRPC("feechoose_list_guarantee_order",
                                    toJsonFormat("list_guarantee_order",
                                                 QJsonArray()<<type<<false
                                                 )
                                    );
}

void FeeChooseWidget::updatePoundageID()
{
    qDebug()<<"poundageID---"<<_p->poundageID;
    _p->poundageID.isEmpty()?HXChain::getInstance()->postRPC( "feechoose_remove_guarantee_id",
                                                              toJsonFormat( "remove_guarantee_id",
                                                                            QJsonArray())):
                             HXChain::getInstance()->postRPC( "feechoose_set_guarantee_id",
                                                              toJsonFormat( "set_guarantee_id",
                                                       QJsonArray() << _p->poundageID ));

}

void FeeChooseWidget::updateAccountNameSlots(const QString &accountName,bool refreshTip)
{
    _p->accountName = accountName;
    ResetAccountBalance();
    if(refreshTip)
    {
        checkAccountBalance();
    }
}

void FeeChooseWidget::ParsePoundage(const std::shared_ptr<PoundageUnit> &poundage)
{
    if(poundage == nullptr)
    {
        _p->feeType = ASSET_NAME;
        _p->coinNumber = _p->feeNumber;
        _p->poundageID = "";
        _p->poundageTip = tr("cannot find proper acceptance!");
    }
    else
    {
        _p->feeType = poundage->chainType;
        _p->coinNumber = poundage->targetCoinNumber/poundage->sourceCoinNumber*_p->feeNumber;
        _p->poundageID = poundage->poundageID;
        double rate = poundage->sourceCoinNumber/poundage->targetCoinNumber;
        int pre = ASSET_PRECISION;
        foreach(AssetInfo asset,HXChain::getInstance()->assetInfoMap){
            if(asset.symbol == _p->feeType)
            {
                pre = asset.precision;
                break;
            }
        }
        _p->poundageTip = tr("pay:") + QString::number(_p->coinNumber,'f',pre) + " " + revertERCSymbol( _p->feeType) + tr("  rate: 1:") + QString::number(rate,'f',ASSET_PRECISION);

    }
}

void FeeChooseWidget::refreshUI()
{
    //检查账户余额
    if(!checkAccountBalance())
    {
        //提示余额不足
    }




    ui->line_6->setVisible(false);
    if(QVBoxLayout* vLay = dynamic_cast<QVBoxLayout*>(layout()))
    {
        vLay->setStretch(5,1);
    }


    //ui->label_fee->setText(QString::number(_p->coinNumber) + " " + _p->feeType);
    ui->label_fee->setText(QString::number(_p->feeNumber,'f',5)+" " ASSET_NAME);

    updatePoundageID();
}

bool FeeChooseWidget::checkAccountBalance()
{
    ui->tipLabel->setVisible(false);
    if(_p->accountName.isEmpty())
    {
        emit feeSufficient(false);
        return true;
    }
    //当前承兑单币种+金额  与 账户中对应资产比较
    qDebug() <<_p->coinNumber <<_p->feeType<< _p->accountAssets[_p->feeType] <<_p->accountAssets.size();
    if(_p->coinNumber > _p->accountAssets[_p->feeType])
    {
        int pre = 5;
        foreach(AssetInfo asset,HXChain::getInstance()->assetInfoMap){
            if(asset.symbol == _p->feeType)
            {
                pre = asset.precision;
                break;
            }
        }

        ui->tipLabel->setText(_p->feeType+tr(" less than ")+QString::number(_p->coinNumber,'f',pre));
        ui->tipLabel->setVisible(true);
        emit feeSufficient(false);
        return false;
    }
    else
    {
        ui->tipLabel->setVisible(false);
        emit feeSufficient(true);
        return true;
    }

}

void FeeChooseWidget::ResetAccountBalance()
{
    _p->accountAssets.clear();

    AccountInfo info = HXChain::getInstance()->accountInfoMap.value(_p->accountName);

    AssetAmountMap map = info.assetAmountMap;
    QStringList keys = HXChain::getInstance()->assetInfoMap.keys();

    for(int i = 0;i < keys.size();++i)
    {
        QString assetId = keys.at(i);
        AssetInfo assetInfo = HXChain::getInstance()->assetInfoMap.value(assetId);

        _p->accountAssets[assetInfo.symbol] = map.value(assetId).amount/pow(10.,assetInfo.precision);
        qDebug()<<assetInfo.symbol<<_p->accountAssets[assetInfo.symbol];
    }

}


void FeeChooseWidget::InitWidget()
{
    InitStyle();
    ResetAccountBalance();


    connect( HXChain::getInstance(), &HXChain::jsonDataUpdated, this, &FeeChooseWidget::jsonDataUpdated);

    feeTypeChanged();
}

void FeeChooseWidget::InitStyle()
{
    QFont font("\"Microsoft YaHei UI Light\"",9,50);
    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(83,61,138));

    ui->label_fee->setPalette(pa);
    ui->label_fee->setFont(font);

}
