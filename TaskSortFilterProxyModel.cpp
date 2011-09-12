#include <QDebug>

#include "TaskSortFilterProxyModel.h"
#include "Task.h"
#include "TaskTableModel.h"

TaskSortFilterProxyModel::TaskSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    hideDone(false),
    numOfDaysAhead(-1)
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

    bool accept = true;

    const TaskTableModel *model = static_cast<const TaskTableModel*>(sourceModel());

    // handle hidden finished tasks
    if(hideDone)
    {
        accept = !model->getTasks().at(source_row)->done() && accept;
    }

    QModelIndex index1 = sourceModel()->index(source_row, 1, source_parent);
    QModelIndex index2 = sourceModel()->index(source_row, 2, source_parent);
    QModelIndex index7 = sourceModel()->index(source_row, 7, source_parent);
    QModelIndex index8 = sourceModel()->index(source_row, 8, source_parent);
    QModelIndex index6 = sourceModel()->index(source_row, 6, source_parent);

    accept = accept && (sourceModel()->data(index1).toString().contains(filterRegExp())
                        || sourceModel()->data(index2).toString().contains(filterRegExp())
                        || sourceModel()->data(index7).toString().contains(filterRegExp())
                        || sourceModel()->data(index8).toString().contains(filterRegExp()))
             && dateInRange(sourceModel()->data(index6).toDate());

    return accept;
}

void TaskSortFilterProxyModel::hideDoneTasks(bool done)
{
    hideDone = done;

    setFilterKeyColumn(3);
}

bool TaskSortFilterProxyModel::dateInRange(const QDate &date) const
{
    if(numOfDaysAhead==-1)
    {
        return true;
    }
    else
    {
        return date <= QDate::currentDate().addDays(numOfDaysAhead);
    }
}

void TaskSortFilterProxyModel::setNumOfDaysAhead(int numOfDaysAhead)
{
    this->numOfDaysAhead = numOfDaysAhead;

    setFilterKeyColumn(6);
}
