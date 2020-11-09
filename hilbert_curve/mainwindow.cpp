#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
void MainWindow:: delay(int millisecondsToWait)
{
    QTime dieTime= QTime::currentTime().addMSecs(millisecondsToWait );
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
QImage img(512, 512, QImage::Format_RGB888);

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

int dist = 512;

int sign(int x){
return x>=0? 1:-1;
}
void MainWindow::bLine(int x1, int y1, int x2, int y2,QRgb col)
{
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int x = x1;
    int y = y1;
    int i = 0;
    if(dx>=dy){
        int p = 2*dy - dx;
        while(i<=dx){
            img.setPixel(x,y,col);
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
            img.setPixel(x,y,col);
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
    ui->window->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_clicked()
{
    dist = 512;
    int level = ui->level->toPlainText().toInt();

    for (int i = level; i > 0; i--) {
        dist /= 2;
    }

    this->x = dist/2;
    this->y = dist/2;
    HilbertA(level);
}

void MainWindow::HilbertA(int level) {
    if (level > 0) {
        HilbertB(level - 1);
        lineDraw(0, dist,ha);
        HilbertA(level - 1);
        lineDraw(dist, 0,ha);
        HilbertA(level - 1);
        lineDraw(0, -dist,ha);
        HilbertC(level - 1);
    }
}

void MainWindow::HilbertB(int level) {
    if (level > 0) {
        HilbertA(level - 1);
        lineDraw(dist, 0,hb);
        HilbertB(level - 1);
        lineDraw(0, dist,hb);
        HilbertB(level - 1);
        lineDraw(-dist, 0,hb);
        HilbertD(level - 1);
    }
}

void MainWindow::HilbertC(int level) {
    if (level > 0) {
        HilbertD(level - 1);
        lineDraw(-dist, 0,hc);
        HilbertC(level - 1);
        lineDraw(0, -dist,hc);
        HilbertC(level - 1);
        lineDraw(dist, 0,hc);
        HilbertA(level - 1);
    }
}

void MainWindow::HilbertD(int level) {
    if (level > 0) {
        HilbertC(level - 1);
        lineDraw(0, -dist,hd);
        HilbertD(level - 1);
        lineDraw(-dist, 0,hd);
        HilbertD(level - 1);
        lineDraw(0, dist,hd);
        HilbertB(level - 1);
    }
}

void MainWindow::lineDraw(int incx, int incy,QRgb col) {
//    delay(10);
    bLine(x, y, x + incx, y + incy,col);
    x += incx;
    y += incy;
}

void MainWindow::on_pushButton_2_clicked()
{
    //clear screen
    img.fill(0);
    ui->window->setPixmap(QPixmap::fromImage(img));
    dist = 512;
}
