#include <QVector>
#include <QPainter>

#include "TaskTableColorDoneDelegate.h"
#include "TaskTableModel.h"
#include "TaskSortFilterProxyModel.h"
#include "Task.h"

TaskTableColorDoneDelegate::TaskTableColorDoneDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void TaskTableColorDoneDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const TaskSortFilterProxyModel *modelProxy = static_cast<const TaskSortFilterProxyModel*>(index.model());
    const TaskTableModel *model = static_cast<const TaskTableModel*>(modelProxy->sourceModel());

    const QVector<Task*> allTasks = model->getTasks();

    bool isDone = allTasks[modelProxy->mapToSource(index).row()]->done();

    if(isDone)
    {
        QStyleOptionViewItem newOption(option);

        newOption.palette.setColor(QPalette::Text, QColor(0, 255, 0));

        QStyledItemDelegate::paint(painter, newOption, index);

        return;
    }
    else
    {
        QStyleOptionViewItem newOption(option);

        newOption.palette.setColor(QPalette::Text, QColor(255, 0, 0));

        QStyledItemDelegate::paint(painter, newOption, index);

        return;
    }

    QStyledItemDelegate::paint(painter, option, index);
}
