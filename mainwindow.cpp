#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->init->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_SubmitSize_clicked()
{
   QString Size =  ui->page->findChild<QLineEdit*>("Size_LineEdit")->text();
   if(Size != "")
   {
       if(CheckIsNumber(Size))
       {
           TotalMemSize = Size.toInt();
           //ui->page->findChild<QLineEdit*>("Size_LineEdit")->setEnabled(false);
           QString msg = "Total Memory Size Added Correctly with a Value = '" + Size + "'";
           SendMsgDone(msg);
           return ;
       }

   }
   //Empty or Not all Digits
   // Add Function to Send msg to user to reSubmit
   QString msg = "Wrone Input Please ReSubmit Your Input with an 'Integer'";
   SendMsgError(msg);
}

// Function to check is the str All digists
bool MainWindow::CheckIsNumber(QString str)
{
    foreach(QChar c , str)
    {
        if(!(c.isDigit()))
        {
            return false;
        }
    }
    return true;
}

void  MainWindow::SendMsgError(QString msg)
{
    QMessageBox::warning(this,"Error",msg);
}

void  MainWindow::SendMsgDone(QString msg)
{
    QMessageBox::information(this,"Input Added",msg);
}
