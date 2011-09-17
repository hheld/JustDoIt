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

    QStyleOptionViewItem newOption(option);

    if(isDone)
    {
        newOption.palette.setColor(QPalette::Text, QColor(0, 200, 0));
    }
    else
    {
        newOption.palette.setColor(QPalette::Text, QColor(200, 0, 0));
    }

    QStyledItemDelegate::paint(painter, newOption, index);
}
