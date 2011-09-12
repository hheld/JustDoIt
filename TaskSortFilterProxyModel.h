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
    void setNumOfDaysAhead(int numOfDaysAhead);

private:
    bool hideDone;
    int numOfDaysAhead;

    bool dateInRange(const QDate &date) const;
};

#endif // TASKSORTFILTERPROXYMODEL_H
