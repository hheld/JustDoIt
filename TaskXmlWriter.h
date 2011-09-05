#ifndef TASKXMLWRITER_H
#define TASKXMLWRITER_H

#include <QString>

class QXmlStreamWriter;
class UserData;

class TaskXmlWriter
{
public:
    explicit TaskXmlWriter(const QString &xmlFileName);
    ~TaskXmlWriter();

    void writeDocument();
    UserData* userDataPtr();

private:
    QXmlStreamWriter *xmlWriter;
    UserData *userData;
    QString fileName;

    void setOptions();
    void writeHeader();
    void writeFooter();
};

#endif // TASKXMLWRITER_H
