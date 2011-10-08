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

#include <QtAlgorithms>
#include <QtGlobal>
#include <QTimer>

#include "TaskTableModel.h"
#include "Task.h"

TaskTableModel::TaskTableModel(const QVector<Task*> allTasks, QObject *parent) :
    QAbstractTableModel(parent),
    allTasks(allTasks)
{
    /*  Since we display something like "xxx days left", in theory it should be possible to leave the application open, never change data, and therefore never get an update
        on these values. Therefore, we just reset the view every 6 hours, that shouldn't have any performance issues and this admittedly rare occasion is handled correctly. */

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(resetView()));
    timer->start(1000 * 60 * 60 * 6);
}

TaskTableModel::~TaskTableModel()
{

}

int TaskTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return allTasks.size();
}

int TaskTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 10;
}

QVariant TaskTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= allTasks.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::CheckStateRole && index.column() == 3)
    {
        Task* task = allTasks.at(index.row());

        return task->done() ? Qt::Checked : Qt::Unchecked;
    }

    if (role == Qt::DisplayRole)
    {
        Task* task = allTasks.at(index.row());

        if (index.column() == 0) return task->id();
        else if (index.column() == 1) return task->location();
        else if (index.column() == 2) return task->category();
        else if (index.column() == 3) return task->done() ? tr("Finished" ): QString::number(qMax(QDateTime::currentDateTime().daysTo(task->dueDate()), 0)) + tr(" days left");
//        else if (index.column() == 3) return QVariant();
        else if (index.column() == 4) return task->startDate();
        else if (index.column() == 5) return task->endDate();
        else if (index.column() == 6) return task->dueDate();
        else if (index.column() == 7) return task->title();
        else if (index.column() == 8) return task->description();
        else if (index.column() == 9) return task->recurrenceIntervalInMinutes();
    }

    return QVariant();
}

QVariant TaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return tr("Id");

        case 1:
            return tr("Location");

        case 2:
            return tr("Category");

        case 3:
            return tr("Done");

        case 4:
            return tr("Start date");

        case 5:
            return tr("End date");

        case 6:
            return tr("Due date");

        case 7:
            return tr("Title");

        case 8:
            return tr("Description");

        case 9:
            return tr("Recurrence");

        default:
            return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags TaskTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if(index.column() == 0
            || index.column() == 4
            || index.column() == 5)
    {
        return QAbstractTableModel::flags(index);
    }

    if (index.column() == 3)
    {
        return QAbstractTableModel::flags(index) | Qt::ItemIsUserCheckable;
    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool TaskTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && (role == Qt::EditRole || role == Qt::CheckStateRole))
    {
        int row = index.row();

        Task *currentTask = allTasks.at(row);

        if (index.column() == 0) currentTask->id(value.toInt());
        else if (index.column() == 1) currentTask->location(value.toString());
        else if (index.column() == 2) currentTask->category(value.toString());
        else if (index.column() == 3)
        {
            currentTask->done(value.toBool());

            if(currentTask->done())
            {
                currentTask->endDate(QDateTime::currentDateTime());

                QModelIndex endDateIndex = createIndex(index.row(), 5);
                emit(dataChanged(endDateIndex, endDateIndex));
            }
            else
            {
                currentTask->endDate(QDateTime());

                QModelIndex endDateIndex = createIndex(index.row(), 5);
                emit(dataChanged(endDateIndex, endDateIndex));
            }
        }
        else if (index.column() == 4) currentTask->startDate(value.toDateTime());
        else if (index.column() == 5) currentTask->endDate(value.toDateTime());
        else if (index.column() == 6) currentTask->dueDate(value.toDateTime());
        else if (index.column() == 7) currentTask->title(value.toString());
        else if (index.column() == 8) currentTask->description(value.toString());
        else if (index.column() == 9) currentTask->recurrenceIntervalInMinutes(value.toInt());
        else return false;

        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

bool TaskTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    beginInsertRows(index, position, position+rows-1);

    for (int row=0; row<rows; ++row)
    {
        Task *newTask = new Task();
        allTasks.append(newTask);
    }

    endInsertRows();

    return true;
}

bool TaskTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(index, position, position+rows-1);

    for (int row=0; row<rows; ++row)
    {
        allTasks.remove(position);
    }

    endRemoveRows();

    return true;
}

const QVector<Task *> & TaskTableModel::getTasks() const
{
    return allTasks;
}

void TaskTableModel::resetView()
{
    reset();
}
