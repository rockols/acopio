#include "mainwindow.h"
#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    createConnection();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
