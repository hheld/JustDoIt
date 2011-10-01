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

#include "ReminderFilterProxyModel.h"

#include "TaskTableModel.h"
#include "Task.h"

#include <QDateTime>

ReminderFilterProxyModel::ReminderFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    setFilterKeyColumn(6);
}

bool ReminderFilterProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);

    // only show done, title, and due date columns
    if(source_column==6 || source_column==3 || source_column==7)
    {
        return true;
    }

    return false;
}

bool ReminderFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);

    bool accept = true;

    const TaskTableModel *model = static_cast<const TaskTableModel*>(sourceModel());

    accept = !model->getTasks().at(source_row)->done() && accept;

    QModelIndex index = sourceModel()->index(source_row, 6, source_parent);

    accept = accept && dateInRange(sourceModel()->data(index).toDateTime());

    return accept;
}

bool ReminderFilterProxyModel::dateInRange(const QDateTime &date) const
{
    // only accept if the due date is less than 2 hours in the future
    return date <= QDateTime::currentDateTime().addSecs(60*60*2);
}
