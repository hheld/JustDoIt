#ifndef TASKTABLEDATETIMEDELEGATE_H
#define TASKTABLEDATETIMEDELEGATE_H

#include <QStyledItemDelegate>

class TaskTableDateTimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TaskTableDateTimeDelegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TASKTABLEDATETIMEDELEGATE_H
