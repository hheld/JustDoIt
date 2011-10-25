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

#include <QPlainTextEdit>

#include "TaskTableTextEditDelegate.h"

TaskTableTextEditDelegate::TaskTableTextEditDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget * TaskTableTextEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    QPlainTextEdit *editor = new QPlainTextEdit(parent);

    return editor;
}

void TaskTableTextEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString textInModel = index.model()->data(index).toString();

    QPlainTextEdit *textEdit = static_cast<QPlainTextEdit*>(editor);

    textEdit->document()->setPlainText(textInModel);
}

void TaskTableTextEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QPlainTextEdit *textEdit = static_cast<QPlainTextEdit*>(editor);

    QString currentText = textEdit->toPlainText();

    model->setData(index, currentText);
}

void TaskTableTextEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    QRect cellRect = option.rect;
    cellRect.setWidth(cellRect.width() + 200);
    cellRect.setHeight(cellRect.height() + 200);

    editor->setGeometry(cellRect);
}

QSize TaskTableTextEditDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QSize(300, option.rect.height());
}
