#include <QtGui/QApplication>
#include "MainWindow.h"

#include "TaskXmlReader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //------------------------------------------------

    TaskXmlReader myReader("myTasks.xml");

    myReader.readDocument();

    UserData *myUd = myReader.uData();

    //------------------------------------------------

    MainWindow w;
    w.setUsrData(myUd);
    w.show();

    return a.exec();
}
