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


void MainWindow::on_pushButton_3_clicked()
{

        ui->textEdit->clear();
        ui->textEdit_2->clear();
        ui->textEdit_3->clear();
        ui->textEdit_4->clear();
        ui->textEdit_5->clear();
        ui->textEdit_6->clear();
        ui->textEdit_7->clear();
        img.fill(0);
        ui->label->setPixmap(QPixmap::fromImage(img));
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
    int x,y,r;
    x = ui->textEdit_5->toPlainText().toInt();
    y = ui->textEdit_6->toPlainText().toInt();
    r = ui->textEdit_7->toPlainText().toInt();
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

void MainWindow::on_pushButton_4_clicked()
{
    Bcircle(250,250,90);
    DDAline(50,350,450,350);
    DDAline(50,350,50,150);
    DDAline(50,150,450,150);
    DDAline(450,150,450,350);
    DDAline(450,250,250,350);
    DDAline(250,150,450,250);
    DDAline(50,250,250,350);
    DDAline(50,250,250,150);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_5_clicked()
{
    int x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    DDAline(x1,y1,x2,y2);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::DDAline(int x1, int y1, int x2, int y2)
{
    float dx = x2-x1;
    float dy = y2-y1;
    float step;
    if(abs(dx)>=abs(dy)){
        step = abs(dx);
    }
    else{
        step = abs(dy);
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
