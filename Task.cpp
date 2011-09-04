#include "Task.h"

QString Task::DateTimeFormat = "yyyy-MM-ddTHH:mm:ss";

//----------------------------------------------------

struct TaskPrivate
{
    TaskPrivate(Task *q) : q_ptr(q) { }

    // parameters ------------------------------------
    QDateTime startDate;
    QDateTime endDate;
    QDateTime dueDate;
    QString title;
    QString description;
    qint32 id;
    QString location;
    QString realm;
    bool done;
    // -----------------------------------------------

    Task *q_ptr;
    Q_DECLARE_PUBLIC(Task)
};

//----------------------------------------------------

Task::Task()
    : d_ptr(new TaskPrivate(this))
{
}

Task::~Task()
{
    delete d_ptr;
    d_ptr = 0;
}

const QDateTime & Task::startDate() const
{
    Q_D(Task);
    return *d->startDate;
}

void Task::startDate(const QDateTime &startDate)
{
    Q_D(Task);
    d->startDate = startDate;
}

const QDateTime & Task::endDate() const
{
    Q_D(Task);
    return *d->endDate;
}

void Task::endDate(const QDateTime &endDate)
{
    Q_D(Task);
    d->endDate = endDate;
}

const QDateTime & Task::dueDate() const
{
    Q_D(Task);
    return *d->dueDate;
}

void Task::dueDate(const QDateTime &dueDate)
{
    Q_D(Task);
    d->dueDate = dueDate;
}

const QString & Task::title() const
{
    Q_D(Task);
    return *d->title;
}

void Task::title(const QString &title)
{
    Q_D(Task);
    d->title = title;
}

const QString & Task::description() const
{
    Q_D(Task);
    return *d->description;
}

void Task::description(const QString &description)
{
    Q_D(Task);
    d->description = description;
}

const qint32 & Task::id() const
{
    Q_D(Task);
    return *d->id;
}

void Task::id(const qint32 &id)
{
    Q_D(Task);
    d->id = id;
}

const QString & Task::location() const
{
    Q_D(Task);
    return *d->location;
}

void Task::location(const QString &location)
{
    Q_D(Task);
    d->location = location;
}

const QString & Task::realm() const
{
    Q_D(Task);
    return *d->realm;
}

void Task::realm(const QString &realm)
{
    Q_D(Task);
    d->realm = realm;
}

const bool & Task::done() const
{
    Q_D(Task);
    return *d->done;
}

void Task::done(const bool &done)
{
    Q_D(Task);
    d->done = done;
}
