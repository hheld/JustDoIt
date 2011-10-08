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

#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QString>

class TaskPrivate;

class Task
{
public:
    Task();
    ~Task();

    const QDateTime& startDate() const;
    void startDate(const QDateTime &startDate);

    const QDateTime& endDate() const;
    void endDate(const QDateTime &endDate);

    const QDateTime& dueDate() const;
    void dueDate(const QDateTime &dueDate);

    const QString& title() const;
    void title(const QString &title);

    const QString& description() const;
    void description(const QString &description);

    const qint32& id() const;
    void id(const qint32 &id);

    const QString& location() const;
    void location(const QString &location);

    const QString& category() const;
    void category(const QString &category);

    const bool& done() const;
    void done(const bool &done);

    const int& recurrenceIntervalInMinutes() const;
    void recurrenceIntervalInMinutes(const int &interval);

    //-------------------------------------------------

    bool operator==(const Task &task) const;

    //-------------------------------------------------

    static QString DateTimeFormat;
    static qint32 NumOfTasks;

private:
    TaskPrivate *d_ptr;

    Q_DISABLE_COPY(Task)
    Q_DECLARE_PRIVATE(Task)
};

#endif // TASK_H
