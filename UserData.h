#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QStringList>
#include <QVector>

class UserDataPrivate;
class Task;

class UserData
{
public:
    UserData(const QString &name);
    ~UserData();

    void addGroup(const QString &group);
    void addLocation(const QString &location);
    void addTask(Task *task);

    const QString& name() const;

    const QStringList& groups() const;
    QStringList& groups();

    const QStringList& locations() const;
    QStringList& locations();

    const QVector<Task*>& tasks() const;
    QVector<Task*>& tasks();

private:
    UserDataPrivate *d_ptr;

    Q_DISABLE_COPY(UserData)
    Q_DECLARE_PRIVATE(UserData)
};

#endif // USERDATA_H
