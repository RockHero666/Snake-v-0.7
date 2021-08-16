#ifndef SNAKE_H
#define SNAKE_H
#include<QMainWindow>
#include <QKeyEvent>
#include<QWidget>


namespace Ui {
class Snake;
}

class Snake : public QMainWindow {
Q_OBJECT
  public:
    Snake(QWidget *parent = nullptr);
    virtual ~Snake();

  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

  private:
     Ui::Snake *ui;// указатель интерфейса
      QImage dot;
      QImage head;
      QImage apple;
      QImage tale;
      QPixmap pix;
      QPalette palette;


      static const int B_WIDTH = 340;
      static const int B_HEIGHT = 420;
      static const int DOT_SIZE = 10;
      static const int ALL_DOTS = 1428;// 32*42
      static const int RAND_POS = 29;


      enum HeadCourse
      {
          RIGHT,
          DOWN,
          LEFT,
          UP
      };


      int delay = 140; // задержка обновления игры в мс.
      int timerId;
      int dots; // длина змеи
      int apple_x;
      int apple_y;
      HeadCourse hc = RIGHT;


      int x[ALL_DOTS];
      int y[ALL_DOTS];

      bool leftDirection; // блокираторы нажатия
      bool rightDirection;//
      bool upDirection;   //
      bool downDirection; // неверных кнопок
      bool inGame; // проверка на конец игры
      bool doMove; // переменная для того что бы не багало передвижение

      void loadImages();
      void initGame();
      void locateApple();
      void checkApple();
      void checkCollision();
      void move();
      void doDrawing();
      void gameOver(QPainter &);
      void headRotate(HeadCourse &,const HeadCourse &);

      void Ui_setting();
private slots:
      void restart();

};

#endif // SNAKE_H
