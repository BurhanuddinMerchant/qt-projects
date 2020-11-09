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
    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();
    dda(x1,y1,x2,y2);
    ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::dda(int x1, int y1, int x2, int y2)
{
    float dx = x2-x1;
    float dy = y2-y1;
    float step;
    if(abs(dx)>=abs(dy)){
        step = dx;
    }
    else{
        step = dy;
    }
    float x_inc = dx/step;
    float y_inc = dy/step;
    int i=0;
    float x=x1;
    float y = y1;
    while(i<step){
        img.setPixel(x,y,qRgb(255,0,0));
        i++;
        x+=x_inc;
        y+=y_inc;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->label->clear();
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
}
