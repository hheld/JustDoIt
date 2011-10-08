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

#include <QDateTimeEdit>

#include "TaskTableDateTimeDelegate.h"

TaskTableDateTimeDelegate::TaskTableDateTimeDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget * TaskTableDateTimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    QDateTimeEdit *editor = new QDateTimeEdit(parent);

    editor->setCalendarPopup(true);

    return editor;
}

void TaskTableDateTimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QDateTimeEdit *dte = static_cast<QDateTimeEdit*>(editor);

    QDateTime currentDt = qMax(index.data().toDateTime(), QDateTime::currentDateTime());

    dte->setDateTime(currentDt);
}

void TaskTableDateTimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDateTimeEdit *dte = static_cast<QDateTimeEdit*>(editor);

    QDateTime currentDt = dte->dateTime();

    model->setData(index, currentDt);
}

void TaskTableDateTimeDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}

void TaskTableDateTimeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 newOption(option);

    newOption.palette.setColor(QPalette::Text, QColor(0, 0, 200));

    QStyledItemDelegate::paint(painter, newOption, index);
}
