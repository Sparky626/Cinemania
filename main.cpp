#include "cinemania.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CineMania w;
    w.show();
    return a.exec();
}
