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

    void addCategory(const QString &category);
    void addLocation(const QString &location);
    void addTask(Task *task);

    const QString& name() const;

    const QStringList& categories() const;
    QStringList& categories();

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
