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
    int x, y;
    QRgb ha = qRgb(255,255,255);
    QRgb hb = qRgb(255,255,255);
    QRgb hc = qRgb(255,255,255);
    QRgb hd = qRgb(255,255,255);
private slots:
    void bLine(int x1, int y1, int x2, int y2,QRgb col);
    void on_pushButton_clicked();

    void HilbertA(int level);

    void HilbertB(int level);

    void HilbertC(int level);

    void HilbertD(int level);

    void lineDraw(int incx, int incy,QRgb col);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    void delay(int millisecondsToWait);
};
#endif // MAINWINDOW_H
