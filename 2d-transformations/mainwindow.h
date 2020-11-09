#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Matrix{
public:
    double mat[4][3];
    int n;
    Matrix(double m[][3],int i){
        if(i==4){
            for(int j=0;j<4;j++){
                mat[j][0]=m[j][0];
                mat[j][1]=m[j][1];
                mat[j][2]=1;
            }
        }
        else{
            int j;
            for(j=0;j<3;j++){
                mat[j][0]=m[j][0];
                mat[j][1]=m[j][1];
                mat[j][2]=1;
            }
            mat[j][0]=0;
            mat[j][1]=0;
            mat[j][2]=1;
        }
        this->n=i;

    }


    Matrix operator *(const Matrix &m){
        double r[this->n][3];
        for(int k=0;k<this->n;k++){
            r[k][0] = 0;
            r[k][1] = 0;
            r[k][2] = 1;
        }
        int m2 = 3,n2 = 3;
        for(int i=0;i<this->n;i++){
            for(int j=0;j<n2;j++){
                int sum = 0;
                int k;
                for(k=0;k<m2;k++){
                    sum+=this->mat[i][k]*m.mat[k][j];
                }
                r[i][j] = sum;
            }
        }
        Matrix res(r,this->n);
        return res;
    }

};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    bool isTriangle;
    double tri[3][3];
    double rh[4][3];
    void multiply_matrices(double a[][3],int m1,double b[3][3]);
    void bLine(int x1,int y1,int x2,int y2);

};
#endif // MAINWINDOW_H
