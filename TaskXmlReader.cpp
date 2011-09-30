#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

#include "TaskXmlReader.h"
#include "UserData.h"
#include "Task.h"

TaskXmlReader::TaskXmlReader(const QString &xmlFileName)
    : xmlReader(0),
      userData(0),
      fileName(xmlFileName)
{ }

TaskXmlReader::~TaskXmlReader()
{
    delete xmlReader;
    xmlReader = 0;
}

void TaskXmlReader::readDocument()
{
    QFile xmlFile(fileName);

    if (!xmlFile.open(QFile::ReadOnly))
    {
        /// \todo do sth. here
    }

    xmlReader = new QXmlStreamReader(&xmlFile);

    while (!xmlReader->atEnd())
    {
        xmlReader->readNext();

        if(xmlReader->isStartElement())
        {
            if (xmlReader->name() == "User")
                readUserName();
            else if (xmlReader->name() == "Category")
                readCategory();
            else if (xmlReader->name() == "Location")
                readLocation();
            else if(xmlReader->name() == "Task")
                readTask();
        }
    }
    if (xmlReader->hasError())
    {
        /// \todo do error handling
        QString err = QString("%1\nLine %2, column %3").arg(xmlReader->errorString()).arg(xmlReader->lineNumber()).arg(xmlReader->columnNumber());
        qDebug() << err;
    }
}

UserData * TaskXmlReader::uData()
{
    return userData;
}

void TaskXmlReader::uData(UserData *uDat)
{
    userData = uDat;
}

void TaskXmlReader::readUserName()
{
    QString uName = xmlReader->attributes().value("name").toString();

    userData = new UserData(uName);
}

void TaskXmlReader::readLocation()
{
    QString location = xmlReader->attributes().value("name").toString();

    userData->addLocation(location);
}

void TaskXmlReader::readCategory()
{
    QString category = xmlReader->attributes().value("name").toString();

    userData->addCategory(category);
}

void TaskXmlReader::readTask()
{
    qint32 id = xmlReader->attributes().value("id").toString().toInt();
    QString location = xmlReader->attributes().value("location").toString();
    QString category = xmlReader->attributes().value("category").toString();
    bool done = xmlReader->attributes().value("done").toString() == "true" ? true : false;

    QDateTime startDate;
    QDateTime endDate;
    QDateTime dueDate;
    QString title;
    QString description;

    while(xmlReader->readNextStartElement())
    {
        if(xmlReader->name() == "startDate")
        {
            startDate = QDateTime::fromString(xmlReader->readElementText(), Task::DateTimeFormat);
        }
        else if(xmlReader->name() == "endDate")
        {
            endDate = QDateTime::fromString(xmlReader->readElementText(), Task::DateTimeFormat);
        }
        else if(xmlReader->name() == "dueDate")
        {
            dueDate = QDateTime::fromString(xmlReader->readElementText(), Task::DateTimeFormat);
        }
        else if(xmlReader->name() == "title")
        {
            title = xmlReader->readElementText(QXmlStreamReader::IncludeChildElements);
        }
        else if(xmlReader->name() == "description")
        {
            description = xmlReader->readElementText();
        }
        else
        {
            xmlReader->skipCurrentElement();
        }
    }

    Task *newTask = new Task();

    newTask->id(id);
    newTask->location(location);
    newTask->category(category);
    newTask->done(done);
    newTask->startDate(startDate);
    newTask->endDate(endDate);
    newTask->dueDate(dueDate);
    newTask->title(title);
    newTask->description(description);

    userData->addTask(newTask);
}
