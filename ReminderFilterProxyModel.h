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

#ifndef REMINDERFILTERPROXYMODEL_H
#define REMINDERFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class ReminderFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ReminderFilterProxyModel(QObject *parent = 0);

    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    bool dateInRange(const QDateTime &date) const;
};

#endif // REMINDERFILTERPROXYMODEL_H
