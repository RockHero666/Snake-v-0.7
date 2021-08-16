#include <QPainter>
#include <QTime>
#include <windows.h>
#include <QFile>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include "snake.h"
#include "ui_snake.h"


Snake::Snake(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Snake) {

    this->setWindowFlags(Qt::FramelessWindowHint); // отключение вин окна



    Ui_setting(); // подключение дизайнера и его обработка

    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;
    doMove = true;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();

    palette.setBrush(QPalette::Background, pix);
    this->setPalette(palette);

    initGame();
}



void Snake::Ui_setting()
{
    ui->setupUi(this);

    QFile file(":/button_style.css"); // рестарт
    file.open(QFile::ReadOnly);
    ui->pushButton->setStyleSheet(file.readAll());
    file.close();

    file.setFileName(":/button_style.css"); // меню
    file.open(QFile::ReadOnly);
    ui->pushButton_2->setStyleSheet(file.readAll());
    file.close();

    file.setFileName(":/button_style3.css"); // повер
    file.open(QFile::ReadOnly);
    ui->pushButton_3->setStyleSheet(file.readAll());
    file.close();

    file.setFileName(":/button_style2.css"); // аров ап
    file.open(QFile::ReadOnly);
    ui->arrow_up->setStyleSheet(file.readAll());
    file.close();

    file.setFileName(":/button_style4.css"); // аров райт
    file.open(QFile::ReadOnly);
    ui->arrow_right->setStyleSheet(file.readAll());
    file.close();

    file.setFileName(":/button_style5.css"); // аров довн
    file.open(QFile::ReadOnly);
    ui->arrow_down->setStyleSheet(file.readAll());
    file.close();

    file.setFileName(":/button_style6.css"); // аров лефт
    file.open(QFile::ReadOnly);
    ui->arrow_left->setStyleSheet(file.readAll());
    file.close();



    ui->pushButton->setGeometry(25,330,55,35);
    ui->pushButton_2->setGeometry(25,375,55,35);
    ui->pushButton_3->setGeometry(140,330,55,55);

    ui->arrow_up->setGeometry(280,340,20,20);
    ui->arrow_right->setGeometry(300,360,20,20);
    ui->arrow_left->setGeometry(260,360,20,20);
    ui->arrow_down->setGeometry(280,380,20,20);


    connect(ui->pushButton_3, &QPushButton::clicked, qApp, QApplication::quit);
    connect(ui->pushButton,&QPushButton::clicked,this,&Snake::restart);
   // connect(ui->arrow_up, &QPushButton::clicked, qApp, Qt::Key::Key_Up);

    setFocus();
}



void Snake::loadImages() {

    pix.load("snakeF.png");
    dot.load("snake.png");
   // tale.load("tale.png");
    head.load("head.png");
    apple.load("apple.png");

}

void Snake::initGame() {

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 70 - z * 10;
        y[z] = 70;
    }

    locateApple();

    timerId = startTimer(delay);
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++)
        {

           if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    } else {

        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp) {

    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2)); // точка старта для отрисовки
    qp.drawText(-textWidth/2, 0, message); // по x выход за точку для полного центрирования


}

void Snake::checkApple() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
        locateApple();
    }
}

void Snake::move() {

    for (int i = dots; i > 0; i--) { // поочередное записование данных из хваста в следующий блок тела до головы
        x[i] = x[(i - 1)];           // голова расщитывается ниже через bool метки
        y[i] = y[(i - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
    doMove = true;
}

void Snake::checkCollision() { // проверка рабочая но укправление беда
    if(dots>4)// если их меньше то и проверять не надо
    for (int i = dots; i > 0; i--) {
        if ((x[0] == x[i]) && (y[0] == y[i])) { // проверка на голову в теле
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT-100) { // -100 от того что размер окна игры 300 на 300  а всего окна 340 на 420
        inGame = false;
    }

    if (y[0] < 20) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH-20) {
        inGame = false;
    }

    if (x[0] < 20) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

void Snake::locateApple() {

    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec()));

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE+20); // +20 из за размера интерфейса  что бы за него не улетало

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE+20);

    for (int i = 0; i < dots; ++i) {
        if(apple_x == x[i] && apple_y==y[i])
            locateApple();
    }
}

void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (inGame) {

        checkApple();
        checkCollision();
        move();
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if (key == Qt::Key_R||key == Qt::Key_K)
    {
        Snake::restart();
    }

    if(doMove)
    {

      if ((key == Qt::Key_Left) && (!rightDirection)) {
          leftDirection = true;
          upDirection = false;
          downDirection = false;
          headRotate(hc,HeadCourse(LEFT));
          hc=LEFT;
         }

      else if ((key == Qt::Key_Right) && (!leftDirection)) {
          rightDirection = true;
          upDirection = false;
          downDirection = false;
          headRotate(hc,HeadCourse(RIGHT));
           hc=RIGHT;

         }

      else if ((key == Qt::Key_Up) && (!downDirection)) {
            upDirection = true;
           rightDirection = false;
            leftDirection = false;
             headRotate(hc,HeadCourse(UP));
             hc=UP;
         }

      else if ((key == Qt::Key_Down) && (!upDirection)) {
         downDirection = true;
            rightDirection = false;
         leftDirection = false;
         headRotate(hc,HeadCourse(DOWN));
          hc=DOWN;
         }

    QWidget::keyPressEvent(e);

    doMove = false;

    }
}

void Snake::restart()
{
     leftDirection = false;
     rightDirection = true;
     upDirection = false;
     downDirection = false;
     inGame = true;
     doMove = true;
     hc=RIGHT;
     head.load("head.png");

     for (int z = 0; z < dots; z++) {
         x[z] = 0;
         y[z] = 0;
     }
     killTimer(timerId);
     palette.setBrush(QPalette::Background, pix);
     this->setPalette(palette);
     Snake::initGame();
     setFocus();
}


 void Snake::headRotate(HeadCourse &headcourse,const HeadCourse &course)
 {

     QPoint center = head.rect().center();
     QMatrix matrix;
     matrix.translate(center.x(), center.y());

     switch(headcourse)
     {
     case HeadCourse::UP:
     {

         switch(course)
         {
         case HeadCourse::RIGHT:
         {
             matrix.rotate(90);
             break;
         }
         case HeadCourse::LEFT:
         {
              matrix.rotate(270);
             break;
         }


         }

         break;
     }

     case HeadCourse::RIGHT:
     {
         switch(course)
         {
         case HeadCourse::UP:
         {
             matrix.rotate(270);
             break;
         }

         case HeadCourse::DOWN:
         {
             matrix.rotate(90);
             break;
         }
         }

         break;
     }

     case HeadCourse::LEFT:
     {
         switch(course)
         {
         case HeadCourse::UP:
         {
             matrix.rotate(90);
             break;
         }

         case HeadCourse::DOWN:
         {
             matrix.rotate(270);
             break;
         }
         }
         break;
     }


     case HeadCourse::DOWN:
     {
         switch(course)
         {
         case HeadCourse::RIGHT:
         {
             matrix.rotate(270);
             break;
         }

         case HeadCourse::LEFT:
         {
             matrix.rotate(90);
             break;
         }
         }
         break;
     }


     }




     head = head.transformed(matrix);
 }


Snake::~Snake()
{
    delete ui;
}
