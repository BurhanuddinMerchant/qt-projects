#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>
#include<iostream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int ver, a[20], b[20], i, j, k, xi[20], temp;
//    int ver,i,j,k,temp;
//    int *a = new int[20];
//    int *b = new int[20];
//    int *xi = new int[20];
//    int *slope = new int[20];
    float dx, dy, slope[20];
//    float dx,dy;
    bool start;

private slots:

    void DDALine(int x1, int y1, int x2, int y2, QRgb);

    void mousePressEvent(QMouseEvent *event);

    void on_pushButton_clicked();
    void delay(int millisecondsToWait);
    void on_pushButton_2_clicked();
    bool validateInput(QString s);
};
#endif // MAINWINDOW_H
