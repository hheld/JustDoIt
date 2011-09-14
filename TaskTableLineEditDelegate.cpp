#include <QLineEdit>

#include "TaskTableLineEditDelegate.h"

TaskTableLineEditDelegate::TaskTableLineEditDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget * TaskTableLineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);

    QLineEdit *editor = new QLineEdit(parent);

    return editor;
}

void TaskTableLineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString currentModelText = index.model()->data(index).toString();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);

    lineEdit->setText(currentModelText);
}

void TaskTableLineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);

    QString currentTextLineEdit = lineEdit->text();

    model->setData(index, currentTextLineEdit);
}

void TaskTableLineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}
