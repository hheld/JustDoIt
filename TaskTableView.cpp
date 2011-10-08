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

#include <QDebug>
#include <QHelpEvent>
#include <QToolTip>

#include "TaskTableView.h"

TaskTableView::TaskTableView(QWidget *parent) :
    QTableView(parent)
{
}

bool TaskTableView::viewportEvent(QEvent *event)
{
    if(event->type() == QEvent::ToolTip)
    {
        QHelpEvent *hevent = static_cast<QHelpEvent*>(event);

        if(columnAt(hevent->pos().x()) == 7)
        {
            int row = rowAt(hevent->pos().y());

            if(row != -1)
            {
                QModelIndex index = indexAt(hevent->pos());

                QToolTip::showText(hevent->globalPos(), index.data().toString(), this, QRect(0, 0, 1, 1));
            }
            else
            {
                QToolTip::hideText();
                event->ignore();
            }
        }
        else
        {
            QToolTip::hideText();
            event->ignore();
        }

        return true;
    }

    return QTableView::viewportEvent(event);
}

void TaskTableView::mousePressEvent(QMouseEvent *event)
{
    if(!indexAt(event->pos()).isValid())
    {
        emit clickedOutsideData();
    }

    QTableView::mousePressEvent(event);
}

void TaskTableView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QTableView::selectionChanged(selected, deselected);

    if(selected.count())
    {
        emit selectionHasChanged(selected.indexes().at(0));
    }
}
