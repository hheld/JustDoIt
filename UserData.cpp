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

#include "UserData.h"
#include "Task.h"

struct UserDataPrivate
{
    UserDataPrivate(UserData *q) : q_ptr(q) { }

    // parameters ------------------------------------
    QString name;
    QStringList categories;
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

void UserData::addCategory(const QString &category)
{
    Q_D(UserData);

    if(!d->categories.contains(category))
    {
        d->categories.append(category);
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

const QStringList & UserData::categories() const
{
    Q_D(const UserData);

    return d->categories;
}

QStringList & UserData::categories()
{
    Q_D(UserData);

    return d->categories;
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
