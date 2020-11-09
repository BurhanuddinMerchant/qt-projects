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
    Bcircle(x,y,r);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::Bcircle(int xc, int yc, int r)
{
    int x=0;
    int y=r;
    int d = 3-2*r;
    while(x<=y){
        img.setPixel(y+xc,x+yc,qRgb(255,0,0));
        img.setPixel(x+xc,y+yc,qRgb(255,0,0));
        img.setPixel(-x+xc,y+yc,qRgb(255,0,0));
        img.setPixel(-y+xc,x+yc,qRgb(255,0,0));
        img.setPixel(-y+xc,-x+yc,qRgb(255,0,0));
        img.setPixel(-x+xc,-y+yc,qRgb(255,0,0));
        img.setPixel(x+xc,-y+yc,qRgb(255,0,0));
        img.setPixel(y+xc,-x+yc,qRgb(255,0,0));

        if(d<0){
            d = d+4*x+6;

        }
        else{
            d=d+4*(x-y)+10;
            y=y-1;
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
