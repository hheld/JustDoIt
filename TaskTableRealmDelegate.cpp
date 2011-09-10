#include <QComboBox>
#include <QDebug>
#include <QStringListModel>

#include "TaskTableRealmDelegate.h"

TaskTableRealmDelegate::TaskTableRealmDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget * TaskTableRealmDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    QComboBox *editor = new QComboBox(parent);

    editor->setModel(model);

    return editor;
}

void TaskTableRealmDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    Q_UNUSED(index);

    QComboBox *cb = static_cast<QComboBox*>(editor);
    QStringListModel *stringListModel = static_cast<QStringListModel*>(model);
    QStringList allRealms = stringListModel->stringList();

    QString selectionFromModel = index.model()->data(index, Qt::DisplayRole).toString();

    int selectedIndex = allRealms.indexOf(selectionFromModel);

    cb->setCurrentIndex(selectedIndex);

    return;
}

void TaskTableRealmDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = static_cast<QComboBox*>(editor);

    model->setData(index, cb->currentText());
}

void TaskTableRealmDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}

void TaskTableRealmDelegate::setModel(QAbstractItemModel *model)
{
    this->model = model;
}
