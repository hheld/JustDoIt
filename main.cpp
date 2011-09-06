#include <QtGui/QApplication>
#include "MainWindow.h"

#include "TaskXmlWriter.h"
#include "UserData.h"
#include "Task.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //------------------------------------------------

    TaskXmlWriter myWriter("myTasks.xml");

    UserData *myUd = new UserData("harry");

    myWriter.uData(myUd);

    myUd->addLocation("myLoc1");
    myUd->addRealm("myRealm1");

    Task *myTask = new Task;
    myTask->description("desc1");
    myTask->done(false);
    myTask->dueDate(QDateTime::fromString("2011-09-06T22:00:00", Task::DateTimeFormat));
    myTask->startDate(QDateTime::fromString("2011-09-07T22:00:00", Task::DateTimeFormat));
    myTask->endDate(QDateTime::fromString("2011-09-08T22:00:00", Task::DateTimeFormat));
    myTask->location("here");
    myTask->realm("private");

    myUd->addTask(myTask);

    myWriter.writeDocument();

    delete myUd;

    //------------------------------------------------

    MainWindow w;
    w.show();

    return a.exec();
}
