#include "mainwindow.h"
#include "ui_mainwindow.h"
QImage img(500,500,QImage::Format_RGB888);
#include <cmath>
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

void MainWindow::multiply_matrices(double a[][3], int m1, double b[3][3])
{
    /*
        int m2 = 3,n2 = 3;
        int r[m1][n2];
        for(int i=0;i<m1;i++){
            for(int j=0;j<n2;j++){
                int sum = 0;
                int k;
                for(k=0;k<m2;k++){
                    sum+=a[i][k]*b[k][j];
                }
                r[i][j] = sum;
            }
        }
        img.fill(0);
        int i;
        for( i=0;i<m1-1;i++){
            bLine(r[i][0],r[i][1],r[i+1][0],r[i+1][1]);
        }
        bLine(r[i][0],r[i][1],r[0][0],r[0][1]);
        ui->label->setPixmap(QPixmap::fromImage(img));
    */

        Matrix points_mat(a,m1),operation(b,3);
        Matrix res = points_mat*operation;
        img.fill(0);
        int i;
        for( i=0;i<m1-1;i++){
            bLine(res.mat[i][0],res.mat[i][1],res.mat[i+1][0],res.mat[i+1][1]);
        }
        bLine(res.mat[i][0],res.mat[i][1],res.mat[0][0],res.mat[0][1]);
        ui->label->setPixmap(QPixmap::fromImage(img));

}



void MainWindow::on_pushButton_clicked()
{
    //triangle push button
    tri[0][0]=ui->textEdit->toPlainText().toInt();
    tri[0][1]=ui->textEdit_2->toPlainText().toInt();
    tri[1][0]=ui->textEdit_6->toPlainText().toInt();
    tri[1][1]=ui->textEdit_7->toPlainText().toInt();
    tri[2][0]=ui->textEdit_8->toPlainText().toInt();
    tri[2][1]=ui->textEdit_9->toPlainText().toInt();
    tri[0][2] = 1;
    tri[1][2] = 1;
    tri[2][2] = 1;
    img.fill(0);
    bLine(tri[0][0],tri[0][1],tri[1][0],tri[1][1]);
    bLine(tri[2][0],tri[2][1],tri[1][0],tri[1][1]);
    bLine(tri[0][0],tri[0][1],tri[2][0],tri[2][1]);
    isTriangle=true;
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_7_clicked()
{
    //rhombus push button
    rh[0][0]=ui->textEdit->toPlainText().toInt();
    rh[0][1]=ui->textEdit_2->toPlainText().toInt();
    rh[1][0]=ui->textEdit_6->toPlainText().toInt();
    rh[1][1]=ui->textEdit_7->toPlainText().toInt();
    rh[2][0]=ui->textEdit_8->toPlainText().toInt();
    rh[2][1]=ui->textEdit_9->toPlainText().toInt();
    rh[3][0]=ui->textEdit_10->toPlainText().toInt();
    rh[3][1]=ui->textEdit_11->toPlainText().toInt();
    rh[0][2] = 1;
    rh[1][2] = 1;
    rh[2][2] = 1;
    rh[3][2] = 1;
    img.fill(0);
    bLine(rh[0][0],rh[0][1],rh[1][0],rh[1][1]);
    bLine(rh[1][0],rh[1][1],rh[2][0],rh[2][1]);
    bLine(rh[2][0],rh[2][1],rh[3][0],rh[3][1]);
    bLine(rh[3][0],rh[3][1],rh[0][0],rh[0][1]);
    isTriangle=false;

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_3_clicked()
{
    //translate
    double tx = ui->textEdit_4->toPlainText().toInt();
    double ty = ui->textEdit_5->toPlainText().toInt();
    double translate[3][3]={{1,0,0},{0,1,0},{tx,ty,1}};
    if(isTriangle){
        multiply_matrices(tri,3,translate);
    }
    else{
        multiply_matrices(rh,4,translate);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    //scale
    double sx = ui->textEdit_4->toPlainText().toFloat();
    double sy = ui->textEdit_5->toPlainText().toFloat();
    double scale[3][3]={{sx,0,0},{0,sy,0},{0,0,1}};
    if(isTriangle){
        multiply_matrices(tri,3,scale);
    }
    else{
        multiply_matrices(rh,4,scale);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    //rotate
    double theta = ui->textEdit_12->toPlainText().toFloat();
    double translate[3][3]={{cos(theta),sin(theta),0},{-sin(theta),cos(theta),0},{0,0,1}};
    if(isTriangle){
        multiply_matrices(tri,3,translate);
    }
    else{
        multiply_matrices(rh,4,translate);
    }
}
