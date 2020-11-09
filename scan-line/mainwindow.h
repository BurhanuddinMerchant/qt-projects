#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void bresenham(int,int,int,int);
    void mousePressEvent(QMouseEvent *event);
    void delay(int);
    int sign(int);


private:
    Ui::MainWindow *ui;
    int i,j,k,x[10],y[10],ymax, ymin, yy, temp,n,ver;
    float dx, dy, m[10], x_int[10], inter_x[10];
    bool start;
};

#endif // MAINWINDOW_H
