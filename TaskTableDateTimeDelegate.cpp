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
