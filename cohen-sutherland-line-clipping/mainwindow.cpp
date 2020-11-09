#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include "QMouseEvent"
#include <QTime>
#include<vector>
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

int MainWindow::computeCode(double x, double y)
{
        int code = INSIDE;

        if (x < MIN_X) // to the left of label
            code |= LEFT;
        else if (x > MAX_X) // to the right of label
            code |= RIGHT;
        if (y < MIN_Y) // below the label
            code |= BOTTOM;
        else if (y > MAX_Y) // above the label
            code |= TOP;
        return code;
}

void MainWindow::cohenSutherlandClip(double x1, double y1, double x2, double y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    // Initialize line as outside the label window
    bool accept = false;
    //this loop will continue to execute untill the clipped coordinates are determined.
    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // If both endpoints lie within label

            accept = true;
            break;
        }
            else if (code1 & code2) {
                //anding operation gives 1
                // line completely outside
                break;
            }
            else {
                // Some segment of line lies within the label
                int out_code;
                double x, y;

                // At least one endpoint is outside the
                // label, pick it.
                if (code1 != 0)
                    out_code = code1;
                else
                    out_code = code2;

                // Find intersection point;
                if (out_code & TOP) {
                    // point is above the clip label
                    x = x1 + (x2 - x1) * (MAX_Y - y1) / (y2 - y1);
                    y = MAX_Y;
                }
                else if (out_code & BOTTOM) {
                    // point is below the label
                    x = x1 + (x2 - x1) * (MIN_Y - y1) / (y2 - y1);
                    y = MIN_Y;
                }
                else if (out_code & RIGHT) {
                    // point is to the right of label
                    y = y1 + (y2 - y1) * (MAX_X - x1) / (x2 - x1);
                    x = MAX_X;
                }
                else if (out_code & LEFT) {
                    // point is to the left of label
                    y = y1 + (y2 - y1) * (MIN_X - x1) / (x2 - x1);
                    x = MIN_X;
                }

                // Now intersection point x, y is found
                // We replace point outside label
                // by intersection point
                if (out_code == code1) {
                    x1 = x;
                    y1 = y;
                    code1 = computeCode(x1, y1);
                }
                else {
                    x2 = x;
                    y2 = y;
                    code2 = computeCode(x2, y2);
                }
            }
        }
        if (accept) {

            bLine(x1,y1,x2,y2);
            ui->label_7->setText("Partial/Full");

        }
        else{
            //line rejecte
            ui->label_7->setText("Outside");
            return;
        }

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int p = event -> pos().x();
    int q = event -> pos().y();
    if(p>500 || q>500){
        return;
    }
    else{
        if(i%2!=0){
            ptx[i]=p;
            pty[i]=q;
            bLine(p,q,ptx[i-1],pty[i-1]);
            ui->label->setPixmap(QPixmap::fromImage(img));
            i++;
        }
        else{
            ptx[i]=p;
            pty[i]=q;
            i+=1;
        }
    }

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

void MainWindow::on_pushButton_clicked()
{
    double x1 = ui->textEdit->toPlainText().toInt();
    double y1 = ui->textEdit_2->toPlainText().toInt();
    double x2 = ui->textEdit_3->toPlainText().toInt();
    double y2 = ui->textEdit_4->toPlainText().toInt();
    cohenSutherlandClip(x1,y1,x2,y2);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_2_clicked()
{
    img.fill(0);
    ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_pushButton_3_clicked()
{
    double x1 = ui->textEdit->toPlainText().toInt();
    double y1 = ui->textEdit_2->toPlainText().toInt();
    double x2 = ui->textEdit_3->toPlainText().toInt();
    double y2 = ui->textEdit_4->toPlainText().toInt();
    bLine(x1,y2,x1,y1);
    bLine(x1,y2,x2,y2);
    bLine(x2,y2,x2,y1);
    bLine(x2,y1,x1,y1);
    MAX_X = x1;
    MAX_Y = y1;
    MIN_X = x2;
    MIN_Y = y2;

    ui->label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_pushButton_4_clicked()
{
    int x1=MAX_X;
    int y1=MAX_Y;
    int x2=MIN_X;
    int y2 =MIN_Y;
    img.fill(0);
    bLine(x1,y2,x1,y1);
    bLine(x1,y2,x2,y2);
    bLine(x2,y2,x2,y1);
    bLine(x2,y1,x1,y1);
    for(int j=0;j<i;j+=2){
        cohenSutherlandClip(ptx[j],pty[j],ptx[j+1],pty[j+1]);
    }
    i=0;
    ui->label->setPixmap(QPixmap::fromImage(img));
}
