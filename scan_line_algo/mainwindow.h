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
    void mousePressEvent(QMouseEvent *ev);
    void bLine(int x1, int y1, int x2, int y2);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int ver,a[20],b[20],i,xi[20],j,temp,k;
    float slope[20],dx,dy;
    bool start;
};
#endif // MAINWINDOW_H
