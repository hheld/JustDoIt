#include <QtAlgorithms>

#include "TaskTableModel.h"
#include "Task.h"
#include "taskSort.h"

TaskTableModel::TaskTableModel(const QVector<Task*> allTasks, QObject *parent) :
    QAbstractTableModel(parent),
    allTasks(allTasks)
{
}

TaskTableModel::~TaskTableModel()
{

}

int TaskTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return allTasks.size();
}

int TaskTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 9;
}

QVariant TaskTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= allTasks.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        Task* task = allTasks.at(index.row());

        if (index.column() == 0) return task->id();
        else if (index.column() == 1) return task->location();
        else if (index.column() == 2) return task->realm();
        else if (index.column() == 3) return task->done();
        else if (index.column() == 4) return task->startDate();
        else if (index.column() == 5) return task->endDate();
        else if (index.column() == 6) return task->dueDate();
        else if (index.column() == 7) return task->title();
        else if (index.column() == 8) return task->description();
    }

    return QVariant();
}

QVariant TaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return tr("Id");

        case 1:
            return tr("Location");

        case 2:
            return tr("Realm");

        case 3:
            return tr("Done");

        case 4:
            return tr("Start date");

        case 5:
            return tr("End date");

        case 6:
            return tr("Due date");

        case 7:
            return tr("Title");

        case 8:
            return tr("Description");

        default:
            return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags TaskTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if(index.column() == 0) return QAbstractTableModel::flags(index);

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool TaskTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();

        Task *currentTask = allTasks.at(row);

        if (index.column() == 0) currentTask->id(value.toInt());
        else if (index.column() == 1) currentTask->location(value.toString());
        else if (index.column() == 2) currentTask->realm(value.toString());
        else if (index.column() == 3) currentTask->done(value.toBool());
        else if (index.column() == 4) currentTask->startDate(value.toDateTime());
        else if (index.column() == 5) currentTask->endDate(value.toDateTime());
        else if (index.column() == 6) currentTask->dueDate(value.toDateTime());
        else if (index.column() == 7) currentTask->title(value.toString());
        else if (index.column() == 8) currentTask->description(value.toString());
        else return false;

        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

bool TaskTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    beginInsertRows(index, position, position+rows-1);

    for (int row=0; row<rows; ++row)
    {
        Task *newTask = new Task();
        allTasks.append(newTask);
    }

    endInsertRows();

    return true;
}

bool TaskTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(index, position, position+rows-1);

    for (int row=0; row<rows; ++row)
    {
        allTasks.remove(position);
    }

    endRemoveRows();

    return true;
}

const QVector<Task *> & TaskTableModel::getTasks() const
{
    return allTasks;
}

void TaskTableModel::sort(int column, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();

    if(order == Qt::AscendingOrder)
    {
        if (column == 0) qSort(allTasks.begin(), allTasks.end(), taskLessThan<0>);
        else if (column == 1) qSort(allTasks.begin(), allTasks.end(), taskLessThan<1>);
        else if (column == 2) qSort(allTasks.begin(), allTasks.end(), taskLessThan<2>);
        else if (column == 3) qSort(allTasks.begin(), allTasks.end(), taskLessThan<3>);
        else if (column == 4) qSort(allTasks.begin(), allTasks.end(), taskLessThan<4>);
        else if (column == 5) qSort(allTasks.begin(), allTasks.end(), taskLessThan<5>);
        else if (column == 6) qSort(allTasks.begin(), allTasks.end(), taskLessThan<6>);
        else if (column == 7) qSort(allTasks.begin(), allTasks.end(), taskLessThan<7>);
        else if (column == 8) qSort(allTasks.begin(), allTasks.end(), taskLessThan<8>);
        else return;
    }
    else if(order == Qt::DescendingOrder)
    {
        if (column == 0) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<0>);
        else if (column == 1) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<1>);
        else if (column == 2) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<2>);
        else if (column == 3) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<3>);
        else if (column == 4) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<4>);
        else if (column == 5) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<5>);
        else if (column == 6) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<6>);
        else if (column == 7) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<7>);
        else if (column == 8) qSort(allTasks.begin(), allTasks.end(), taskGreaterThan<8>);
        else return;
    }

    emit layoutChanged();
}
