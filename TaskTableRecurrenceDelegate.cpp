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

#include <QLineEdit>
#include <QPainter>

#include "TaskTableRecurrenceDelegate.h"

TaskTableRecurrenceDelegate::TaskTableRecurrenceDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget * TaskTableRecurrenceDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    QLineEdit *editor = new QLineEdit(parent);
    editor->setInputMask(tr("999 \\D\\ays 99 \\Hours 99 Mi\\nutes"));

    return editor;
}

void TaskTableRecurrenceDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString currentModelText = index.model()->data(index).toString();

    int totalMinutes = currentModelText.toInt();

    int days = totalMinutes / (24*60);
    int hours = (totalMinutes - days * 24 * 60) / 60;
    int minutes = totalMinutes - days * 24 * 60 - hours * 60;

    currentModelText = QString("%1%2%3").arg(days, 3, 'f', 0, '0').arg(hours, 2, 'f', 0, '0').arg(minutes, 2, 'f', 0, '0');

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);

    lineEdit->setText(currentModelText);
}

void TaskTableRecurrenceDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);

    QString currentTextLineEdit = lineEdit->text().replace(" Days ", "").replace(" Hours ", "").replace(" Minutes ", "");

    int days = currentTextLineEdit.mid(0, 3).toInt();
    int hours = currentTextLineEdit.mid(3, 2).toInt();
    int minutes = currentTextLineEdit.mid(5, 2).toInt();

    model->setData(index, days*24*60 + hours*60 + minutes);
}

void TaskTableRecurrenceDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}

void TaskTableRecurrenceDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int minutes = index.model()->data(index).toInt();

    QPen myPen(QColor(100, 50, 20));

    QFont myFont = option.font;
    myFont.setPointSizeF(0.75*myFont.pointSizeF());

    painter->setPen(myPen);
    painter->setFont(myFont);

    if(minutes == 0)
    {
        QString text = tr("Not recurring");

        painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }
    else
    {
        int h = minutes / 60;
        int d = h / 24;

        int leftHours = (minutes - d*24*60) / 60;
        int leftMinutes = minutes - leftHours*60 - d*24*60;

        QString text;

        if(d > 0)
        {
            text = tr("%1 days %2 hours %3 minutes").arg(QString::number(d)).arg(QString::number(leftHours)).arg(QString::number(leftMinutes));
        }
        else if(leftHours > 0)
        {
            text = tr("%1 hours %2 minutes").arg(QString::number(leftHours)).arg(QString::number(leftMinutes));
        }
        else
        {
            text = tr("%1 minutes").arg(QString::number(leftMinutes));
        }

        painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }
}
