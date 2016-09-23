#include "customwidget.h"
#include <QGridLayout>
#include <QAbstractButton>
#include <QPushButton>
#include <mydialog.h>
#include<QMessageBox>
#include <QLabel>
#include <QScrollArea>

class MyButtom:public QPushButton{
public:
    int row,column;
    MyButtom(int r, int c , QWidget * parent = 0):QPushButton(parent){
        row = r;
        column = c;

    }
};

CustomWidget::CustomWidget(int row, int column , QString P1, QString P2 , QWidget*parent):QWidget(parent)
{
//    isEmpty = new bool*[row-1];
//    for(int i = 0 ; i < row -1 ; i++)
//        isEmpty[i] = new bool[column-1];
    p1 = P1;

    p2 = P2;
    this->row = row;
    this->column=  column;
    QSize dotSize(25,25);
    QSize hlineSize(50,25);
    QSize VlineSize(25,50);
    QSize LabSize(50,50);
    QGridLayout *layout = new QGridLayout;
    setLayout(layout);
    QPixmap *pix = new QPixmap(":/dotIcon.png");
    QIcon *icon = new QIcon(*pix);

    horizontalLine = new MyButtom **[row];
    for(int i = 0 ; i < row ; i++)
        horizontalLine[i] = new MyButtom*[column -1];
    verticalLine = new MyButtom **[row -1];
    for(int i = 0 ; i < row-1 ; i++)
        verticalLine[i] = new MyButtom *[column];
    label = new QLabel**[row -1];
    for(int i = 0 ; i < row-1 ; i++)
        label[i] = new QLabel*[column-1];
    for(int i = 0 ; i < row-1 ; i++)
        for(int j = 0 ; j < column -1 ; j++){
            label[i][j] = new  QLabel;
            label[i][j]->setFixedSize(LabSize);
            //label[i][j]->setTextFormat(Qt::TextFormat);
            label[i][j]->setAlignment(Qt::AlignCenter);
            //isEmpty[i][j] = true;
        }
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < column -1 ; j++){
            horizontalLine[i][j] = new MyButtom(i,j);
            horizontalLine[i][j]->setFixedSize(hlineSize);
            connect(horizontalLine[i][j],SIGNAL(clicked()),this,SLOT(slotHor()));
        }
    for(int i = 0 ; i < row-1 ; i++)
        for(int j = 0 ; j < column  ; j++){
            verticalLine[i][j] = new MyButtom(i,j);
            verticalLine[i][j]->setFixedSize(VlineSize);

            connect(verticalLine[i][j],SIGNAL(clicked()),this,SLOT(slotVer()));
        }
    currentPlayer = new QLabel(p1 + " turn");
    p1ScoreLabe = new QLabel(p1 + " score : 0");
    p2ScoreLabe = new QLabel(p2 + " score : 0");
    layout->addWidget(p1ScoreLabe,0,0,1,5);
    layout->addWidget(currentPlayer,1,0,2,4);
    layout->addWidget(p2ScoreLabe,0,6,1,9);
    QPalette pal = QPushButton().palette();
    pal.setColor(QPalette::Button, QColor(Qt::black));
    layout->setSpacing(0);

    for (int r = 0 ; r < 2*(row -1) ; r+=2)
    {
        QPushButton *temp =new QPushButton;

//        temp->setIconSize(dotSize);
//        temp->setIcon(*icon);

        temp->setEnabled(false);
        temp->setFixedSize(dotSize);
        temp->setFlat(true);
        temp->setAutoFillBackground(true);
        temp->setPalette(pal);

        layout->addWidget(temp,r + 2 + 1,0); // first dot
        for(int c = 0 ; c < (column -1)*2 ; c+=2)
        {
            layout->addWidget(horizontalLine[r/2][c/2],r+ 2 + 1,c+1);

            QPushButton *temp2 =new QPushButton;
            temp2->setEnabled(false);

            temp2->setFixedSize(dotSize);
            temp2->setFlat(true);
            temp2->setAutoFillBackground(true);
            temp2->setPalette(pal);

            layout->addWidget(temp2 ,r + 2 + 1,c+2);

        }
        layout->addWidget(verticalLine[r/2][0],r+1 + 1 + 2,0);

        for(int c = 0 ; c < (column -1)*2 ; c+=2)
        {
            layout->addWidget(label[r/2][c/2] ,r+1 + 2 + 1,c+1);

            layout->addWidget(verticalLine[r/2][c/2 +1],r+1 + 1 + 2,c+2);

        }


    }
    QPushButton *temp =new QPushButton;
    temp->setEnabled(false);
    temp->setFixedSize(dotSize);
    temp->setFlat(true);
    temp->setAutoFillBackground(true);
    temp->setPalette(pal);

    int r = row -1;
    r*=2;
    layout->addWidget(temp,r+2 + 1,0); // first dot
    for(int c = 0 ; c < (column -1)*2 ; c+=2)
    {
        layout->addWidget(horizontalLine[r/2][c/2],r + 2 + 1,c+1);

        QPushButton *temp2 =new QPushButton;
        temp2->setEnabled(false);
        temp2->setFixedSize(dotSize);
        temp2->setFlat(true);
        temp2->setAutoFillBackground(true);
        temp2->setPalette(pal);

        layout->addWidget(temp2 ,r + 2 + 1,c+2);

    }
    QScrollArea* scrollArea = new QScrollArea();
       scrollArea->setWidget(this);

       scrollArea->resize(900, 900);
       scrollArea->show();


}

void CustomWidget::slotHor()
{
    MyButtom *button = (MyButtom *)sender();
    bool changeFlag = true;
    int r = button->row;
    int c = button->column;
    if( r<row -1)
    {
        if(! (horizontalLine[r+1][c]->isEnabled() || verticalLine[r][c]->isEnabled() || verticalLine[r][c+1]->isEnabled()))
        {
            if(player1Run)   {
            label[r][c]->setText(p1);
            player1Score++;

            label[r][c]->autoFillBackground();

            label[r][c]->setStyleSheet("QLabel { background-color : pink; color : black; }");

            p1ScoreLabe->setText(p1 + " score : "+ QString::number(player1Score));

            }
            else
            {
            label[r][c]->setText(p2);
            player2Score++;

            label[r][c]->autoFillBackground();

            label[r][c]->setStyleSheet("QLabel { background-color : yellow; color : black; }");

            p2ScoreLabe->setText(p2 + " score : "+ QString::number(player2Score));

            }
            changeFlag = false;
        }

    }
    if(r != 0)
    {
        if(!(horizontalLine[r-1][c]->isEnabled() || verticalLine[r-1][c]->isEnabled() || verticalLine[r-1   ][c+1]->isEnabled()))
        {
            if(player1Run)   {
            label[r-1][c]->setText(p1);
            player1Score++;
            label[r-1][c]->autoFillBackground();

            label[r-1][c]->setStyleSheet("QLabel { background-color : pink; color : black; }");

            p1ScoreLabe->setText(p1 + " score : "+ QString::number(player1Score));

            }
            else
            {
            label[r-1][c]->setText(p2);
            label[r-1][c]->autoFillBackground();

            label[r-1][c]->setStyleSheet("QLabel { background-color : yellow; color : black; }");

            player2Score++;
            p2ScoreLabe->setText(p2 + " score : "+ QString::number(player2Score));

            }
            changeFlag = false;
        }

    }

    button->setFlat(true);
    QPalette pal = button->palette();
    if(player1Run)
    pal.setColor(QPalette::Button, QColor(Qt::blue));
    else
        pal.setColor(QPalette::Button, QColor(Qt::red));
    if(changeFlag){
    player1Run = !player1Run;
    if(player1Run)
        currentPlayer->setText(p1 + " turn");
    else
        currentPlayer->setText(p2 + " turn");
    }
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
    button->setEnabled(false);
    //btn->set
    isEnd();
}

void CustomWidget::slotVer()
{
    MyButtom *button = (MyButtom *)sender();

    bool changFlag = true;
    int r = button->row;
    int c = button->column;

    if (c !=0 )
    {
        if(!verticalLine[r][c-1]->isEnabled() && !horizontalLine[r][c-1]->isEnabled() &&!horizontalLine[r+1][c-1]->isEnabled() )
        {
            if(player1Run)   {
            label[r][c-1]->setText(p1);
            player1Score++;
            p1ScoreLabe->setText(p1 + " score : "+ QString::number(player1Score));
            label[r][c-1]->autoFillBackground();

            label[r][c-1]->setStyleSheet("QLabel { background-color : pink; color : black; }");

            }
            else
            {
            label[r][c-1]->setText(p2);
            label[r][c-1]->autoFillBackground();

            label[r][c-1]->setStyleSheet("QLabel { background-color : yellow; color : black; }");


            player2Score++;
            p2ScoreLabe->setText(p2 + " score : "+ QString::number(player2Score));

            }
            changFlag = false;
        }
    }
    if(c != column -1)
    {
        if(!verticalLine[r][c+1]->isEnabled() && !horizontalLine[r][c]->isEnabled() &&!horizontalLine[r+1][c]->isEnabled() )
        {
            if(player1Run)   {
            label[r][c]->setText(p1);
       //     label[r][c]->autoFillBackground();
            label[r][c]->autoFillBackground();

            label[r][c]->setStyleSheet("QLabel { background-color : pink; color : black; }");
            player1Score++;
            p1ScoreLabe->setText(p1 + " score : "+ QString::number(player1Score));

            }
            else
            {
            label[r][c]->setText(p2);
            label[r][c]->autoFillBackground();

            label[r][c]->setStyleSheet("QLabel { background-color : yellow; color : black; }");

            player2Score++;
            p2ScoreLabe->setText(p2 + " score : "+  QString::number(player2Score));

            }
            changFlag = false;
        }

    }



    button->setFlat(true);
    QPalette pal = button->palette();
    if(player1Run)
    pal.setColor(QPalette::Button, QColor(Qt::blue));
    else
        pal.setColor(QPalette::Button, QColor(Qt::red));
    if(changFlag){
    player1Run = !player1Run;
    if(player1Run)
        currentPlayer->setText(p1 + " turn");
    else
        currentPlayer->setText(p2 + " turn");
    }
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
    button->setEnabled(false);
    isEnd();

}


void CustomWidget::isEnd()
{
    for(int i = 0 ; i < row -1 ; i++)
        for(int j = 0  ; j < column -1 ; j++)
            if(label[i][j]->text() == "")
                return ;

    QMessageBox* msgBox = new QMessageBox;
    msgBox->setIcon(QMessageBox::Question);
    msgBox->setText(player1Score > player2Score ? p1 + " won" : player2Score > player1Score ? p2 + " won": " Draw");
    QPushButton *connectButton = msgBox->addButton(tr("Play Again"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox->addButton(QMessageBox::Abort);
    abortButton->setText("Exit");
        msgBox->exec();


    if (msgBox->clickedButton() == connectButton) {
        MyDialog *D= new MyDialog(p1,p2,QString::number(row),QString::number(column));
       D->show();

       this->close();
    } else if (msgBox->clickedButton() == abortButton) {
       // msgBox.destroy();
        this->close();
    }

}
