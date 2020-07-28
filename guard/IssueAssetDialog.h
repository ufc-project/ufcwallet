#ifndef ISSUEASSETDIALOG_H
#define ISSUEASSETDIALOG_H

#include <QDialog>

namespace Ui {
class IssueAssetDialog;
}

class IssueAssetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IssueAssetDialog(QString _symbol, QWidget *parent = nullptr);
    ~IssueAssetDialog();

    void pop();

    void init();

private slots:
    void jsonDataUpdated(QString id);

    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_closeBtn_clicked();


private:
    Ui::IssueAssetDialog *ui;
    QString symbol;

    void checkOkBtnEnabled();
};

#endif // ISSUEASSETDIALOG_H
