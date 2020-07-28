#ifndef CREATEDIRECTORDIALOG_H
#define CREATEDIRECTORDIALOG_H

#include <QDialog>

namespace Ui {
class CreateSenatorDialog;
}

class CreateSenatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateSenatorDialog(QWidget *parent = 0);
    ~CreateSenatorDialog();
signals:
    void CreateSenatorSuccess();
private slots:
    void jsonDataUpdated(QString id);

    void on_registerLabel_linkActivated(const QString &link);

    void CreateSenatorSlots();
private:
    void InitWidget();
    void InitData();
private:
    Ui::CreateSenatorDialog *ui;
};

#endif // CREATEDIRECTORDIALOG_H
