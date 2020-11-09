#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"

#include<iostream>
#include <QTime>
using namespace std;
void MainWindow:: delay(int millisecondsToWait)
{
    QTime dieTime= QTime::currentTime().addMSecs(millisecondsToWait );
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
QImage img(500, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver = 0;
    start = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DDALine(int x1, int y1, int x2, int y2, QRgb color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xinc = dx / steps;
    float yinc = dy / steps;

    float x = x1;
    float y = y1;

    for(int i = 0; i < steps; i++)
    {
        img.setPixel(x, y, color);
        x += xinc;
        y += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(start)
    {
        int p = event -> pos().x();
        int q = event -> pos().y();
        if(p>500 || q>500){
            return;
        }
        b[ver] = q;
        a[ver] = p;

        if(event -> button() == Qt :: RightButton)
        {
            DDALine(a[0], b[0], a[ver - 1], b[ver - 1], qRgb(255, 255, 255));
            start = false;
        } else
        {
            if(ver > 0)
            {
                DDALine(a[ver], b[ver], a[ver - 1], b[ver - 1], qRgb(255, 255, 255));
            }
        }
        ver++;
    }
}

void MainWindow::on_pushButton_clicked()
{
    cout<<"HEllo";
    QString r = ui -> textEdit -> toPlainText();
    QString g = ui -> textEdit_2-> toPlainText();
    QString bl = ui -> textEdit_3 -> toPlainText();
    int red ;
    int green ;
    int blue ;
    if(validateInput(r)||validateInput(g)||validateInput(bl)){
        red = r.toInt();
        green = g.toInt();
        blue = bl.toInt();
    }
    else{
        red = 255;
        green = 255;
        blue = 255;
    }
    a[ver-1] = a[0];
    b[ver-1] = b[0];
    //loop over the points registered upto the point right click event occurs
    for(i = 0; i < ver-1; i++)
    {
        //calculate the slopes of every line and store in the slope array
        dy = b[i + 1] - b[i];
        dx = a[i + 1] - a[i];
        if(dy == 0.0f) slope[i] = 1.0;
        if(dx == 0.0f) slope[i] = 0.0;
        if((dy != 0.0f) && (dx != 0.0f))
        {
            slope[i] = dx/dy;
        }
    }
    // loop over all the 500 y coordinates
    for (int y = 0; y < 500; y++)
    {
        // initialise number of active edges at a particular y level
        k = 0;
        // loop over the the slopes array and look for active edges
        for(i = 0; i < ver-1; i++)
        {
            // if the point in consideration is an active edge....
            if(((b[i] <= y) && (b[i + 1] > y)) || ((b[i] > y) && (b[i + 1] <= y)))
            {
                // update its value to the new value required for this y-level
                xi[k] = int(a[i] + (slope[i] * (y - b[i])));
                k++;
            }
        }
        // sort the active edges in increasing order
        for(j = 0; j < k - 1; j++)
            for(i = 0; i < k - j - 1; i++)
            {
                if(xi[i] > xi[i + 1])
                {
                    temp = xi[i];
                    xi[i] = xi[i + 1];
                    xi[i + 1] = temp;
                }
            }
        // draw lines at the current y-level between the k active edges
        for(i = 0; i < k; i += 2)
        {
            DDALine(xi[i], y, xi[i + 1] +1, y, qRgb(red, green, blue));
            delay(5);
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    img.fill(0);
    ver = 0;
    start = true;
    ui->label->setPixmap(QPixmap::fromImage(img));

}

bool MainWindow::validateInput(QString s)
{
    bool noError = true;
    if((int)s.size()>3){
        noError = false;
        return noError;
    }
    for(int i=0;i<(int)s.size();i++){
        if(s[i].isDigit()){
            continue;
        }
        else{
            noError = false;
            break;
        }
    }
    return noError;
}
