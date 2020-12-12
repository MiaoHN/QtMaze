#include "mywidget.h"
#include "ui_mywidget.h"

void MyWidget::resetMazeData()
{
    if (this->maze_data == nullptr) {
        // 如果mazedata是空指针则分配空间
        this->maze_data = new int * [this->row];
        for (int i = 0; i < this->row; i++) {
            this->maze_data[i] = new int[this->col];
        }
    }
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->maze_data[i][j] = this->maze_record[i][j];
        }
    }

}

int MyWidget::randomNumber(int x, int y)
{
    return QRandomGenerator::global()->bounded(x, y);
}

int **MyWidget::autoSetMaze(int row, int col)
{
    QList<Point*> path_list;
    int ** res = new int * [row];
    for (int i = 0; i < row; i++) {
        res[i] = new int[col];
    }
    for (int i = 0; i < row; i++) {
        int flag = i % 2;
        for (int j = 0; j < col; j++) {
            if (flag == 0) {
                // 单数行全为墙
                res[i][j] = 1;
            }else {
                // 偶数行墙和路依次分布
                if (j % 2 == 0) {
                    res[i][j] = 1;
                }else {
                    res[i][j] = 0;
                }
            }
        }
    }
    // 随机选取地图边缘的路
    int flag_xy = randomNumber(0, 10);
    int x = 0;
    int y = 0;
    if (flag_xy % 2 == 0) {
        x = 1;
        y = 2 * randomNumber(0, (col - 1) / 2) + 1;
    } else {
        y = 1;
        x = 2 * randomNumber(0, (row - 1) / 2) + 1;
    }
    // 将该点做标记
    res[x][y] = 10;
    // 将该点周围的墙加入数组中
    if (x != 1 && res[x - 1][y] != 10) {
        path_list.push_back(new Point(x - 1, y, 0));
    }
    if (x != row - 2 && res[x + 1][y] != 10) {
        path_list.push_back(new Point(x + 1, y, 0));
    }
    if (y != 1 && res[x][y - 1] != 10) {
        path_list.push_back(new Point(x, y - 1, 0));
    }
    if (y != col - 2 && res[x][y + 1] != 10) {
        path_list.push_back(new Point(x, y + 1, 0));
    }
    while (path_list.empty() == false) {
        // 数组中随机选取一个点
        int index = randomNumber(0, path_list.size());
        Point * ptr = path_list[index];
        int ptr_x = ptr->x;
        int ptr_y = ptr->y;
        // 从左到右
        if (res[ptr_x - 1][ptr_y] == 10 && res[ptr_x + 1][ptr_y] == 0) {
            res[ptr_x][ptr_y] = 10;
            res[ptr_x + 1][ptr_y] = 10;
            // 将周围的墙加入数组中
            if (ptr_x + 1 != row - 2 && res[ptr_x + 3][ptr_y] != 10) {
                path_list.push_back(new Point(ptr_x + 2, ptr_y, 0));
            }
            if (ptr_y != 1 && res[ptr_x + 1][ptr_y - 2] != 10) {
                path_list.push_back(new Point(ptr_x + 1, ptr_y - 1, 0));
            }
            if (ptr_y != col - 2 && res[ptr_x + 1][ptr_y + 2] != 10) {
                path_list.push_back(new Point(ptr_x + 1, ptr_y + 1, 0));
            }
        }
        // 从右到左
        if (res[ptr_x + 1][ptr_y] == 10 && res[ptr_x - 1][ptr_y] == 0) {
            res[ptr_x][ptr_y] = 10;
            res[ptr_x - 1][ptr_y] = 10;
            // 将周围的墙加入数组中
            if (ptr_x - 1 != 1 && res[ptr_x - 3][ptr_y] != 10) {
                path_list.push_back(new Point(ptr_x - 2, ptr_y, 0));
            }
            if (ptr_y != 1 && res[ptr_x - 1][ptr_y - 2] != 10) {
                path_list.push_back(new Point(ptr_x - 1, ptr_y - 1, 0));
            }
            if (ptr_y != col - 2 && res[ptr_x - 1][ptr_y + 2] != 10) {
                path_list.push_back(new Point(ptr_x - 1, ptr_y + 1, 0));
            }
        }
        // 从上到下
        if (res[ptr_x][ptr_y - 1] == 10 && res[ptr_x][ptr_y + 1] == 0) {
            res[ptr_x][ptr_y] = 10;
            res[ptr_x][ptr_y + 1] = 10;
            // 将周围的墙加入数组中
            if (ptr_x != row - 2 && res[ptr_x + 2][ptr_y + 1] != 10) {
                path_list.push_back(new Point(ptr_x + 1, ptr_y + 1, 0));
            }
            if (ptr_x != 1 && res[ptr_x - 2][ptr_y + 1] != 10) {
                path_list.push_back(new Point(ptr_x - 1, ptr_y + 1, 0));
            }
            if (ptr_y + 1!= col - 2 && res[ptr_x][ptr_y + 3] != 10) {
                path_list.push_back(new Point(ptr_x, ptr_y + 2, 0));
            }
        }
        // 从下到上
        if (res[ptr_x][ptr_y + 1] == 10 && res[ptr_x][ptr_y - 1] == 0) {
            res[ptr_x][ptr_y] = 10;
            res[ptr_x][ptr_y - 1] = 10;
            // 将周围的墙加入数组中
            if (ptr_x != row - 2 && res[ptr_x + 2][ptr_y - 1] != 10) {
                path_list.push_back(new Point(ptr_x + 1, ptr_y - 1, 0));
            }
            if (ptr_x != 1 && res[ptr_x - 2][ptr_y - 1] != 10) {
                path_list.push_back(new Point(ptr_x - 1, ptr_y - 1, 0));
            }
            if (ptr_y - 1 != 1 && res[ptr_x][ptr_y - 3] != 10) {
                path_list.push_back(new Point(ptr_x, ptr_y - 2, 0));
            }
        }
        path_list.removeAt(index);

    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (res[i][j] == 10) {
                res[i][j] = 0;
            }
        }
    }

    if (col > 20 || row > 20) {
        for (int i = 0; i < row * 5; i++) {
            int x = randomNumber(0, 100) % (row - 2) + 1;
            int y = randomNumber(0, 100) % (col - 2) + 1;
            if (res[x][y] == 1) {
                int flag = 0;
                if (res[x - 1][y] == 1) {
                    flag++;
                }
                if (res[x + 1][y] == 1) {
                    flag++;
                }
                if (res[x][y - 1] == 1) {
                    flag++;
                }
                if (res[x][y + 1] == 1) {
                    flag++;
                }
                if (flag > 1) {
                    res[x][y] = 0;
                }
            }
        }
    }

    return res;
}

Point * MyWidget::findPointNotVisited(Point * p)
{
    Point * res = new Point();
    res->status = 0;
    if (p->x - 1 >= 0 && this->maze_data[p->x - 1][p->y] != 1 && this->maze_data[p->x - 1][p->y] != -1) {
        res->x = p->x - 1;
        res->y = p->y;
    } else if (p->x + 1 < this->row && this->maze_data[p->x + 1][p->y] != 1 && this->maze_data[p->x + 1][p->y] != -1) {
        res->x = p->x + 1;
        res->y = p->y;
    } else if (p->y - 1 >= 0 && this->maze_data[p->x][p->y - 1] != 1 && this->maze_data[p->x][p->y - 1] != -1) {
        res->x = p->x;
        res->y = p->y - 1;
    } else if (p->y + 1 < this->col && this->maze_data[p->x][p->y + 1] != 1 && this->maze_data[p->x][p->y + 1] != -1) {
        res->x = p->x;
        res->y= p->y + 1;
    }
    return res;
}

void MyWidget::findPathBFS()
{
    this->resetMazeData();
    this->repaint();
    // BFS寻路通过队列来寻找路径
    MyQueue pointQueue;
    if (this->start == nullptr || this->end == nullptr) {
        // 如果起点和终点未设置则报错并退出
        message("警告", "未设置起点或终点！！！");
        return;
    }
    // 将start入队
    this->maze_data[start->x][start->y] = -1;
    pointQueue.push(start);
    // 当队列不空且队列头不为终点时，将队列头的所有后继结点加入队列中，直到队首为end停止
    while (pointQueue.isEmpty() == false && *pointQueue.frontPoint() != *end)
    {
        // 指针p指向队列头元素
        Point * p = pointQueue.frontPoint();
        // 上方结点未经过
        if (p->x - 1 >= 0 && this->maze_data[p->x - 1][p->y] != 1 && this->maze_data[p->x - 1][p->y] != -1)
        {
            // 队头元素的后继元素入队，将maze中响应结点的poineer填入
            Point * resp = new Point();
            resp->x = p->x - 1;
            resp->y = p->y;
            this->maze_data[resp->x][resp->y] = -1;
            pointQueue.push(resp);
            pointQueue.queue[pointQueue.end - 1]->pioneer = pointQueue.front;
        }
        // 下方结点未经过
        if (p->x + 1 < this->row && this->maze_data[p->x + 1][p->y] != 1 && this->maze_data[p->x + 1][p->y] != -1)
        {
            // 队头元素的后继元素入队，将maze中响应结点的poineer填入
            Point * resp = new Point();
            //cout << "2" << endl;
            resp->x = p->x + 1;
            resp->y = p->y;
            this->maze_data[resp->x][resp->y] = -1;
            pointQueue.push(resp);
            pointQueue.queue[pointQueue.end - 1]->pioneer = pointQueue.front;
        }
        // 左方结点未经过
        if (p->y - 1 >= 0 && this->maze_data[p->x][p->y - 1] != 1 && this->maze_data[p->x][p->y - 1] != -1)
        {
            // 队头元素的后继元素入队，将maze中响应结点的poineer填入
            Point * resp = new Point();
            resp->x = p->x;
            resp->y = p->y - 1;
            this->maze_data[resp->x][resp->y] = -1;
            pointQueue.push(resp);
            pointQueue.queue[pointQueue.end - 1]->pioneer = pointQueue.front;
        }
        // 右方结点未经过
        if (p->y + 1 < this->col && this->maze_data[p->x][p->y + 1] != 1 && this->maze_data[p->x][p->y + 1] != -1)
        {
            // 队头元素的后继元素入队，将maze中响应结点的poineer填入
            Point * resp = new Point();
            resp->x = p->x;
            resp->y = p->y + 1;
            this->maze_data[resp->x][resp->y] = -1;
            pointQueue.push(resp);
            pointQueue.queue[pointQueue.end - 1]->pioneer = pointQueue.front;
        }
        pointQueue.pop();
    }
    if (pointQueue.isEmpty() == true) {
        message("警告", "未找到通路！！！");
        return;
    }
    QStack<Point*> tempStack;
    Point * point = pointQueue.queue[pointQueue.front];
    while (point->pioneer != -1) {
        tempStack.push(point);
        point = pointQueue.queue[point->pioneer];
    }
    this->resetMazeData();
    while (tempStack.empty() == false) {
        this->maze_data[tempStack.top()->x][tempStack.top()->y] = -1;

        sleep(100);

        this->repaint();

        tempStack.pop();
    }

    // 将起点和终点重新绘制
    this->maze_data[this->start->x][this->start->y] = 2;
    this->maze_data[this->end->x][this->end->y] = 3;
    this->repaint();
    message("info", "路径寻找成功！！！");
}

void MyWidget::findPathDFS()
{
    this->resetMazeData();
    // DFS寻路通过使用栈来寻找路径
    QStack<Point*> pointStack;
    if (this->start == nullptr || this->end == nullptr) {
        // 如果起点和终点未设置则报错并退出
        message("警告", "未设置起点或终点！！！");
        return;
    }

    // 将start入栈并设为已经过（设为-1）
    pointStack.push_back(this->start);
    this->maze_data[this->start->x][this->start->y] = -1;

    // 当栈不为空且栈顶元素不为end时，判断栈顶结点是否有后继未经过结点
    // 如果有未经过结点则入栈，否则栈顶弹出并将栈顶元素标为已经过
    while (pointStack.empty() == false && *(pointStack.top()) != *(this->end)) {
        Point * next_point = findPointNotVisited(pointStack.top());
        if (next_point->x == -1 || next_point->y == -1)
        {
            pointStack.pop();
            continue;
        }
        this->maze_data[next_point->x][next_point->y] = -1;
        pointStack.push(next_point);
    }
    if (pointStack.empty() == true) {
        message("警告", "未找到通路！！！");
        return;
    }

    QStack<Point*> temp_stack;
    while (pointStack.empty() == false) {
        temp_stack.push_back(pointStack.top());
        pointStack.pop();
    }

    // 将栈中元素画到mazedata中
    this->resetMazeData();
    while (temp_stack.empty() == false) {
        this->maze_data[temp_stack.top()->x][temp_stack.top()->y] = -1;

        sleep(100);

        this->repaint();
        temp_stack.pop();
    }
    // 将起点和终点重新绘制
    this->maze_data[this->start->x][this->start->y] = 2;
    this->maze_data[this->end->x][this->end->y] = 3;
    this->repaint();
    message("info", "路径寻找成功！！！");
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    // 获取鼠标相对迷宫左上角的坐标
    int x = event->x() - 240;
    int y = event->y() - 70;
    if (x < 0 || y < 0 || this->maze_data == nullptr) {
        // 如果x，y小于0则直接跳出
        return;
    }
    // 得到迷宫中每个方块的大小
    int max_size = (this->row > this->col) ? this->row : this->col;
    int each_box_size = 500 / max_size;
    // 计算出鼠标点击的方块位置
    int click_row = x / each_box_size;
    int click_col = y / each_box_size;
    // 改变方块当前状态
    if (this->maze_record[click_row][click_col] == 0) {
        // 如果是路则变为墙
        this->maze_record[click_row][click_col] = 1;

    }else if (this->maze_record[click_row][click_col] == 1) {
        // 如果是墙则变为起点
        this->maze_record[click_row][click_col] = 2;
        if (this->start != nullptr) {
            // 如果已经有起点
            this->maze_record[this->start->x][this->start->y] = 0;
            this->start->x = click_row;
            this->start->y = click_col;
        }else {
            // 如果未设置起点则设为起点
            this->start = nullptr;

            this->start = new Point(click_row, click_col, 2);
        }
    }else if (this->maze_record[click_row][click_col] == 2) {
        // 如果是起点，则设置为终点
        delete this->start;
        this->start = nullptr;
        this->maze_record[click_row][click_col] = 3;
        if (this->end != nullptr) {
            // 如果终点已经存在
            this->maze_record[this->end->x][this->end->y] = 0;
            this->end->x = click_row;
            this->end->y = click_col;
        }else {
            this->end = new Point(click_row, click_col, 3);
        }

    }else if (this->maze_record[click_row][click_col] == 3) {
        // 如果是终点，则设置为路
        delete this->end;
        this->end = nullptr;
        this->maze_record[click_row][click_col] = 0;
    }
    this->resetMazeData();
    this->repaint();
}

void MyWidget::sleep(int sec)
{
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<sec);
}

void MyWidget::message(QString title, QString info)
{
    ///---实例化消息对话框对象
    QMessageBox *msgBox;
    msgBox = new QMessageBox(title,		///--这里是设置消息框标题
        info,						///--这里是设置消息框显示的内容
        QMessageBox::Information,							///--这里是在消息框显示的图标
        QMessageBox::Ok | QMessageBox::Default,		///---这里是显示消息框上的按钮情况
        QMessageBox::Cancel | QMessageBox::Escape,	///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
        0);
    msgBox->show();
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    paint = new QPainter;
    paint->begin(this);
    paint->setPen(QPen(Qt::black, 1, Qt::SolidLine));//设置画笔形式
    // 得到迷宫中每个方块的大小
    int max_size = (this->row > this->col) ? this->row : this->col;
    int each_box_size = 500 / max_size;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            // 重复对每个方块进行绘制
            if (this->maze_data[i][j] == 0) {
                // 如果是路则将画笔设为白色
                paint->setBrush(QBrush(Qt::white, Qt::SolidPattern));//设置画刷形式
            }else if(this->maze_data[i][j] == -1) {
                // 如果是墙路径则将画笔设为黄色
                paint->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
            }else if (this->maze_data[i][j] == 1) {
                // 如果是墙则将画笔设为黑色
                paint->setBrush(QBrush(Qt::black, Qt::SolidPattern));
            } else if (this->maze_data[i][j] == 2) {
                // 如果是起点则将画笔设为绿色
                paint->setBrush(QBrush(Qt::green, Qt::SolidPattern));
            } else if (this->maze_data[i][j] == 3) {
                // 如果是终点则将画笔设为红色
                paint->setBrush(QBrush(Qt::red, Qt::SolidPattern));
            }
            paint->drawRect(240 + each_box_size * i, 70 + each_box_size * j, each_box_size, each_box_size);
        }
    }
    paint->end();
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->start = nullptr;
    this->end = nullptr;
}

MyWidget::~MyWidget()
{
    delete ui;
    for (int i = 0; i < this->row ; i++) {
        delete[] this->maze_data[i];
        delete[] this->maze_record[i];
    }
    delete[] this->maze_data;
    delete[] this->maze_record;
}


void MyWidget::on_hand_btn_clicked()
{
    if (this->maze_record) {
        // 如果已经设置则重新初始化
        for (int i = 0; i < this->row ; i++) {
            delete[] this->maze_data[i];
            delete[] this->maze_record[i];
        }
        delete[] this->maze_data;
        delete[] this->maze_record;
        this->maze_data = nullptr;
        this->maze_record = nullptr;
    }
    this->row = ui->x_edit->text().toInt();
    this->col = ui->y_edit->text().toInt();
    this->maze_record = new int * [this->row];
    for (int i = 0; i < this->row; i++) {
        this->maze_record[i] = new int[this->col];
    }
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->maze_record[i][j] = 0;
        }
    }
    this->resetMazeData();
    this->update();
}

void MyWidget::on_auto_btn_clicked()
{
    if (ui->x_edit->text().toInt() % 2 == 0 || ui->y_edit->text().toInt() % 2 == 0) {
        message("警告", "自动生成迷宫时请将行数与列数设为奇数");
        return;
    }
    if (this->maze_record) {
        // 如果已经设置则重新初始化
        for (int i = 0; i < this->row ; i++) {
            delete[] this->maze_data[i];
            delete[] this->maze_record[i];
        }
        delete[] this->maze_data;
        delete[] this->maze_record;
        this->maze_data = nullptr;
        this->maze_record = nullptr;
    }
    this->row = ui->x_edit->text().toInt();
    this->col = ui->y_edit->text().toInt();

    this->maze_record = autoSetMaze(this->row, this->col);
    this->resetMazeData();
    this->update();
}

void MyWidget::on_DFS_btn_clicked()
{
    this->findPathDFS();
}

void MyWidget::on_BFS_btn_clicked()
{
    this->findPathBFS();
}
