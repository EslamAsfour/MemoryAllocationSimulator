#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "External_Functions.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool CheckIsNumber(QString str);
    void SendMsgError(QString msg);
    void SendMsgInfo(QString msg);

    void Display();
    void RemoveAllDisplayed();
    void DisplayTable();
private slots:
    void on_pushButton_SubmitSize_clicked();

    void on_pushButton_AddHoleP1_clicked();

    void on_pushButton_To_P2_clicked();

    void on_NextButtonP2_clicked();

    void on_BestRadioBtn_clicked(bool checked);

    void on_BestRadioBtn_clicked();

    void on_FirstRadioBtn_clicked();

    void on_Seg_Submit_clicked();

    void on_DeAlloc_Btn_clicked();

private:
    Ui::MainWindow *ui;
    int TotalMemSize;
    QVector<QString> ProcessesName;

    int count;
    QString Type;
    QVector<QString> SegName;
    QVector<int> SegSize;

    //
    QVector<segment> Memory;
    QVector<int> InitHoleAddr;
    QVector<int>InitHoleSize;

    //
    QVector<QWidget*>ToBeDeleted;
};
#endif // MAINWINDOW_H
