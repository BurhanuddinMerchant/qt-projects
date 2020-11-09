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
    int x,y,r;
    x = ui->textEdit->toPlainText().toInt();
    y = ui->textEdit_2->toPlainText().toInt();
    r = ui->textEdit_3->toPlainText().toInt();
    midpoint_circle(x,y,r);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::midpoint_circle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 5/4-r;
    while(x<=y){
        img.setPixel(x+xc,y+yc,qRgb(0,255,0));
        img.setPixel(-x+xc,-y+yc,qRgb(0,255,0));
        img.setPixel(-x+xc,y+yc,qRgb(0,255,0));
        img.setPixel(x+xc,-y+yc,qRgb(0,255,0));
        img.setPixel(y+xc,x+yc,qRgb(0,255,0));
        img.setPixel(-y+xc,-x+yc,qRgb(0,255,0));
        img.setPixel(y+xc,-x+yc,qRgb(0,255,0));
        img.setPixel(-y+xc,x+yc,qRgb(0,255,0));
    if(d<0){
        d=d+2*x+1;
    }
    else{
        d=d+2*(x-y)+1;
        y-=1;
    }
    x+=1;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->clear();
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
}
