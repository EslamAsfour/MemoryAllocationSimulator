#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TotalMemSize = 0 ;
    ui->init->setCurrentIndex(0);
    ui->page_2->findChild<QStackedWidget*>("Process_Input_Stacked_Wid")->setCurrentIndex(0);
    Type = "" ;
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
    {
        return false;
    }
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

      QString  Addr =  ui->page->findChild<QLineEdit*>("lineEdit_StartAddP1")->text();
      QString  Size =  ui->page->findChild<QLineEdit*>("lineEdit_SizeP1")->text();

      //Name is not empty  And  Addr and Size are All Digits
      if( CheckIsNumber(Addr) && CheckIsNumber(Size))
      {
          // Add Hole to the vector for the first Function to use     "add_holes"
          InitHoleAddr.push_back(Addr.toInt());
          InitHoleSize.push_back(Size.toInt());
          // Clear LineEdit Fields

          ui->page->findChild<QLineEdit*>("lineEdit_StartAddP1")->setText("");
          ui->page->findChild<QLineEdit*>("lineEdit_SizeP1")->setText("");
          //Confirmation msg
          QString msg = " Starting Address = ' "+ Addr + " ' \n Size = ' "+ Size + " '";
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
        add_holes(Memory,InitHoleAddr,InitHoleSize,TotalMemSize);
        Display();
        ui->init->setCurrentIndex(1);
    }
    QString msg = "Please Atleast Enter the Size of the memory";
    SendMsgError(msg);
}


void MainWindow::Display()
{
    for(int i = 0 ; i < Memory.length() ; i++)
    {
        auto wid = new QWidget();
        auto box = new QHBoxLayout(wid);
        box->setMargin(0);
        wid->setContentsMargins(0,0,0,0);
        int height = (Memory[i].size * 450)/TotalMemSize;
        QString lab = Memory[i].parent + "\n" + Memory[i].name;
        QString style = "color : white; height :" + QString::number(height) +"px; width : 170px; font-size : 15px; font : bold ;";

        if(Memory[i].hole == false)
        {
           style += " background-image : url(:/img2/Gray.jpg);background-position: top ;";

            // "background-color:  rgb(50,205,50);color : rgb(255, 255, 255);border: 2px solid white;border-radius: 4px;";
        }
        else
        {
            style += "background-color:  rgb(50,205,50);";

        }

        // Add Button and label
        auto btn = new QPushButton(lab);
        btn->setStyleSheet(style);
        auto MemAddr = new QLabel(QString::number(Memory[i].address));
        MemAddr->setStyleSheet("qproperty-alignment: 'AlignTop';");
        box->addWidget(MemAddr);
        box->addWidget(btn);
        box->setAlignment(Qt::AlignTop);


        // Widget to set Width and Height


       ui->ButtonsBar_2->findChild<QVBoxLayout*>("VertMemo")->addWidget(wid,0);

    }
}

void MainWindow::DisplayTable()
{
    QTableWidgetItem *Proc= new QTableWidgetItem ("Hosam");
    QTableWidgetItem *Seg= new QTableWidgetItem ("Hosam");
    QTableWidgetItem *Add= new QTableWidgetItem ("Hosam");
    QTableWidgetItem *Size= new QTableWidgetItem ("Hosam");

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int row = ui->tableWidget->rowCount()-1;
    ui->tableWidget->setItem(row,0,Proc);
    ui->tableWidget->setItem(row,1,Seg);
    ui->tableWidget->setItem(row,2,Add);
    ui->tableWidget->setItem(row,3,Size);

}


// Check Process name and number of segment then Go to next page
void MainWindow::on_NextButtonP2_clicked()
{
    auto PName = ui->page_3->findChild<QLineEdit*>("PName")->text();
    auto NumSeg = ui->page_3->findChild<QLineEdit*>("NumSeg")->text();
    //Empty Input
    if(PName == "" || NumSeg == ""  )
    {
        QString msg = "Please Fill All Input Fields";
        SendMsgError(msg);
        return ;               // To Terminate the Function
    }
    if(!CheckIsNumber(NumSeg))
    {
         QString msg = "Wronge input for Number Of Segments";
         ui->page_3->findChild<QLineEdit*>("NumSeg")->setText("");
         SendMsgError(msg);
         return ;               // To Terminate the Function
    }
    if(Type == "")
    {
         QString msg = "Please Choose the method of Allocation";
         SendMsgError(msg);
         return ;
    }

    ProcessesName.push_back(PName);
    count = NumSeg.toInt();
    ui->page_4->findChild<QLineEdit*>("ShowCount")->setText(QString::number(count));
    ui->page_2->findChild<QStackedWidget*>("Process_Input_Stacked_Wid")->setCurrentIndex(1);

}









void MainWindow::on_BestRadioBtn_clicked()
{
    Type = "Best-Fit";
    qDebug() << Type;
}

void MainWindow::on_FirstRadioBtn_clicked()
{
    Type = "First-Fit";
    qDebug() << Type;
}

//Check Seg name and size
void MainWindow::on_Seg_Submit_clicked()
{
    auto SegName = ui->page_4->findChild<QLineEdit*>("SegName_LineEdit")->text();
    auto SegSize = ui->page_4->findChild<QLineEdit*>("SegSize_LineEdit")->text();

    // Submited All the segment so we return to Process page

    // Empty Inputs
    if(SegName == "" || SegSize == "" )
    {
        QString msg = "Please Fill All Input Fields";
        SendMsgError(msg);
        return ;               // To Terminate the Function
    }
     qDebug() << SegSize;
      qDebug() << CheckIsNumber(SegSize);
    //SegSize is not a number
    if(!CheckIsNumber(SegSize))
    {
        QString msg = "Wronge input for Segment Size";
        ui->page_4->findChild<QLineEdit*>("SegSize_LineEdit")->setText("");
        SendMsgError(msg);
        return ;               // To Terminate the Function
    }

    count--;
    SegName.push_back(SegName);
    SegSize.push_back(SegSize.toInt());


    ui->page_4->findChild<QLineEdit*>("ShowCount")->setText(QString::number(count));

    if(count == 0)
    {
        ui->page_2->findChild<QStackedWidget*>("Process_Input_Stacked_Wid")->setCurrentIndex(0);
    }
}
