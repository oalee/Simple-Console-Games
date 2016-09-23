#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include<QtWidgets>

class MyButtom;

class CustomWidget:public QWidget
{
    Q_OBJECT

    MyButtom ***horizontalLine;
    MyButtom ***verticalLine;
    QLabel ***label;
    int row,column;
    bool player1Run = true;
    int player1Score =0;
    int player2Score =0;
    QString p1;
    QString p2;
    QLabel *p1ScoreLabe;
    QLabel *p2ScoreLabe;
    QLabel *currentPlayer;
    void isEnd();
public:
    CustomWidget(int row ,int column ,QString , QString, QWidget * parent = 0);

public slots:
    void slotHor();
    void slotVer();
};

#endif // CUSTOMWIDGET_H
