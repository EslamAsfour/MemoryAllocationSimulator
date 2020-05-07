#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TotalMemSize = 0 ;
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
       // next line commented so the user can reSubmit the Size multiple Times
        // ui->page->findChild<QLineEdit*>("Size_LineEdit")->setEnabled(false);
           QString msg = "Total Memory Size Added Correctly with a Value = '" + Size + "'";
           SendMsgInfo(msg);
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
    if(str.size() == 0)
        return false;
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

void  MainWindow::SendMsgInfo(QString msg)
{
    QMessageBox::information(this,"Input Added",msg);
}

// Button to add hole
void MainWindow::on_pushButton_AddHoleP1_clicked()
{
      QString  name =  ui->page->findChild<QLineEdit*>("lineEdit_HoleNameP1")->text();
      QString  Addr =  ui->page->findChild<QLineEdit*>("lineEdit_StartAddP1")->text();
      QString  Size =  ui->page->findChild<QLineEdit*>("lineEdit_SizeP1")->text();

      //Name is not empty  And  Addr and Size are All Digits
      if(name != "" && CheckIsNumber(Addr) && CheckIsNumber(Size))
      {
          // Add The Hole to the DS we Are using                 <<<<<<<<<<<<<<<<<<<-----
          // --------------------------------

          // Clear LineEdit Fields
          ui->page->findChild<QLineEdit*>("lineEdit_HoleNameP1")->setText("");
          ui->page->findChild<QLineEdit*>("lineEdit_StartAddP1")->setText("");
          ui->page->findChild<QLineEdit*>("lineEdit_SizeP1")->setText("");
          //Confirmation msg
          QString msg = "Hole Added with \n Name =' "+ name +" ' \n Starting Address = ' "+ Addr + " ' \n Size = ' "+ Size + " '";
          SendMsgInfo(msg);
          // To terminate the Function
          return ;
      }
       // Wrong Input
       QString msg  = "Wrong input please make sure you added all the needed inputs and the Address and the size are all Digits";
       SendMsgError(msg);
}




void MainWindow::on_pushButton_To_P2_clicked()
{
    if(TotalMemSize != 0)
    {
        ui->init->setCurrentIndex(1);
    }
    QString msg = "Please Atleast Enter the Size of the memory";
    SendMsgError(msg);
}


void MainWindow::Display()
{
    auto wid = new QWidget();
    auto box = new QHBoxLayout(wid);
    box->setMargin(0);
    wid->setContentsMargins(0,0,0,0);

    // Add Button and label
    auto btn = new QPushButton("GAP");
    btn->setStyleSheet("color : blue; height : 60px; width : 170px; font-size : 12px; font : bold  ");
    auto MemAddr = new QLabel(QString::number(100022000));
    MemAddr->setStyleSheet("qproperty-alignment: 'AlignTop';");
    box->addWidget(MemAddr);
    box->addWidget(btn);
    box->setAlignment(Qt::AlignTop);


    // Widget to set Width and Height


   ui->ButtonsBar_2->findChild<QVBoxLayout*>("VertMemo")->addWidget(wid,0);


}


void MainWindow::on_NextButtonP2_clicked()
{
    Display();
}
