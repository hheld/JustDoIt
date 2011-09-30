#include "Task.h"

QString Task::DateTimeFormat = "yyyy-MM-ddTHH:mm:ss";
qint32 Task::NumOfTasks = 0;

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
    QString category;
    bool done;
    // -----------------------------------------------

    Task *q_ptr;
    Q_DECLARE_PUBLIC(Task)
};

//----------------------------------------------------

Task::Task()
    : d_ptr(new TaskPrivate(this))
{
    Q_D(Task);

    d->done = false;

    d->id = NumOfTasks;
    NumOfTasks++;

    d->startDate = QDateTime::currentDateTime();
}

Task::~Task()
{
    delete d_ptr;
    d_ptr = 0;
}

const QDateTime & Task::startDate() const
{
    Q_D(const Task);
    return d->startDate;
}

void Task::startDate(const QDateTime &startDate)
{
    Q_D(Task);
    d->startDate = startDate;
}

const QDateTime & Task::endDate() const
{
    Q_D(const Task);
    return d->endDate;
}

void Task::endDate(const QDateTime &endDate)
{
    Q_D(Task);
    d->endDate = endDate;
}

const QDateTime & Task::dueDate() const
{
    Q_D(const Task);
    return d->dueDate;
}

void Task::dueDate(const QDateTime &dueDate)
{
    Q_D(Task);
    d->dueDate = dueDate;
}

const QString & Task::title() const
{
    Q_D(const Task);
    return d->title;
}

void Task::title(const QString &title)
{
    Q_D(Task);
    d->title = title;
}

const QString & Task::description() const
{
    Q_D(const Task);
    return d->description;
}

void Task::description(const QString &description)
{
    Q_D(Task);
    d->description = description;
}

const qint32 & Task::id() const
{
    Q_D(const Task);
    return d->id;
}

void Task::id(const qint32 &id)
{
    Q_D(Task);
    d->id = id;

    if(id>NumOfTasks)
    {
        NumOfTasks = id+1;
    }
}

const QString & Task::location() const
{
    Q_D(const Task);
    return d->location;
}

void Task::location(const QString &location)
{
    Q_D(Task);
    d->location = location;
}

const QString & Task::category() const
{
    Q_D(const Task);
    return d->category;
}

void Task::category(const QString &category)
{
    Q_D(Task);
    d->category = category;
}

const bool & Task::done() const
{
    Q_D(const Task);
    return d->done;
}

void Task::done(const bool &done)
{
    Q_D(Task);
    d->done = done;
}

bool Task::operator ==(const Task &task) const
{
    Q_D(const Task);

    qint32 leftId = d->id;
    qint32 rightId = task.id();

    return leftId == rightId;
}
