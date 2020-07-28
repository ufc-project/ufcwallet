#ifndef ISSUEASSETPAGE_H
#define ISSUEASSETPAGE_H

#include <QWidget>

namespace Ui {
class IssueAssetPage;
}

class IssueAssetPage : public QWidget
{
    Q_OBJECT

public:
    explicit IssueAssetPage(QWidget *parent = nullptr);
    ~IssueAssetPage();

    void init();
    void refresh();

private slots:
    void jsonDataUpdated(QString id);

    void onAccountComboBoxCurrentIndexChanged(const QString &arg1);

    void on_assetIssuerTableWidget_cellClicked(int row, int column);

    void on_createAssetBtn_clicked();

private:
    Ui::IssueAssetPage *ui;

    void showAssetIssuer();
    void paintEvent(QPaintEvent*);
};

#endif // ISSUEASSETPAGE_H
