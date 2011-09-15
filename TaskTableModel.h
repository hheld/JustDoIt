#ifndef TASKTABLEMODEL_H
#define TASKTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class Task;
class QTimer;

class TaskTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TaskTableModel(const QVector<Task*> allTasks, QObject *parent=0);
    ~TaskTableModel();

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    const QVector<Task*>& getTasks() const;

private:
    Q_DISABLE_COPY(TaskTableModel)

    QVector<Task*> allTasks;

    QTimer *timer;

private slots:
    void resetView();
};

#endif // TASKTABLEMODEL_H
