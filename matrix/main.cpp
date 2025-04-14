#include <QApplication>
#include "matrixwidget.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MatrixWidget w;
    w.show();
    return a.exec();
}
