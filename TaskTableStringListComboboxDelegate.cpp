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
