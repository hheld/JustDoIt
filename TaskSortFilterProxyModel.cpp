#include <QDebug>

#include "TaskSortFilterProxyModel.h"
#include "Task.h"
#include "TaskTableModel.h"

TaskSortFilterProxyModel::TaskSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    hideDone(false)
{
    setDynamicSortFilter(true);
}

bool TaskSortFilterProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);

    // hide the id column
    if(source_column==0)
    {
        return false;
    }

    return true;
}

bool TaskSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);

    const TaskTableModel *model = static_cast<const TaskTableModel*>(sourceModel());

    if(hideDone)
    {
        return !model->getTasks().at(source_row)->done();
    }

    return true;
}

void TaskSortFilterProxyModel::hideDoneTasks(bool done)
{
    hideDone = done;

    setFilterFixedString("Finished");
    setFilterKeyColumn(2);
}
