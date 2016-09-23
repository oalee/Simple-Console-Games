#include "mydialog.h"
#include <customwidget.h>
MyDialog::MyDialog(QString p1,QString p2,QString Row,QString Col,QWidget *parent ):QWidget(parent)
{

    QGridLayout *layout = new QGridLayout;
    setLayout(layout);
    player1 = new QLineEdit(p1);
    player2 = new QLineEdit(p2);
    row = new QLineEdit(Row);
    column = new QLineEdit(Col);

    layout->addWidget(new QLabel("Player 1 :") ,0,0);
    layout->addWidget(player1,0,1);

    layout->addWidget(new QLabel("Player 2 :") ,1,0);
    layout->addWidget(player2,1,1);

        layout->addWidget(new QLabel("Row :") ,2,0);
        layout->addWidget(row,2,1);

        layout->addWidget(new QLabel("Column :") ,3,0);
        layout->addWidget(column,3,1);

        QPushButton *btn = new QPushButton("start");
        layout->addWidget(btn,4,0,1,2);
        connect(btn,SIGNAL(clicked()),this,SLOT(close()));
                connect(btn,SIGNAL(clicked()),this,SLOT(goToGame()));

}

void MyDialog::goToGame(){

    CustomWidget * wdg = new CustomWidget(row->text().toInt(),column->text().toInt(),player1->text(),player2->text());
    wdg->show();
}
