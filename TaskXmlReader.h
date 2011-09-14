#ifndef TASKXMLREADER_H
#define TASKXMLREADER_H

#include <QString>

class QXmlStreamReader;
class UserData;

class TaskXmlReader
{
public:
    explicit TaskXmlReader(const QString &xmlFileName);
    ~TaskXmlReader();

    void readDocument();
    UserData* uData();
    void uData(UserData *uDat);

private:
    QXmlStreamReader *xmlReader;
    UserData *userData;
    QString fileName;

    void readUserName();
    void readLocation();
    void readGroup();
    void readTask();
};

#endif // TASKXMLREADER_H
