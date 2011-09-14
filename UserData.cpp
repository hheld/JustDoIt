#include "UserData.h"
#include "Task.h"

struct UserDataPrivate
{
    UserDataPrivate(UserData *q) : q_ptr(q) { }

    // parameters ------------------------------------
    QString name;
    QStringList groups;
    QStringList locations;
    QVector<Task*> tasks;
    // -----------------------------------------------

    UserData *q_ptr;
    Q_DECLARE_PUBLIC(UserData)
};

//----------------------------------------------------

UserData::UserData(const QString &name)
    : d_ptr(new UserDataPrivate(this))
{
    Q_D(UserData);

    d->name = name;
}

UserData::~UserData()
{
    Q_D(UserData);

    for(int i=0; i<d->tasks.size(); ++i)
    {
        delete d->tasks[i];
        d->tasks[i] = 0;
    }

    d->tasks.clear();

    delete d_ptr;
    d_ptr = 0;
}

void UserData::addGroup(const QString &group)
{
    Q_D(UserData);

    if(!d->groups.contains(group))
    {
        d->groups.append(group);
    }
}

void UserData::addLocation(const QString &location)
{
    Q_D(UserData);

    if(!d->locations.contains(location))
    {
        d->locations.append(location);
    }
}

void UserData::addTask(Task *task)
{
    Q_D(UserData);

    if(!d->tasks.contains(task))
    {
        d->tasks.append(task);
    }
}

const QString & UserData::name() const
{
    Q_D(const UserData);

    return d->name;
}

const QStringList & UserData::groups() const
{
    Q_D(const UserData);

    return d->groups;
}

QStringList & UserData::groups()
{
    Q_D(UserData);

    return d->groups;
}

const QStringList & UserData::locations() const
{
    Q_D(const UserData);

    return d->locations;
}

QStringList & UserData::locations()
{
    Q_D(UserData);

    return d->locations;
}

const QVector<Task*> & UserData::tasks() const
{
    Q_D(const UserData);

    return d->tasks;
}

QVector<Task*> & UserData::tasks()
{
    Q_D(UserData);

    return d->tasks;
}
