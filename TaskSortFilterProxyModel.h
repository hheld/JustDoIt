#ifndef TASKSORTFILTERPROXYMODEL_H
#define TASKSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class TaskSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TaskSortFilterProxyModel(QObject *parent = 0);

    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

public slots:
    void hideDoneTasks(bool done);

private:
    bool hideDone;
};

#endif // TASKSORTFILTERPROXYMODEL_H
