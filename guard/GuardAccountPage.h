#ifndef DIRECTORACCOUNTPAGE_H
#define DIRECTORACCOUNTPAGE_H

#include <QWidget>

namespace Ui {
class GuardAccountPage;
}

class GuardAccountPage : public QWidget
{
    Q_OBJECT

public:
    explicit GuardAccountPage(QWidget *parent = 0);
    ~GuardAccountPage();

    void init();

private slots:
    void on_accountComboBox_currentIndexChanged(const QString &arg1);

    void on_newSenatorBtn_clicked();

    void on_changeSenator_clicked();
private:
    Ui::GuardAccountPage *ui;

    void paintEvent(QPaintEvent*);
};

#endif // DIRECTORACCOUNTPAGE_H
