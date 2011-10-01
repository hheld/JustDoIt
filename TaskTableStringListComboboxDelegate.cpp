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

#include <QComboBox>
#include <QDebug>
#include <QStringListModel>

#include "TaskTableStringListCombobox.h"

TaskTableStringListComboboxDelegate::TaskTableStringListComboboxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget * TaskTableStringListComboboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    QComboBox *editor = new QComboBox(parent);

    editor->setModel(model);

    return editor;
}

void TaskTableStringListComboboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = static_cast<QComboBox*>(editor);
    QStringListModel *stringListModel = static_cast<QStringListModel*>(model);
    QStringList allCategories = stringListModel->stringList();

    QString selectionFromModel = index.model()->data(index, Qt::DisplayRole).toString();

    int selectedIndex = allCategories.indexOf(selectionFromModel);

    cb->setCurrentIndex(selectedIndex);
}

void TaskTableStringListComboboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = static_cast<QComboBox*>(editor);

    model->setData(index, cb->currentText());
}

void TaskTableStringListComboboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}

void TaskTableStringListComboboxDelegate::setModel(QAbstractItemModel *model)
{
    this->model = model;
}
