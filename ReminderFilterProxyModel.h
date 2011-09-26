#ifndef REMINDERFILTERPROXYMODEL_H
#define REMINDERFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class ReminderFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ReminderFilterProxyModel(QObject *parent = 0);

    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    bool dateInRange(const QDateTime &date) const;
};

#endif // REMINDERFILTERPROXYMODEL_H
