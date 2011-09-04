#ifndef TASKXMLWRITER_H
#define TASKXMLWRITER_H

class QXmlStreamWriter;

class TaskXmlWriter
{
public:
    TaskXmlWriter();
    ~TaskXmlWriter();

private:
    QXmlStreamWriter *xmlWriter;
};

#endif // TASKXMLWRITER_H
