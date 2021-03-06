#include "IssueAssetPage.h"
#include "ui_IssueAssetPage.h"

#include "wallet.h"
#include "control/AssetIconItem.h"
#include "ToolButtonWidget.h"
#include "CreateAssetDialog.h"
#include "IssueAssetDialog.h"

IssueAssetPage::IssueAssetPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IssueAssetPage)
{
    ui->setupUi(this);

    connect( HXChain::getInstance(), SIGNAL(jsonDataUpdated(QString)), this, SLOT(jsonDataUpdated(QString)));

    ui->assetIssuerTableWidget->installEventFilter(this);
    ui->assetIssuerTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->assetIssuerTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->assetIssuerTableWidget->setFocusPolicy(Qt::NoFocus);
//    ui->assetIssuerTableWidget->setFrameShape(QFrame::NoFrame);
    ui->assetIssuerTableWidget->setMouseTracking(true);
    ui->assetIssuerTableWidget->setShowGrid(false);//隐藏表格线

    ui->assetIssuerTableWidget->horizontalHeader()->setSectionsClickable(true);
//    ui->assetIssuerTableWidget->horizontalHeader()->setFixedHeight(40);
    ui->assetIssuerTableWidget->horizontalHeader()->setVisible(true);
    ui->assetIssuerTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui->assetIssuerTableWidget->setColumnWidth(0,160);
    ui->assetIssuerTableWidget->setColumnWidth(1,110);
    ui->assetIssuerTableWidget->setColumnWidth(2,130);
    ui->assetIssuerTableWidget->setColumnWidth(3,130);
    ui->assetIssuerTableWidget->setColumnWidth(4,100);
    ui->assetIssuerTableWidget->setStyleSheet(TABLEWIDGET_STYLE_1);

    ui->createAssetBtn->setStyleSheet(TOOLBUTTON_STYLE_1);

    init();
}

IssueAssetPage::~IssueAssetPage()
{
    delete ui;
}

void IssueAssetPage::init()
{
    ui->accountComboBox->clear();
    QStringList accounts = HXChain::getInstance()->getMyFormalGuards();
    if(accounts.size() > 0)
    {
        ui->accountComboBox->addItems(accounts);
        if(accounts.contains(HXChain::getInstance()->currentAccount))
        {
            ui->accountComboBox->setCurrentText(HXChain::getInstance()->currentAccount);
        }
        onAccountComboBoxCurrentIndexChanged(ui->accountComboBox->currentText());
        connect(ui->accountComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onAccountComboBoxCurrentIndexChanged(const QString &)));
    }
    else
    {
        ui->label->hide();
        ui->accountComboBox->hide();

        QLabel* label = new QLabel(this);
        label->setGeometry(QRect(ui->label->pos(), QSize(300,18)));
        label->setText(tr("There are no director accounts in the wallet."));
    }

    ui->createAssetBtn->setVisible(accounts.size() > 0);

    HXChain::getInstance()->mainFrame->installBlurEffect(ui->assetIssuerTableWidget);

}

void IssueAssetPage::refresh()
{
    showAssetIssuer();
}

void IssueAssetPage::jsonDataUpdated(QString id)
{

}

void IssueAssetPage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(243,245,250),Qt::SolidLine));
    painter.setBrush(QBrush(QColor(243,245,250),Qt::SolidPattern));

    painter.drawRect(rect());
}

void IssueAssetPage::onAccountComboBoxCurrentIndexChanged(const QString &arg1)
{
    HXChain::getInstance()->currentAccount = ui->accountComboBox->currentText();
    showAssetIssuer();
}

void IssueAssetPage::showAssetIssuer()
{
    QStringList keys = HXChain::getInstance()->assetInfoMap.keys();
    ui->assetIssuerTableWidget->setRowCount(0);
    ui->assetIssuerTableWidget->setRowCount(keys.size());

    for(int i = 0; i < keys.size(); i++)
    {
        AssetInfo info = HXChain::getInstance()->assetInfoMap.value( keys.at(i));

        ui->assetIssuerTableWidget->setRowHeight(i,40);
        ui->assetIssuerTableWidget->setItem(i, 0, new QTableWidgetItem(info.symbol));
        AssetIconItem* assetIconItem = new AssetIconItem();
        assetIconItem->setAsset(ui->assetIssuerTableWidget->item(i,0)->text());
        ui->assetIssuerTableWidget->setCellWidget(i, 0, assetIconItem);

        QString issuer = HXChain::getInstance()->guardAccountIdToName(info.issuer);
        ui->assetIssuerTableWidget->setItem(i, 1, new QTableWidgetItem( issuer));
        ui->assetIssuerTableWidget->setItem(i, 2, new QTableWidgetItem( getBigNumberString(info.currentSupply, info.precision)));
        ui->assetIssuerTableWidget->setItem(i, 3, new QTableWidgetItem( getBigNumberString(info.maxSupply, info.precision)));

        ui->assetIssuerTableWidget->setItem(i, 4, new QTableWidgetItem(tr("issue")));
        ToolButtonWidget *toolButton = new ToolButtonWidget(this);
        toolButton->setText(ui->assetIssuerTableWidget->item(i,4)->text());
        toolButton->setEnabled( (!ui->accountComboBox->currentText().isEmpty()) && (ui->accountComboBox->currentText() == HXChain::getInstance()->guardAccountIdToName(info.issuer)));
        ui->assetIssuerTableWidget->setCellWidget(i,4,toolButton);
        connect(toolButton,&ToolButtonWidget::clicked,std::bind(&IssueAssetPage::on_assetIssuerTableWidget_cellClicked,this,i,4));

        if(info.symbol == ASSET_NAME)   ui->assetIssuerTableWidget->setRowHidden(i,true);

    }

    tableWidgetSetItemZebraColor(ui->assetIssuerTableWidget);

}

void IssueAssetPage::on_assetIssuerTableWidget_cellClicked(int row, int column)
{
    if(column == 4)
    {
        if(ui->assetIssuerTableWidget->item(row,0) != nullptr)
        {
            IssueAssetDialog issueAssetDialog(ui->assetIssuerTableWidget->item(row,0)->text());
            issueAssetDialog.pop();
            refresh();
        }
        return;
    }
}

void IssueAssetPage::on_createAssetBtn_clicked()
{
    CreateAssetDialog createAssetDialog;
    createAssetDialog.pop();
    refresh();
}
