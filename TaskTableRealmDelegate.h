#ifndef TASKTABLEDELEGATES_H
#define TASKTABLEDELEGATES_H

#include <QStyledItemDelegate>

class TaskTableRealmDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TaskTableRealmDelegate(QObject *parent = 0);

    void setModel(QAbstractItemModel* model);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QAbstractItemModel *model;
};

#endif // TASKTABLEDELEGATES_H
