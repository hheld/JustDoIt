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
    void readCategory();
    void readTask();
};

#endif // TASKXMLREADER_H
