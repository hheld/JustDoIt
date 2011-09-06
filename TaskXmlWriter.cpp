#include <QXmlStreamWriter>
#include <QFile>

#include "TaskXmlWriter.h"
#include "UserData.h"
#include "Task.h"

TaskXmlWriter::TaskXmlWriter(const QString &xmlFileName)
    : xmlWriter(0),
      userData(0),
      fileName(xmlFileName)
{ }

TaskXmlWriter::~TaskXmlWriter()
{
    delete xmlWriter;
    xmlWriter = 0;
}

void TaskXmlWriter::setOptions()
{
    xmlWriter->setAutoFormatting(true);
}

void TaskXmlWriter::writeHeader()
{
    xmlWriter->writeStartDocument();
}

void TaskXmlWriter::writeFooter()
{
    xmlWriter->writeEndDocument();
}

void TaskXmlWriter::writeDocument()
{
    QFile xmlFile(fileName);

    if (!xmlFile.open(QFile::WriteOnly))
    {
        /// \todo do sth. here
    }

    xmlWriter = new QXmlStreamWriter(&xmlFile);

    setOptions();

    //------------------------------------------------

    writeHeader();

    if(userData)
    {
        xmlWriter->writeStartElement("User");
        xmlWriter->writeAttribute("name", userData->name());
        xmlWriter->writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
        xmlWriter->writeAttribute("xsi:noNamespaceSchemaLocation", "Tasks.xsd");

        // realms
        xmlWriter->writeStartElement("Realms");

        const QStringList& allRealms = userData->realms();

        for(int i=0; i<allRealms.size(); ++i)
        {
            xmlWriter->writeEmptyElement("Realm");
            xmlWriter->writeAttribute("name", allRealms.at(i));
        }

        xmlWriter->writeEndElement();

        // locations
        xmlWriter->writeStartElement("Locations");

        const QStringList& allLocations = userData->locations();

        for(int i=0; i<allLocations.size(); ++i)
        {
            xmlWriter->writeEmptyElement("Location");
            xmlWriter->writeAttribute("name", allLocations.at(i));
        }

        xmlWriter->writeEndElement();

        // tasks
        xmlWriter->writeStartElement("Tasks");

        QVector<Task*>& allTasks = userData->tasks();

        for(int i=0; i<allTasks.size(); ++i)
        {
            Task *currentTask = allTasks.at(i);

            xmlWriter->writeStartElement("Task");
            xmlWriter->writeAttribute("done", currentTask->done() ? "true" : "false");
            xmlWriter->writeAttribute("id", QString::number(currentTask->id()));
            xmlWriter->writeAttribute("location", currentTask->location());
            xmlWriter->writeAttribute("realm", currentTask->realm());
            xmlWriter->writeTextElement("startDate", currentTask->startDate().toString(Task::DateTimeFormat));
            xmlWriter->writeTextElement("endDate", currentTask->endDate().toString(Task::DateTimeFormat));
            xmlWriter->writeTextElement("dueDate", currentTask->dueDate().toString(Task::DateTimeFormat));
            xmlWriter->writeTextElement("title", currentTask->title());
            xmlWriter->writeTextElement("description", currentTask->description());
            xmlWriter->writeEndElement();
        }

        xmlWriter->writeEndElement(); // Tasks

        xmlWriter->writeEndElement(); // User
    }

    writeFooter();

    //------------------------------------------------

    xmlFile.close();
}

UserData * TaskXmlWriter::uData()
{
    return userData;
}

void TaskXmlWriter::uData(UserData *uDat)
{
    userData = uDat;
}
