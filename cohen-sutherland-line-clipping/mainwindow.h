#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    int  MAX_X = 499;
    int  MAX_Y = 499;
    int  MIN_X = 0;
    int  MIN_Y = 0;
    int const INSIDE = 0; // 0000
    int const LEFT = 1; // 0001
    int const RIGHT = 2; // 0010
    int const BOTTOM = 4; // 0100
    int const TOP = 8; // 1000
    int computeCode(double x,double y);
    void cohenSutherlandClip(double x1, double y1,double x2, double y2);
    void bLine(int x1, int y1, int x2, int y2);
    void mousePressEvent(QMouseEvent *event);
    double ptx[20];
    double pty[20];
    int i=0;

};
#endif // MAINWINDOW_H
