#ifndef CREATEASSETDIALOG_H
#define CREATEASSETDIALOG_H

#include <QDialog>

namespace Ui {
class CreateAssetDialog;
}

class CreateAssetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAssetDialog(QWidget *parent = nullptr);
    ~CreateAssetDialog();

    void pop();

    void init();


private slots:
    void jsonDataUpdated(QString id);

    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_closeBtn_clicked();

    void on_precisionSpinBox_valueChanged(int arg1);

    void on_assetNameLineEdit_textChanged(const QString &arg1);

    void on_maxAmountLineEdit_textChanged(const QString &arg1);

private:
    Ui::CreateAssetDialog *ui;

    void setSupplyValidator();
    void checkOkBtnEnabled();
};

#endif // CREATEASSETDIALOG_H
