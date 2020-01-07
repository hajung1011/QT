#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setGeometry(0,0,1137,653);
    w.show();
    return a.exec();
}
