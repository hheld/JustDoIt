#ifndef TASKTABLELINEEDITDELEGATE_H
#define TASKTABLELINEEDITDELEGATE_H

#include <QStyledItemDelegate>

class TaskTableLineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TaskTableLineEditDelegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TASKTABLELINEEDITDELEGATE_H
