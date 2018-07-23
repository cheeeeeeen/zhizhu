#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include<QComboBox>
#include<QMovie>
#include<QList>
#include <QWidget>
#include <QPainter>
#include <QMainWindow>
#include <QtCore>
#include <QTimer>
#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <cstring>
#include <QPushButton>
#include <QLCDNumber>
#include <QPixmap>
#include <QGuiApplication>
#include <QFrame>
#include <QTextEdit>
#include <stdlib.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QDebug>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void readhelp();
    void start();
    void backtomenu();
    void addpoke();
    void check();
private:
    Ui::MainWindow *ui;
};
class poke : public QPushButton
{
    Q_OBJECT
public:
    int color;//1红桃，2方片，3草花，4黑桃
    int number;//1-K
    int solved=0;//0代表没有被从1-13排好
    int open=0;//0代表没被翻开
    int ontable=0;//0代表还没被发出来
    poke *father=NULL;//上一张牌
    poke *child=NULL;//下一张牌
    int my=-1;//自己的编号
    poke(QWidget *parent=Q_NULLPTR):
        QPushButton(parent)
    {

    }
public:
    void showpicture();
public slots:
    void clickpoke();
};

#endif // MAINWINDOW_H
