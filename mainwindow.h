#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
private slots:
    void on_pushButton_SubmitSize_clicked();

    void on_pushButton_AddHoleP1_clicked();

    void on_pushButton_To_P2_clicked();

    void on_NextButtonP2_clicked();

private:
    Ui::MainWindow *ui;
    int TotalMemSize;
};
#endif // MAINWINDOW_H
