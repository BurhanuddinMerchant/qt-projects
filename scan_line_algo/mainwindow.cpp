#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
QImage img(500,500,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver=0;
    start=true;
}

MainWindow::~MainWindow()
{
    delete ui;
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
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_clicked()
{
    //mousePressEvent()
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(start){
    int p = ev->pos().x();
    int q= ev->pos().y();
    a[ver]=p;
    b[ver]=q;
    if(ev->button()==Qt::RightButton){
        bLine(a[0],b[0],a[ver-1],b[ver-1]);
        start = false;
    }
    else{
        if(ver>0){
            bLine(a[ver],b[ver],a[ver-1],b[ver-1]);
        }
    }
    ver++;
    }

    }


void MainWindow::on_pushButton_2_clicked()
{
    img.fill(0);
    ui->label->setPixmap(QPixmap::fromImage(img));
}
