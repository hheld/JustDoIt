#include "ReminderFilterProxyModel.h"

#include "TaskTableModel.h"
#include "Task.h"

#include <QDateTime>

ReminderFilterProxyModel::ReminderFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    setFilterKeyColumn(6);
}

bool ReminderFilterProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);

    // only show done, title, and due date columns
    if(source_column==6 || source_column==3 || source_column==7)
    {
        return true;
    }

    return false;
}

bool ReminderFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);

    bool accept = true;

    const TaskTableModel *model = static_cast<const TaskTableModel*>(sourceModel());

    accept = !model->getTasks().at(source_row)->done() && accept;

    QModelIndex index = sourceModel()->index(source_row, 6, source_parent);

    accept = accept && dateInRange(sourceModel()->data(index).toDateTime());

    return accept;
}

bool ReminderFilterProxyModel::dateInRange(const QDateTime &date) const
{
    // only accept if the due date is less than 2 hours in the future
    return date <= QDateTime::currentDateTime().addSecs(60*60*2);
}
