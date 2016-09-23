
#include <QApplication>
#include <mydialog.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyDialog d("Player 1","Player 2","11","11");
    d.show();
    return a.exec();
}
