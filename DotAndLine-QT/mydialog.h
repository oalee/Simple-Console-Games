
#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QtWidgets>
class MyDialog:public QWidget
{
    Q_OBJECT
    QLineEdit * player1  ;
    QLineEdit * player2  ;
    QLineEdit * row ;
    QLineEdit * column ;

public:

    MyDialog(QString p1,QString p2,QString row,QString col,QWidget *parent = 0);

public slots:
    void goToGame();

};

#endif // MYDIALOG_H
