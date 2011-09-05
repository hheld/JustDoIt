#include <QXmlStreamWriter>
#include <QFile>

#include "TaskXmlWriter.h"

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

    xmlWriter->writeStartElement("User");
    xmlWriter->writeAttribute("name", "usr");
    xmlWriter->writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    xmlWriter->writeAttribute("xsi:noNamespaceSchemaLocation", "Tasks.xsd");

    // realms
    xmlWriter->writeStartElement("Realms");
    xmlWriter->writeEmptyElement("Realm");
    xmlWriter->writeAttribute("name", "r1");
    xmlWriter->writeEmptyElement("Realm");
    xmlWriter->writeAttribute("name", "r2");
    xmlWriter->writeEndElement();

    // locations
    xmlWriter->writeStartElement("Locations");
    xmlWriter->writeEmptyElement("Location");
    xmlWriter->writeAttribute("name", "l1");
    xmlWriter->writeEmptyElement("Location");
    xmlWriter->writeAttribute("name", "l2");
    xmlWriter->writeEndElement();

    // tasks
    xmlWriter->writeStartElement("Tasks");

    xmlWriter->writeStartElement("Task");
    xmlWriter->writeAttribute("done", "false");
    xmlWriter->writeAttribute("id", "0");
    xmlWriter->writeAttribute("location", "l1");
    xmlWriter->writeAttribute("realm", "r1");
    xmlWriter->writeTextElement("startDate", "2011-09-05T21:57:00");
    xmlWriter->writeTextElement("endDate", "2011-09-05T21:57:00");
    xmlWriter->writeTextElement("dueDate", "2011-09-05T21:57:00");
    xmlWriter->writeTextElement("title", "t1");
    xmlWriter->writeTextElement("description", "desc1");
    xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("Task");
    xmlWriter->writeAttribute("done", "false");
    xmlWriter->writeAttribute("id", "1");
    xmlWriter->writeAttribute("location", "l2");
    xmlWriter->writeAttribute("realm", "r2");
    xmlWriter->writeTextElement("startDate", "2011-09-06T21:57:00");
    xmlWriter->writeTextElement("endDate", "2011-09-06T21:57:00");
    xmlWriter->writeTextElement("dueDate", "2011-09-06T21:57:00");
    xmlWriter->writeTextElement("title", "t2");
    xmlWriter->writeTextElement("description", "desc2");
    xmlWriter->writeEndElement();

    xmlWriter->writeEndElement(); // Tasks

    xmlWriter->writeEndElement(); // User

    writeFooter();

    //------------------------------------------------

    xmlFile.close();
}

UserData * TaskXmlWriter::userDataPtr()
{
    return userData;
}
