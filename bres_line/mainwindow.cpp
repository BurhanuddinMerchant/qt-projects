#include "mainwindow.h"
#include "ui_mainwindow.h"
QImage img(500,500,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    bLine(x1,y1,x2,y2);
    ui->label->setPixmap(QPixmap::fromImage(img));
}
int sign(int x){
return x>=0? 1:-1;
}
void MainWindow::bLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int x = x1;
    int y = y1;
    int i = 0;
    if(dx>=dy){
        int p = 2*dy - dx;
        while(i<=dx){
            img.setPixel(x,y,qRgb(255,0,0));
            if(p<0){
                p+=2*dy;
            }
            else{
                p+=2*dy-2*dx;
                y+=sign(y2-y1);
            }
            x+=sign(x2-x1);
            i+=1;
        }

    }else{
        int p = 2*dx - dy;
        while(i<=dy){
            img.setPixel(x,y,qRgb(0,255,0));
            if(p<0){
                p+=2*dx;
            }
            else{
                p+=2*dx-2*dy;
                x+=sign(x2-x1);
            }
            y+=sign(y2-y1);
            i+=1;
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->clear();
}
