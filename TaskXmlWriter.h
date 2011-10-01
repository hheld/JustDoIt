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

#ifndef TASKXMLWRITER_H
#define TASKXMLWRITER_H

#include <QString>

class QXmlStreamWriter;
class UserData;

class TaskXmlWriter
{
public:
    explicit TaskXmlWriter(const QString &xmlFileName);
    ~TaskXmlWriter();

    void writeDocument();
    UserData* uData();
    void uData(UserData *uDat);

private:
    QXmlStreamWriter *xmlWriter;
    UserData *userData;
    QString fileName;

    void setOptions();
    void writeHeader();
    void writeFooter();
};

#endif // TASKXMLWRITER_H
