#include <QApplication>
#include <QString>
#include "maindial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainDial* w;
    w = new MainDial;

    w->setMinimumHeight(300);
    w->setMaximumHeight(300);
    w->setMinimumWidth(600);
    w->setMaximumWidth(600);

    w->show();



    return a.exec();
}
