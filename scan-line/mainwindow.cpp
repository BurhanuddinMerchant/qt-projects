#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QMouseEvent>
#include<QTime>

using namespace std;
static QImage img(500,500,QImage::Format_RGB888);
struct edge
{
int x1, y1, x2, y2, flag;
}ed[10], temped;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ymax= 0; ymin= 480;
    ver=0;
    start =true;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
     int p=ev->pos().x();
     int q=ev->pos().y();
     x[ver]=p;
     y[ver]=q;
     //img.setPixel(x[ver],y[ver],qRgb(255,255,255));
     ver++;
    //ui->label->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::on_pushButton_clicked()
{
    n=ver;
    //cout<<n<<endl;
   for(i=0;i<n;i++)
    {
        if(y[i]>ymax)
        ymax=y[i];
        if(y[i]<ymin)
        ymin=y[i];
        ed[i].x1=x[i];
        ed[i].y1=y[i];
        //cout<<i<<",";
    }
   // store the edge information
   for(i=0;i<n-1;i++)
   {
   ed[i].x2= ed[i+1].x1;
   ed[i].y2=ed[i+1].y1;
   ed[i].flag=0;
   }
   //for last edge x2= first point x1
   ed[i].x2=ed[0].x1;
   ed[i].y2=ed[0].y1;
   ed[i].flag=0;
   for(i=0;i<n-1;i++)//check for y1>y2 if not interchange it
   {
       if(ed[i].y1<ed[i].y2)
       {
       temp=ed[i].x1;
       ed[i].x1=ed[i].x2;
       ed[i].x2=temp;
       temp=ed[i].y1;
       ed[i].y1=ed[i].y2;
       ed[i].y2=temp;
       }
   }
   for(i=0;i<n;i++)//draw polygon
   {
        bresenham(ed[i].x1, ed[i].y1, ed[i].x2, ed[i].y2);
   }
   for(i=0;i<n-1;i++)//storing the edges as y1, y2, x1
   for(j=0;j<n-1;j++)
   {
   if( ed[j].y1<ed[j+1].y1)
   {
   temped= ed[j];
   ed[j]= ed[j+1];
   ed[j+1]=ed[j+1];
   ed[j+1]=temped;
   }
   if(ed[j].y1==ed[j+1].y1)
   {
   if(ed[j].y2<ed[j+1].y2)
   {
   temped=ed[j];
   ed[j]=ed[j+1];
   ed[j+1]=temped;
   if(ed[j].y2==ed[j+1].y2)
   {
   if(ed[j].x1<ed[j+1].x1)
   {
   temped=ed[j];
   ed[j]=ed[j+1];
   ed[j+1]=temped;
   }
   }
   }
   }
   for(i=0;i<n;i++)//calcualte 1/slope
   {
   dx=ed[i].x2-ed[i].x1;
   dy=ed[i].y2-ed[i].y1;
   if(dy==0)
   m[i]=0;
   else
   m[i]=dx/dy;
   inter_x[i]= ed[i].x1;
   }
   yy=ymax;
   while(yy>ymin)// mark active edges
   {
   for(i=0;i<n;i++)
   {
   if(yy>ed[i].y2&&yy<=ed[i].y1&&ed[i].y1!=ed[i].y2)
   ed[i].flag=1;
   else
   ed[i].flag=0;
   }
   j=0;
   for(i=0;i<n;i++)// finding x intersections
   {
   if(ed[i].flag==1)
   {
   if(yy==ed[i].y1)
   {
   x_int[j]=ed[i].x1;
   j++;
   if(ed[i-1].y1==yy&&ed[i-1].y1<<yy)
   {
   x_int[j]=ed[i].x1;
   j++;
   }
   if(ed[i+1].y1==yy&&ed[i+1].y1<yy)
   {
   x_int[j]=ed[i].x1;
   j++;
   }
   }
   else
   {
   x_int[j]=inter_x[i]+(-m[i]);
   inter_x[i]=x_int[j];
   j++;
   }
   }
   }
   for(i=0;i<j;i++)// sorting the x intersections
   {
   for(k=0;k<j-1;k++)
   {
   if (x_int[k]>x_int[k+1])
   {
   temp= x_int[k];
   x_int[k]=x_int[k+1];
   x_int[k+1]=temp;
   }
   }
   }
   for(i=0;i<j;i+=2)// extracting x values to draw a line
   {
       delay(20);
   bresenham(x_int[i], yy, x_int[i+1], yy);
   }
   yy--;
   }// end of while loop
}
}
void MainWindow:: delay(int millisecondsToWait)
{
    QTime dieTime= QTime::currentTime().addMSecs(millisecondsToWait );
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::bresenham(int x1, int y1, int x2, int y2)
{
   int x,y,dx,dy,i=0;
   int p;
        QRgb value;
        value=qRgb(255,255,0);
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    x=x1;
    y=y1;
   // qDebug()<<x<<" "<<dx<<" "<<y<<" "<<dy;
    if(dx>=dy)
    {
        p=2*(dy)-dx;
      //   qDebug()<<"\n value of p:"<<p;
        while (i<dx)
        {
            img.setPixel(x,y,value);

            if(p<0)
                p=p+2*dy;
            else
                {
                    p=p+2*(dy-dx);
                    y=y+1*sign(y2-y1);
                }
            x = x + 1*sign(x2-x1);
            i++;
            }
        }
    else
    {
        p=2*dx-dy;
        while (i<dy)
        {
            img.setPixel(x,y,value);
            if(p<0)
                p=p+2*dx;
            else
                {
                    p=p+2*(dx-dy);
                    x=x+1*sign(x2-x1);
                }
            y = y + 1*sign(y2-y1);
            i++;
            }

    }
    //ui->label->setPixmap(QPixmap::fromImage(img));

    }

int MainWindow::sign(int q)
{
    if(q<0)
        return -1;
    else {
        return 1;
    }
}
