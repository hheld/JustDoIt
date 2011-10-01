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

#include <QVector>
#include <QPainter>

#include "TaskTableColorDoneDelegate.h"
#include "TaskTableModel.h"
#include "TaskSortFilterProxyModel.h"
#include "Task.h"

TaskTableColorDoneDelegate::TaskTableColorDoneDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void TaskTableColorDoneDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const TaskSortFilterProxyModel *modelProxy = static_cast<const TaskSortFilterProxyModel*>(index.model());
    const TaskTableModel *model = static_cast<const TaskTableModel*>(modelProxy->sourceModel());

    const QVector<Task*> allTasks = model->getTasks();

    bool isDone = allTasks[modelProxy->mapToSource(index).row()]->done();

    QStyleOptionViewItem newOption(option);

    if(isDone)
    {
        newOption.palette.setColor(QPalette::Text, QColor(0, 200, 0));
    }
    else
    {
        newOption.palette.setColor(QPalette::Text, QColor(200, 0, 0));
    }

    QStyledItemDelegate::paint(painter, newOption, index);
}
