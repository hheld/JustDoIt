/*
 * This file is part of JustDoIt.
 *
 * Copyright 2011 Harald Held <harald.held@gmail.com>
 *
 * JustDoIt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JustDoIt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JustDoIt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCryptographicHash>

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
    qint32 recurrenceInterval;
    bool isUnprocessed;
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
    d->recurrenceInterval = 0;
    d->isUnprocessed = true;
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
    return hash() == task.hash();
}

const int & Task::recurrenceIntervalInMinutes() const
{
    Q_D(const Task);

    return d->recurrenceInterval;
}

void Task::recurrenceIntervalInMinutes(const int &interval)
{
    Q_D(Task);

    d->recurrenceInterval = interval;
}

const bool & Task::unprocessed() const
{
    Q_D(const Task);

    return d->isUnprocessed;
}

void Task::unprocessed(const bool &isUnprocessed)
{
    Q_D(Task);

    d->isUnprocessed = isUnprocessed;
}

const QByteArray Task::hash() const
{
    Q_D(const Task);

    QCryptographicHash myHash(QCryptographicHash::Sha1);

    QByteArray taskData;

    taskData.append(d->startDate.toString());
    taskData.append(d->endDate.toString());
    taskData.append(d->dueDate.toString());
    taskData.append(d->title);
    taskData.append(d->description);
    taskData.append(d->location);
    taskData.append(d->category);
    taskData.append(QString::number(d->done));
    taskData.append(QString::number(d->recurrenceInterval));
    taskData.append(QString::number(d->isUnprocessed));

    myHash.addData(taskData);

    return myHash.result().toHex();
}
