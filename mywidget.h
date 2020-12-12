#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStack>
#include <QList>
#include "point.h"
#include "myqueue.h"
#include <QMessageBox>
#include <QElapsedTimer>
#include <QProcess>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    int row;
    int col;
    int ** maze_record; // 保存原始迷宫数据
    int ** maze_data;   // 迷宫

    Point * start;
    Point * end;
    Point * curr;   // 当前位置

public:
    // 重置Mazedata
    void resetMazeData();

    int randomNumber(int x, int y);

    // 自动设置迷宫
    int ** autoSetMaze(int row, int col);

    // 寻找未经过的路径
    Point * findPointNotVisited(Point * p);

    // BFS寻路
    void findPathBFS();

    // DFS寻路
    void findPathDFS();

public:
    // 鼠标按下事件，接收鼠标左键时的位置并在该位置对迷宫进行处理
    void mousePressEvent(QMouseEvent *event);

public:
    // 延时函数
    void sleep(int sec);
    // 弹出信息框
    void message(QString title, QString info);

public:
    QPainter * paint;
    // 绘图事件
    void paintEvent(QPaintEvent *event);

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_hand_btn_clicked();

    void on_DFS_btn_clicked();

    void on_BFS_btn_clicked();

    void on_auto_btn_clicked();

private:
    Ui::MyWidget *ui;
};
#endif // MYWIDGET_H
