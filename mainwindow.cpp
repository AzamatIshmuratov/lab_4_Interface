#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <clocale>

using namespace std;

char* filename = "dbase.txt";
enum Action { INSERT, DEL, INFO };
enum Dir { LEFT, RIGHT };
const int l_time = 20, l_type = 40, l_number = 12;
struct Fine {//---------------Штраф (элемент списка)
char time[l_time];//Время нарушения
char type[l_type];//Вид нарушения
float price;//Размер штрафа
Fine* next;//Указатель на следующий элемент
};

struct Node {//-----------------Узел дерева
char number[l_number];//Номер автомобиля
Fine* beg;//Указатель на начало списка нарушений
Node* left;//Указатель на левое поддерево
Node* right;//Указатель на правое поддерево
};

struct Data {//-----------------Исходные данные
char number[l_number];//Номер автомобиля
char time[l_time];//Время нарушения
char type[l_type];//Вид нарушения
float price;//Размер штрафа
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_exit_clicked()
{
    QMessageBox::StandardButton reply=QMessageBox::question(this,"Выход","Выйти?", QMessageBox::Yes| QMessageBox::No);
        if(reply==QMessageBox::Yes){
            QApplication::quit();
        }
}

void MainWindow::on_out_clicked()
{
    ifstream f( filename, ios::in);
    string nom,dt,vrem,tp,no;
    //int no;//номер авто, дата, время, тип нарушения, знак равно
    float razz; int i=1;
    if(!(f>>nom)){
         ui->textBrowser->append("\nНет данных\n");
         goto label1;
    }
    while(1){
         f>>dt>>vrem>>tp>>razz>>no;
         QString nom1= QString::fromLocal8Bit(nom.c_str());
         QString dt1= QString::fromLocal8Bit(dt.c_str());
         QString vrem1= QString::fromLocal8Bit(vrem.c_str());
         QString tp1= QString::fromLocal8Bit(tp.c_str());
         ui->textBrowser->append("Номер автомобиля: ");
         ui->textBrowser->insertPlainText(nom1); ui->textBrowser->append("Дата нарушения: ");
         ui->textBrowser->insertPlainText(dt1); ui->textBrowser->append("Время: ");
         ui->textBrowser->insertPlainText(vrem1); ui->textBrowser->append("Тип нарушения: ");
         ui->textBrowser->insertPlainText(tp1); ui->textBrowser->append("Размер штрафа: ");
         ui->textBrowser->insertPlainText(QString::number(razz)); ui->textBrowser->append("");
         //cout<<"\n  Номер автомобиля: "<<nom<<endl<<"  Дата нарушения: "<<dt<<endl<<"  Время нарушения: "<<vrem<<endl<<"  Тип нарушения: "<<tp<<endl<<"  Размер штрафа: "<<razz<<"\n\n";
         if(!(f>>nom)) break; i++;
         }
   label1:
   f.close();
}
