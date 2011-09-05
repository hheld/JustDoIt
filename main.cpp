#include <QtGui/QApplication>
#include "MainWindow.h"

#include "TaskXmlWriter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TaskXmlWriter myWriter("myTasks.xml");
    myWriter.writeDocument();

    MainWindow w;
    w.show();

    return a.exec();
}
