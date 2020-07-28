#ifndef FUNCTIONDIRECTORWIDGET_H
#define FUNCTIONDIRECTORWIDGET_H

#include <QWidget>

namespace Ui {
class FunctionGuardWidget;
}

class FunctionGuardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionGuardWidget(QWidget *parent = 0);
    ~FunctionGuardWidget();
    void retranslator();
public slots:
    void DefaultShow();
private:
    void InitWidget();
    void InitStyle();

signals:
    void showGuardAccountSignal();
    void showGuardIncomeSignal();
    void showLockContractSignal();
    void showIssueAssetSignal();
    void showProposalSignal();
    void showFeedPriceSignal();

private slots:
    void on_accountInfoBtn_clicked();

    void on_myIncomeBtn_clicked();

    void on_issueAssetBtn_clicked();

    void on_proposalBtn_clicked();

    void on_feedPriceBtn_clicked();



private:
    Ui::FunctionGuardWidget *ui;

    void paintEvent(QPaintEvent*);
};

#endif // FUNCTIONDIRECTORWIDGET_H
