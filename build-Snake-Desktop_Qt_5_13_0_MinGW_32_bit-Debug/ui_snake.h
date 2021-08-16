/********************************************************************************
** Form generated from reading UI file 'snake.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAKE_H
#define UI_SNAKE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Snake
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *arrow_up;
    QPushButton *arrow_down;
    QPushButton *arrow_right;
    QPushButton *arrow_left;

    void setupUi(QWidget *Snake)
    {
        if (Snake->objectName().isEmpty())
            Snake->setObjectName(QString::fromUtf8("Snake"));
        Snake->resize(400, 300);
        pushButton = new QPushButton(Snake);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 210, 80, 21));
        pushButton_2 = new QPushButton(Snake);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 260, 80, 21));
        pushButton_3 = new QPushButton(Snake);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(150, 210, 80, 21));
        arrow_up = new QPushButton(Snake);
        arrow_up->setObjectName(QString::fromUtf8("arrow_up"));
        arrow_up->setGeometry(QRect(290, 190, 80, 21));
        arrow_down = new QPushButton(Snake);
        arrow_down->setObjectName(QString::fromUtf8("arrow_down"));
        arrow_down->setGeometry(QRect(290, 260, 80, 21));
        arrow_right = new QPushButton(Snake);
        arrow_right->setObjectName(QString::fromUtf8("arrow_right"));
        arrow_right->setGeometry(QRect(340, 220, 80, 21));
        arrow_left = new QPushButton(Snake);
        arrow_left->setObjectName(QString::fromUtf8("arrow_left"));
        arrow_left->setGeometry(QRect(240, 220, 80, 21));

        retranslateUi(Snake);

        QMetaObject::connectSlotsByName(Snake);
    } // setupUi

    void retranslateUi(QWidget *Snake)
    {
        Snake->setWindowTitle(QCoreApplication::translate("Snake", "Form", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        arrow_up->setText(QString());
        arrow_down->setText(QString());
        arrow_right->setText(QString());
        arrow_left->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Snake: public Ui_Snake {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAKE_H
