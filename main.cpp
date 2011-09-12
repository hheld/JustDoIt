#include <QtGui/QApplication>
#include <QDir>
#include <QProcessEnvironment>

#include <QxtGlobalShortcut>

#include "MainWindow.h"
#include "TaskXmlReader.h"
#include "UserData.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //------------------------------------------------

    QDir homeDir = QDir::homePath();

    if(!homeDir.exists(".justdoit"))
    {
        homeDir.mkdir(".justdoit");
    }

    QDir savePath = homeDir.absolutePath() + "/.justdoit";

    TaskXmlReader myReader(savePath.absolutePath() + "/tasks.xml");

    UserData *myUd = 0;

    if(savePath.exists("tasks.xml"))
    {
        myReader.readDocument();
        myUd = myReader.uData();
    }
    else
    {
        myUd = new UserData(QProcessEnvironment::systemEnvironment().value("USER"));
    }

    //------------------------------------------------

    MainWindow w;

    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(&w);
    QObject::connect(shortcut, SIGNAL(activated()), &w, SLOT(toggleVisibility()));
    shortcut->setShortcut(QKeySequence("Ctrl+Shift+F11"));

    w.setUsrData(myUd);
    w.setSaveFileName(savePath.absolutePath() + "/tasks.xml");
    w.show();

    return a.exec();
}
